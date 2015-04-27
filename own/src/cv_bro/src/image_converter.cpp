#include "image_converter.h"
#include <termios.h>
#include <algorithm>
const double p = 1.6;
int getch()
{
  static struct termios oldt, newt;
  tcgetattr( STDIN_FILENO, &oldt);           // save old settings
  newt = oldt;
  newt.c_cc[VMIN] = 0; newt.c_cc[VTIME] = 0;
  newt.c_lflag &= ~(ICANON);                 // disable buffering      
  tcsetattr( STDIN_FILENO, TCSANOW, &newt);  // apply new settings

  int c = getchar(); 						 // read character (non-blocking)

  tcsetattr( STDIN_FILENO, TCSANOW, &oldt);  // restore old settings
  return c;
}

double euclideanDistance(Point2f point1)
{
	double match=0;
    match += sqrt((point1.x - 0) * (point1.x - 0)+ (point1.y - 0) * (point1.y - 0));
    return match;
	
}

Point ImageConverter::normCrossCorrelation(Mat imgI, Mat imgJ,vector<Point2f> points1, vector<uchar> status, int method)
{
	Mat res,rec1;
	Size size(307,230);
    for(int i = 0; i <= points1.size(); i++)
    {
        if(status[i] == 1)
        {
			getRectSubPix(imgI,size,points1[i],rec1);
            matchTemplate(rec1, ROI, res, method);
            //cout << ((float *)(res.operator _IplImage().imageData))[0] << endl;
        }
    }
    normalize(res,res,0,1,NORM_MINMAX,-1,cv::Mat());
    double minVal,maxVal;
    Point minLoc,maxLoc;
	
	minMaxLoc(res,&minVal,&maxVal,&minLoc,&maxLoc,cv::Mat());
	
	cout << "new location: " << maxLoc << " Maxval: " << maxVal << endl; 
	return minLoc;
}

Point2f Mean(vector<Point2f> points)
{
	Mat mean_;
	reduce(points,mean_,CV_REDUCE_AVG,1);
	Point2f mean(mean_.at<float>(0,0),mean_.at<float>(0,1));
	//cout << "Mean: " << mean_ << endl; 
	return mean;
	
}

bool std_dev(vector<Point2f> points)
{
	double Std_dev;
	Point2f mean = Mean(points);
	for(int i = 0; i < points.size(); i++)
	{	
		Std_dev += pow(euclideanDistance(points[i]-mean),2);

	}
	Std_dev = Std_dev/points.size();
	Std_dev = sqrt(Std_dev);
	cout << "STD_DEV: " << Std_dev << endl; 
	if(Std_dev <= 200)
	{
		cout << "Still reasonable fine " << endl; 
		return true; //Threshold has to be added to know when it should re init the goodFeaturesToTrack Function. 
	}
	else
	{
		cout <<"you are fucked - too much drifting " << endl;  
		return false;
	}
}
double std_dev_determine(vector<Point2f> points)
{
	double Std_dev;
	Point2f mean = Mean(points);
	for(int i = 0; i < points.size(); i++)
	{	
		Std_dev += pow(euclideanDistance(points[i]-mean),2);

	}
	Std_dev = Std_dev/points.size();
	Std_dev = sqrt(Std_dev);
	return Std_dev;
}

Point2f newBox(vector<Point2f> points1,vector<Point2f> points2,vector<Point2f> points3)
{
	double Std_dev1 = std_dev_determine(points1);
	double Std_dev2 = std_dev_determine(points2);
	double Std_dev3 = std_dev_determine(points3);
	double decision = min(min(Std_dev1,Std_dev2),Std_dev3);
	if(decision == Std_dev1)
	{
		cout << "final" << endl;
		return  Mean(points1);
	}
	if(decision == Std_dev2)
	{
		cout << "points[1]" << endl;
		return  Mean(points2);

	}	
	if(decision == Std_dev3)
	{
		cout << "points[0]" << endl; 
		return  Mean(points3);
	}	
}
ImageConverter::ImageConverter()
    : it_(nh_),pos(2),	vel(2) 
  {
    // Subscrive to input video feed and publish output video feed
    
		image_sub_ = it_.subscribe("/bumblebeePTU/left/image_rect_color", 1, 
		&ImageConverter::imageDetect, this);
		image_pub_ = it_.advertise("/image_converter/output_video", 1);
 		state = false;
 		reinit = false;
 		redetect = false;
 		sendCommands = false;
 		frames = 0;
 		goodFeatures.reserve(500);
 		String frontalface_alt2_XML = "/usr/share/opencv/haarcascades/haarcascade_frontalface_alt2.xml";
		String frontal_alt_XML = "/usr/share/opencv/haarcascades/haarcascade_frontalface_alt.xml";
		String frontal_alt_tree_XML = "/usr/share/opencv/haarcascades/haarcascade_frontalface_alt_tree.xml"; 
		String frontal_face_xml = "/usr/share/opencv/haarcascades/haarcascade_frontalface_default.xml";
	
		if( !frontalface_alt2.load( frontalface_alt2_XML ) )
		{
				cout << "face_cascade Cascade Error" << endl;
		};
		if( !frontal_alt.load( frontal_alt_XML ) )
		{
				cout << "profileface Cascade Error" << endl;
		};
		if(!frontal_alt_tree.load( frontal_alt_tree_XML ))
		{
			cout << "nose Cascade Error" << endl;
		}
		if(!frontal_face.load( frontal_face_xml ))
		{
			cout << "nose Cascade Error" << endl;
		}
  }

 ImageConverter::~ImageConverter()
  {
    //cv::destroyAllWindows();
  }
  
  void ImageConverter::imageDetect(const sensor_msgs::ImageConstPtr& msg)
  {	 
	 facedetect_pub = nh_.advertise<sensor_msgs::JointState>("/ptu/cmd", 1);
	 sub = nh_.subscribe("/joint_states",1,&ImageConverter::chatterCallback,this); 
     cv_bridge::CvImagePtr cv_ptr;
     sensor_msgs::JointState ms;
    try
    {
      cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
    }
    catch (cv_bridge::Exception& e)
    {
      ROS_ERROR("cv_bridge exception: %s", e.what());
      return;
    }
	if(!(state))
	{
		image = cv_ptr->image;
		//ROI_IMAGE = cv_ptr->image;
		smallIMG = image;
		cvtColor(smallIMG,smallIMG,COLOR_BGR2GRAY);
	    cv::equalizeHist(smallIMG, smallIMG); 
	    ROI_IMAGE = smallIMG;
	    Size size(100,100);  
	    resize(smallIMG,smallIMG,size);
		vector<Rect> faces(1);
		Rect face_big;
		center_of_frame.x = image.size().width/2;
		center_of_frame.y = image.size().height/2;
		center_of_frame_small.x = smallIMG.size().width/2;
		center_of_frame_small.y = smallIMG.size().height/2;
		pair<Point, Point> corners;
		pair<double,double> displacement;
		double displacement_pixel_x;
		double displacement_pixel_y;
		pair<Rect, bool> response;
		
			//if (image.type()!= 8) 
			//{
				//cvtColor(image,image, CV_8U);
			//}
    
	//-- 1. Load the cascades
		
			circle(image, center_of_frame, 1, CV_RGB(0,255,255),8,8,0);
			circle(smallIMG, center_of_frame_small, 1, CV_RGB(0,255,255),3,3,0);
			
    
	//-- Detect faces
			frontalface_alt2.detectMultiScale(smallIMG, faces, 1.1, 2, 0, Size(0, 0) );
			//frontal_alt.detectMultiScale( smallIMG, faces, 1.1, 2, 0, Size(0, 0) );
			//frontal_alt_tree.detectMultiScale( smallIMG, faces, 1.1, 2, 0, Size(0, 0) );
			//frontal_face.detectMultiScale( smallIMG, faces, 1.1, 2, 0, Size(0, 0) );

			
			int i,k;
			for( i = k = 0; i<faces.size() ; i++)
			{
				
					Point center_position_of_face_small((faces[i].br().x+faces[i].tl().x)/2,(faces[i].tl().y+faces[i].br().y)/2);
					Point corner_1_small(faces[i].br().x,faces[i].tl().y);
					Point corner_2_small = faces[i].tl();
					Point corner_3_small = faces[i].br();
					Point corner_4_small(faces[i].tl().x,faces[i].br().y);
					
					Point center_position_of_face((faces[i].br().x*float(image.cols)/float(smallIMG.cols)+faces[i].tl().x*float(image.cols)/float(smallIMG.cols))/2,(faces[i].tl().y*float(image.rows)/float(smallIMG.rows)+faces[i].br().y*float(image.rows)/float(smallIMG.rows))/2);
					Point corner_1(faces[i].br().x*float(image.cols)/float(smallIMG.cols),faces[i].tl().y*float(image.rows)/float(smallIMG.rows));
					Point corner_2(faces[i].tl().x*float(image.cols)/float(smallIMG.cols),faces[i].tl().y*float(image.rows)/float(smallIMG.rows));
					Point corner_3(faces[i].br().x*float(image.cols)/float(smallIMG.cols),faces[i].br().y*float(image.rows)/float(smallIMG.rows));
					Point corner_4(faces[i].tl().x*float(image.cols)/float(smallIMG.cols),faces[i].br().y*float(image.rows)/float(smallIMG.rows));
					
					face_big.br() = corner_2;
					face_big.tl() = corner_3; 	
					face_big.width  = corner_1.x-corner_2.x;
					face_big.height = corner_1.y-corner_4.y;
					Rect test(corner_2,corner_3);
					
					face_big = test; 
					face_big += Size(15,70); 				
					rectangle(smallIMG, faces[i], CV_RGB(0,255,0),4,8,0);
					rectangle(image,test , CV_RGB(45,255,102),8,8,0);
					
					circle(smallIMG, center_position_of_face_small, 8, CV_RGB(128,128,128),8,8,0);
					circle(smallIMG, corner_1_small, 1, CV_RGB(128,128,128),8,8,0);
					circle(smallIMG, corner_2_small, 1, CV_RGB(128,128,128),8,8,0);
					circle(smallIMG, corner_3_small, 1, CV_RGB(128,128,128),8,8,0);
					circle(smallIMG, corner_4_small, 1, CV_RGB(128,128,128),8,8,0);
					
					circle(image, center_position_of_face, 8, CV_RGB(128,128,128),8,8,0);
					circle(image, corner_1, 1, CV_RGB(128,128,128),8,8,0);
					circle(image, corner_2, 1, CV_RGB(128,128,128),8,8,0);
					circle(image, corner_3, 1, CV_RGB(128,128,128),8,8,0);
					circle(image, corner_4, 1, CV_RGB(128,128,128),8,8,0);
					
					line(smallIMG, 	center_position_of_face_small, center_of_frame_small, CV_RGB(0,200,0),1,8);
					line(image, center_position_of_face, center_of_frame, CV_RGB(0,200,0),1,8);
					
					faces[k++] = faces[i];
				//}
			}
		faces.resize(k);	
		flip(image, image, 1);
		flip(smallIMG,smallIMG,1);
		imshow("Facedetection", image);
		imshow("FACEdetection - small", smallIMG);
		if(face_big.area() != 0 )
		{
			ROI = ROI_IMAGE(face_big);
			imwrite("/home/kratnarajah/Desktop/template_matching_images/ROI.jpg",ROI); 
			face = 	face_big;
		}
		cout << "face - info: " << face_big.area() << endl;
		waitKey(1);
		int cc = getch();
		if(cc == 'y' || redetect == true)
		{
			
			if(cc == 'y')
			{	
				cout << "keypress registered" << endl; 
			}
			else if(redetect == true)
			{
				cout << "redetect applied" << endl; 
			}
			state = true;
			redetect = false;
			destroyAllWindows();
		}
		int key = getch();
		if(key == 'r')
		{
			cout << "keypress registered" << endl;  
			cout << "RESET STATE"	<< endl; 
			pos[0] = 0;
			pos[1] = 0;
			vel[0] = 0.1;
			vel[1] = 0.1;
			ms.position = pos;
			ms.velocity = vel;
			facedetect_pub.publish(ms);

		}
	} 
	//else
	//{
		//cout <<"Face detected" << endl; 
		//displacement = track(face,cv_ptr->image);
		
		////if(abs(pos[0]-position_prev_pan) > 0.50 )
		////{
			//cout << "PAN change" << endl;
			//pos[0] = ceil(sin(displacement.first*0.000727220522)*1000)/1000 + position_prev_pan;
		////}
		////if(abs(pos[1]-position_prev_pan) > 0.50)
		////{
			////cout << "tilt change" << endl;
			//pos[1] =0; //-ceil(sin(displacement.second*0.000727220522)*1000)/1000 + position_prev_tilt;
		////}
		
			//ms.position = pos;
			//vel[0] = 0.1;//abs(pos[0])/3;//2*atan(displacement.first+position_prev[0]/2*physical_width)*0.01 ;
			//vel[1] = 0.1;//abs(pos[1])/3;
			//ms.velocity = vel;
			//ROS_INFO_STREAM("pan: "<<pos[0]);
			//ROS_INFO_STREAM("pan_prev: " << position_prev_pan);
			//ROS_INFO_STREAM("Subtracted: " <<abs(pos[0]-position_prev_pan));
			//ROS_INFO_STREAM("tilt: "<<pos[1]);
			//ROS_INFO_STREAM("tilt_prev: " << position_prev_tilt);
			//ROS_INFO_STREAM("Subtracted: " <<abs(pos[1]-position_prev_tilt));
			//facedetect_pub.publish(ms);
			//ROS_WARN_STREAM("OUT of if");
			//waitKey(1);
    //// Update GUI Window
    ////cv::imshow(OPENCV_WINDOW, cv_ptr->image);
    
    //// Output modified video stream
    ////image_pub_.publish(cv_ptr->toImageMsg());
	//}
	else
	{
		    image = cv_ptr->image;
   			flip(image, image, 1);
		    cvtColor(image,gray,COLOR_BGR2GRAY);
			equalizeHist(gray,gray);
			Mat mask(image.size(),CV_8UC1,Scalar(0));
			mask(face).setTo(Scalar(255));
			circle(cv_ptr->image, center_of_frame, 1, CV_RGB(0,255,255),8,8,0);
			static uint64_t c;
			if (c++ == 0)
			{
				cout << "automatic initialization" << endl;
				goodFeaturesToTrack(gray, points[1], MAX_COUNT, 0.01, 10, mask, 3, 0, 0.04);
				cornerSubPix(gray, points[1], subPixWinSize, Size(-1,-1), termcrit);
				cout << "points[1].size(): "<< points[1].size()<< endl; 
				reinit = false;
				cout << "i am here" << endl;

			}
			
			//if(reinit == true)
			//{
				//cout << "Reinit engaged" << endl;
				//vector<Point2f> tmp;
				//tmp.push_back(point);
				//goodFeaturesToTrack(gray, tmp, MAX_COUNT, 0.01, 10, mask, 3, 0, 0.04);
				//cornerSubPix( gray, tmp, winSize, cvSize(-1,-1), termcrit);
				//points[1].push_back(tmp[0]);
				//reinit = false;
				
			//}
			  
			if( !points[0].empty() )
				{
					vector<uchar> status;
					vector<float> err;
					vector<uchar> status2;
					vector<float> err2;
					if(prevGray.empty())
					{
						gray.copyTo(prevGray);
					}
					//Lukas kanade optilcal flow + Forward - backward error
					calcOpticalFlowPyrLK(prevGray, gray, points[0], points[1], status, err, winSize, 3, termcrit, OPTFLOW_LK_GET_MIN_EIGENVALS, qualitylevel);
					calcOpticalFlowPyrLK(gray, prevGray, points[1], point_final, status2, err2, winSize, 3, termcrit, OPTFLOW_LK_GET_MIN_EIGENVALS, qualitylevel);
					//outlier_point(); 		
					//double match=0; 
					Point2f center = Mean(point_final);
					Point2f center2 = Mean(points[1]);
					//Point2f center3 = Mean(points[0]);
					//Point2f centrum;
					//centrum.x = center.x + center2.x /2.0;
					//centrum.y = center.y + center2.y /2.0;
					//cout << "centrum: " << centrum << endl; 
					if(std_dev(point_final) &&	std_dev(points[1]))
					{	
						cout << "Alowable deviation" << endl; 
						goodFeatures.push_back(center);
						goodFeatures.push_back(center2);
						sendCommands = true;
						ROI = prevGray(face);
						imwrite("/home/kratnarajah/Desktop/template_matching_images/ROI.jpg",ROI);
						if(goodFeatures.empty())
						{
							backup_center = center;
							backup_center.y =+ 40;
						}
						else
						{
							backup_center = Mean(goodFeatures);
							Rect NewBOx;
							NewBOx.x  = backup_center.x-face.width/2;
							NewBOx.y  = backup_center.y-face.height/2/2; 
							NewBOx.width = face.width;
							NewBOx.height = face.height;
							face = NewBOx;
							
						}
						//backup_center2.x = min((center2 - backup_center).x,(center - backup_center).x)+backup_center.x;
						//backup_center2.y = min((center2 - backup_center).y,(center - backup_center).y)+backup_center.y;
						//goodFeatures.push_back(backup_center2);
						//rectangle(image,face,Scalar(255,255,0));
						cout << "face.tl(): " << face.tl() << endl; 
						cout << "backup_center: " <<backup_center << endl; 
						if(std_dev_determine(point_final)>120 ||std_dev_determine(point_final)>120)
						{
							frames++;
							cout << "Issues may occur (frame++) => taking precaution by removing outliers" << endl; 

						}
						else
						{
							frames = 0;
							cout << "frames reset" << endl; 

						}
						rectangle(image,face,Scalar(255,255,0));

					}
					else
					{
						frames+=10;
						sendCommands = false;
						cout << "frames++" <<endl; 
						cout << "Error_count: " << frames << endl; 
						if(frames <= 50)
						{
							cout << "Too far out" << endl; 
							cout << "std.dev point1:  " << std_dev_determine(points[1])<< "std.dev points_final: " <<std_dev_determine(point_final) <<endl;
							cout << "point1.size:  " << points[1].size() <<"points_final.size: " << point_final.size() << endl;
							cout << "point1 afstand til forrige: " << center2 - backup_center  << "point_final afstand til forrige: " << center - backup_center << endl;
							cout << "position point1: " << center2 << "point_final position: " <<center<< endl; 
							backup_center.x = min((center2 - backup_center).x,(center - backup_center).x)+backup_center.x;
							backup_center.y = min((center2 - backup_center).y,(center - backup_center).y)+backup_center.y;
							cout << "punkt: " << backup_center << endl; 
							circle(image,backup_center,12, Scalar(255,0,255),-1,19,3);
								
						}
						cout << "Move mask to: " << backup_center<< endl; 
						points[1].clear();
						//points[0].clear();
						point_final.clear();
						//punkt2  = normCrossCorrelation(prevGray,gray,points[1],status,CV_TM_SQDIFF); //CV_TM_CCOEFF_NORMED
						//cout << punkt2 << endl;
						Rect NewBOx;
						if(backup_center.x != 0  && backup_center.y != 0 )
						{
							NewBOx.x  = backup_center.x-face.width/2;
							NewBOx.y  = backup_center.y-face.height/2/2; 
							NewBOx.width = face.width;
							NewBOx.height = face.height;
							face = NewBOx;
						}
						else
						{
							face = face;
						}
						//face+=Size(10,10);
						cout << "new 	face.tl(): " << face.tl() << endl; 
						cout << "new 	face.br(): " << face.br() << endl;
						cout << "new 	face.height():  " << face.height << endl;
						cout << "new 	face.width(): 	" << face.width  << endl;
						rectangle(image,face,Scalar(255,255,0));
						mask(face).setTo(Scalar(255));
						vector<Point2f> tmp;
						goodFeaturesToTrack(gray, tmp, MAX_COUNT, 0.01, 10, mask, 3, 0, 0.04);
						cornerSubPix( gray, tmp, winSize, cvSize(-1,-1), termcrit);
						points[1].push_back(tmp[0]);
						calcOpticalFlowPyrLK(prevGray, gray, points[0], points[1], status, err, winSize, 3, termcrit, OPTFLOW_LK_GET_MIN_EIGENVALS, qualitylevel);
						calcOpticalFlowPyrLK(gray, prevGray, points[1], point_final, status2, err2, winSize, 3, termcrit, OPTFLOW_LK_GET_MIN_EIGENVALS, qualitylevel);
						//reinit = true;
						
						
					}
					for( int i = 0; i < points[1].size(); i++ )
					{
						if( status[i] && status2[i] ) // Forward - backward Error estimation => Good values are only taken. 
						{
							if(std_dev_determine(point_final) < 80)//std_dev_determine(points[1]))
							{
								//cout << "limit is now: " << std_dev_determine(point_final) << endl;  
								if(euclideanDistance(Mean(point_final) - point_final[i]) < 110)//std_dev_determine(point_final))
								{
									goodFeatures.push_back(point_final[i]);
								}
								else
								{
									//cout << "removed because distance is above!!!!!!!!!!!!!!!!!!!!!!!!: " <<  std_dev_determine(point_final)*(2*frames) <<endl;
									circle(image,point_final[i],4, Scalar(0,0,255),-1,10,0);
								}
							}	
							else
							{
								//cout << "limit is now: " << std_dev_determine(points[1]) << endl;  
								if(euclideanDistance(Mean(points[1]) - points[1][i]) < 110)//std_dev_determine(points[1])*(2*frames))
								{
									goodFeatures.push_back(points[1][i]);
								}
								else
								{
									//cout << "removed because distance is above: " <<  std_dev_determine(points[1])*(2*frames) <<endl;
									circle(image,points[1][i],4, Scalar(0,0,255),-1,10,0);
								}
							}
						}
						
						if(goodFeatures.empty())
						{
							cout << "emppty !!!!!!!!!!!!!" << endl;
							frames =- 30;
							cout << " No features, widen the std.dev " << endl; 
						}
						else if(goodFeatures.size() > 50)
						{
							backup_center = center;
							//cout << "features: " << goodFeatures.size() << endl; 
						}
						//else
						//{
							//points[1][k++] = points[1][i];
							//circle( image, points[1][i], 3, Scalar(0,255,0), -1, 8);
						//}
					}
					cout << "GoodFeatures.size(): "<< goodFeatures.size() << endl; 
					//euclideanDistance(points[1],point_final); 
					for(int j = 0; j<500; j++)
					{
						circle(image,goodFeatures[0],9, Scalar(0,0,255),-1,12,0);
						circle(image,goodFeatures[1],4, Scalar(0,255,0),-1,8,0);
						circle(image,Mean(goodFeatures),10,Scalar(255,0,255),-1,12,0);
						circle(image,punkt2,10,Scalar(0,255,255),-1,12,0);
						circle(image,goodFeatures[j],4, Scalar(255,0,0),-1,8,0);

					}
					//cout << "k: " << k  << endl;
					//points[1].resize(k);
					//ka = fitEllipse(goodFeatures);
					//ellipse(image, ka, CV_RGB(0, 0, 255));
					//circle(image,ka.center,5,CV_RGB(102,178,255),8,8,0);
					//cout << "Center-position: " << floor(ka.center.x) << "," << floor(ka.center.y) << endl; 
					displacement = make_pair(Mean(goodFeatures).x-center_of_frame.x,Mean(goodFeatures).y-center_of_frame.y);
			        line(image, center , center_of_frame, CV_RGB(0,200,0),1,8);

				}
      
        
        if( goodFeatures.size() < 20 )
        {
			cout << "Adding extra because goodFeature count getting low" << endl; 
            vector<Point2f> tmp;
            tmp.push_back(point);
            Rect templ = face;
            templ+= Size(30,30);
            Mat maskINC(image.size(),CV_8UC1,Scalar(0));
			maskINC(face).setTo(Scalar(255));
            goodFeaturesToTrack(gray, tmp, MAX_COUNT, 0.01, 10, maskINC, 3, 0, 0.04);
            cornerSubPix( gray, tmp, winSize, cvSize(-1,-1), termcrit);
            goodFeatures.push_back(tmp[0]);
        }
        std::swap(points[1], points[0]);
        cv::swap(prevGray, gray);
        //cout << "new - point: "<<points[1].size() << endl;
        //cout << "old - point: " << points[0].size() << endl;
        //cout << "GoodFeatures: " << goodFeatures.size() << endl; 
        goodFeatures.clear();
        //frames++; 
        //cout << "frames: "<< frames << endl;
        
        //if(frames==50)
        //{
            //state = false;
            //reinit = true;
            //redetect = true;
            //frames = 0; 
        //}
        //if(points[1].size()<10)
        //{
			//cout << "Too few features to track => init GoodFeaturesToTrack" << endl; 
			//state = false;
            //reinit = true;
            //redetect = true;
            //frames = 0; 	
       	//}
       	int key = getch();
		if(key == 'r')
		{
			cout << "keypress registered" << endl;  
			cout << "RESET STATE"	<< endl; 
			pos[0] = 0;
			pos[1] = 0;
			vel[0] = 0.8;
			vel[0] = 0.8;
			ms.position = pos;
			ms.velocity = vel;
			facedetect_pub.publish(ms);

		}
       	if(sendCommands)
       	{
			//if((abs(pos[0]-position_prev_pan) < 0.100))
			//{
				pos[0] = ceil(sin(displacement.first*0.000727220522)*1000)/10000 + position_prev_pan;

			//}	
			//if((abs(pos[1]-position_prev_tilt) < 0.100))
			//{
				pos[1] = -ceil(sin(displacement.second*0.000727220522)*1000)/10000 + position_prev_tilt;

			//}
			cout << "Speed1 is: " << abs(ceil(sin(displacement.first*0.000727220522)*1000)/10000 + position_prev_pan) << endl; 
			//if(abs(ceil(sin(displacement.first*0.000727220522)*1000)/1000 + position_prev_pan)>= 0.1)
			//{	
				vel[0] = 0.1;//abs(ceil(sin(displacement.first*0.000727220522)*1000)/1000 + position_prev_pan)*p;//2*atan(displacement.first+position_prev[0]/2*physical_width)*0.01 ;
				cout << " sent" << endl; 
			//}
			cout << "Speed2 is: " << abs(ceil(sin(displacement.second*0.000727220522)*1000)/10000 + position_prev_pan) << endl; 

			//if(abs(ceil(sin(displacement.second*0.000727220522)*1000)/10000 + position_prev_pan)>= 0.1)
			//{	
				vel[1] = 0.1;//abs(ceil(sin(displacement.second*0.000727220522)*1000)/1000 + position_prev_pan)*p;
				cout << " sent" << endl; 
			//}	
		
       
			ms.position = pos;
			ms.velocity = vel;
			ROS_INFO_STREAM("pan: "<<pos[0]);
			ROS_INFO_STREAM("pan_prev: " << position_prev_pan);
			ROS_INFO_STREAM("pan vel: " << abs(pos[0])) ;
			ROS_INFO_STREAM("prev Pan Vel: " << velocity_prev_pan);
			ROS_INFO_STREAM("tilt: "<<pos[1]);
			ROS_INFO_STREAM("tilt_prev: " << position_prev_tilt);
			ROS_INFO_STREAM("tilt vel: " << abs(pos[1]));
			ROS_INFO_STREAM("prev tilt Vel: " << velocity_prev_tilt);
			facedetect_pub.publish(ms);
			
		}
			flip(mask,mask,1);
			imshow("Tracking", image);
			//imshow("Mask",mask);
			waitKey(1);

		
    }
	

}
  //void ImageConverter::imageDetect(const sensor_msgs::ImageConstPtr& msg)
  //{
	 //facedetect_pub = nh_.advertise<sensor_msgs::JointState>("/ptu/cmd", 1);
	 //sub = nh_.subscribe("/joint_states",1,&ImageConverter::chatterCallback,this);  
	 //cv_bridge::CvImagePtr cv_ptr;
    //try
    //{
      //cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
    //}
    //catch (cv_bridge::Exception& e)
    //{
      //ROS_ERROR("cv_bridge exception: %s", e.what());
      //return;
    //}
    //sensor_msgs::JointState ms;
	////cout << "I am inside" << endl; 
	////frame = cv_ptr->image;
	////cout << "I am out" << endl;
	//image_pub_.publish(cv_ptr->toImageMsg()); 
	//displacement = detectAndDisplay(cv_ptr->image);
	//// Detect and outputs next position to PTU

	//if((abs(pos[0]-position_prev_pan) < 0.100))
	//{
		//pos[0] = ceil(sin(displacement.first*0.000727220522)*1000)/1000 + position_prev_pan;
	//}
	//if((abs(pos[1]-position_prev_tilt) < 0.100))
	//{
		//pos[1] = ceil(sin(displacement.second*0.000727220522)*1000)/1000 + position_prev_tilt;
	//}
		
	//ms.position = pos;
	//vel[0] = 0.1;//abs(pos[0]);//2*atan(displacement.first+position_prev[0]/2*physical_width)*0.01 ;
	//vel[1] = 0.1;//abs(pos[1]);
	//ms.velocity = vel;
	//ROS_INFO_STREAM("pan: "<<pos[0]);
	//ROS_INFO_STREAM("pan_prev: " << position_prev_pan);
	//ROS_INFO_STREAM("Subtracted: " <<abs(pos[0]-position_prev_pan));
	//ROS_INFO_STREAM("tili: "<<pos[1]);
	//ROS_INFO_STREAM("tilt_prev: " << position_prev_tilt);
	//ROS_INFO_STREAM("Subtracted: " <<abs(pos[1]-position_prev_tilt));
	//facedetect_pub.publish(ms);

    //// Update GUI Window
	//cv::imshow(OPENCV_WINDOW, cv_ptr->image);
   
    //// Output modified video stream
	//image_pub_.publish(cv_ptr->toImageMsg());

	//ROS_WARN_STREAM("OUT of if"); 
	//ros::spinOnce();
	

  //}
 

void ImageConverter::chatterCallback(const sensor_msgs::JointState::ConstPtr& msg)
   {	
	 position_prev_pan 	= (msg->position[0]);
	 position_prev_tilt = (msg->position[1]);
	 velocity_prev_pan 	= (msg->velocity[0]);
	 velocity_prev_tilt = (msg->velocity[1]);
	//ROS_INFO("Tilt moves to: %f", msg->position[1]);
	//ROS_INFO("Pan Velocity: %f", msg->velocity[0]);
	//ROS_INFO("Tilt Velocity: %f", msg->velocity[1]);
   }
