//
//  main.cpp
//  facedetect
//
//  Created by Keerthikan Ratnarajah on 30/01/15.
//  Copyright (c) 2015 Keerthikan Ratnarajah. All rights reserved.
//
#include <ros/ros.h>
#include <iostream>
#include <string>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/video/tracking.hpp"
#include <opencv2/ml/ml.hpp>


using namespace cv;
using namespace std;



//String face_cascade_XML = "/usr/share/opencv/haarcascades/haarcascade_frontalface_alt.xml";



////detectAndDisplay - displacement
//Rect detectAndDisplay( Mat frame )
//{	
	//vector<Rect> faces(1);
	//Point center_of_frame(frame.size().width/2,frame.size().height/2);
	//pair<Point, Point> corners;
	//pair<double,double> displacement;
	//double displacement_pixel_x;
	//double displacement_pixel_y;
	//pair<Rect, bool> response;
		
			//if (frame.type()!= 8) {
				//cvtColor(frame, frame, CV_8U);
			//}
    
	////-- 1. Load the cascades
			//if( !face_cascade.load( face_cascade_XML ) ){
				//cout << "Cascade Error" << endl;
			//};
    
			//circle(frame, center_of_frame, 1, CV_RGB(0,255,255),8,8,0);
    
	////-- Detect faces
			//face_cascade.detectMultiScale( frame, faces, 1.1, 2, 0, Size(100, 100) );
			
			//for( int i = 0; i<faces.size() ; i++)
			//{
				//Point center_position_of_face((faces[i].br().x+faces[i].tl().x)/2,(faces[i].tl().y+faces[i].br().y)/2);
				//Point corner_1(faces[i].br().x,faces[i].tl().y);
				//Point corner_2 = faces[i].tl();
				//Point corner_3 = faces[i].br();
				//Point corner_4(faces[i].tl().x,faces[i].br().y);
				//rectangle(frame, faces[i], CV_RGB(0,255,0),4,8,0);
				//circle(frame, center_position_of_face, 8, CV_RGB(128,128,128),8,8,0);
				//circle(frame, corner_1, 1, CV_RGB(128,128,128),8,8,0);
				//circle(frame, corner_2, 1, CV_RGB(128,128,128),8,8,0);
				//circle(frame, corner_3, 1, CV_RGB(128,128,128),8,8,0);
				//circle(frame, corner_4, 1, CV_RGB(128,128,128),8,8,0);
				//line(frame, center_position_of_face, center_of_frame, CV_RGB(0,200,0),1,8);
				////displacement_pixel_x = (center_position_of_face.x-center_of_frame.x);
				////displacement_pixel_y = (center_position_of_face.y-center_of_frame.y);

			//}
       
		//flip(frame, frame, 1);
		//imshow("Facedetection", frame);
		//return faces.back();

//}


//pair<double, double> track(Rect face, Mat frame){
    //Mat hsv, hue, hist, mask, backproj;
    //Rect trackWindow;
    //int hsize = 50;
    //float hranges[] = {0,180};
    //const float* phranges = hranges;
    //pair<double, double> displacement;
    //double displacement_pixel_x;
    //double displacement_pixel_y;
    
    //Point Center_of_frame(frame.size().width/2, frame.size().height/2);
    //flip(frame, frame, 1);
    //cvtColor(frame, hsv, CV_BGR2HSV);
    //inRange(hsv, Scalar(0, 51, 89),Scalar(17, 140, 255), mask);
    //int ch[] = {0, 0};
    //hue.create(hsv.size(), hsv.depth());
    //mixChannels(&hsv, 1, &hue, 1, ch, 1);
    //Mat roi(hue, face), maskroi(mask, face);
    //calcHist(&roi, 1, 0, maskroi, hist, 1, &hsize, &phranges);
    //normalize(hist, hist, 0, 255, CV_MINMAX,-1,Mat());
    //calcBackProject(&hue, 1, 0, hist, backproj, &phranges);
    //backproj &= mask;
    //RotatedRect trackBox = CamShift(backproj, face, TermCriteria( CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 10, 1 ));
    //rectangle(frame, trackBox.boundingRect(), Scalar(0,0,255), 3, CV_AA);
    //Point center_position_of_face((trackBox.boundingRect().br().x+trackBox.boundingRect().tl().x)/2,(trackBox.boundingRect().tl().y+trackBox.boundingRect().br().y)/2);
    //circle(frame, center_position_of_face, 8, CV_RGB(128,128,128),8,8,0);
    //circle(frame, Center_of_frame, 8, CV_RGB(0, 255, 0),8,8,0);
    //line(frame, center_position_of_face, Center_of_frame, CV_RGB(0,200,0),1,8);
    //displacement_pixel_x = (center_position_of_face.x-Center_of_frame.x);
    //displacement_pixel_y = (center_position_of_face.y-Center_of_frame.y);
    ////string text = to_string(displacement_pixel_x)+','+to_string(displacement_pixel_y);
    ////putText(frame, text, center_position_of_face, FONT_HERSHEY_SIMPLEX, 1, CV_RGB(0, 200, 0));

    //imshow( "Result", frame );
    //imshow("mask", mask);
    
    //displacement = make_pair(displacement_pixel_x, displacement_pixel_y);
    //return displacement;
    
    
//}

////int main( int argc, const char** argv )
////{
    ////VideoCapture cam(0);
    ////Mat frame;
    ////Rect face;
    
    //////-- 2. Read the video stream
    ////if( !cam.isOpened() )
    ////{
        ////cout <<"Webcam error" << endl;
        ////return 0;
    ////}
    ////else
    ////{
        ////cout << "Is face detected ?" << endl;
        
        ////while(waitKey(1)!= 'y')
        ////{
            ////cam.read(frame);
            //////-- 3. Apply the classifier to the frame
            ////if( !frame.empty()){
                ////face = detectAndDisplay(frame);
            ////}
            
        ////}
        ////destroyAllWindows();
        
        ////while(waitKey(1)!= 'y')
        ////{
            ////cam.read(frame);
            //////-- 3. Apply the classifier to the frame
            ////if( !frame.empty()){
                ////cout << track(face,frame).first;
            ////}
            
        ////}
    ////}
    
    ////return 0;
////}
