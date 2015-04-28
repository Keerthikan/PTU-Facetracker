//
//  main.cpp
//  templateMathing
//
//  Created by Keerthikan Ratnarajah on 28/04/15.
//  Copyright (c) 2015 Keerthikan Ratnarajah. All rights reserved.
//

#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;
Mat ROI;
Mat ROIS;

Point normCrossCorrelation(Mat imgI, Mat ROI/*,vector<Point2f> points1, vector<uchar> status,*/, int method)
{
    Mat res,rec1;
    Size size(307,230);
    //for(int i = 0; i <= points1.size(); i++)
   //{
        //if(status[i] == 1)
        //{
            //getRectSubPix(imgI,size,points1[i],rec1);
            matchTemplate(imgI, ROI, res, method);
            //cout << ((float *)(res.operator _IplImage().imageData))[0] << endl;
        //}
    //}
    normalize(res,res,0,1,NORM_MINMAX,-1,cv::Mat());
    double minVal,maxVal;
    Point minLoc,maxLoc;
    
    minMaxLoc(res,&minVal,&maxVal,&minLoc,&maxLoc,cv::Mat());
    
    cout << "new location: " << maxLoc << " Maxval: " << maxVal << endl;
    
    return minLoc;
}

Rect Facerecognizer(Mat &now_frame)
{

    ROI = imread("/Users/keerthikanratnarajah/PTU-Facetracker/templateMathing/sourceimg/man.jpg",CV_LOAD_IMAGE_GRAYSCALE);
    //cvtColor(now_frame, next, CV_BGR2GRAY);
    //equalizeHist(next,next);
    Point center_of_frame(now_frame.size().width/2,now_frame.size().height/2);
    circle(now_frame, center_of_frame, 1, CV_RGB(0,255,255),8,8,0);
    String face_cascade_XML = "/Users/keerthikanratnarajah/Downloads/opencv-master/data/haarcascades/haarcascade_frontalface_alt2.xml";
    CascadeClassifier face_cascade;
    vector<Rect> faces(1);
    if( !face_cascade.load( face_cascade_XML ) ){
        cout << "Cascade Error" << endl;
    };
    face_cascade.detectMultiScale( now_frame, faces, 1.1, 2, CASCADE_DO_CANNY_PRUNING, Size(300, 300) );
    
    if (!faces.empty()) {
        for( auto faces : faces)
        {
            Point center_position_of_face((faces.br().x+faces.tl().x)/2,(faces.tl().y+faces.br().y)/2);
            Point corner_1(faces.br().x,faces.tl().y);
            Point corner_2 = faces.tl();
            Point corner_3 = faces.br();
            Point corner_4(faces.tl().x,faces.br().y);
            rectangle(now_frame, faces, CV_RGB(0,255,0),4,8,0);
            circle(now_frame, center_position_of_face, 8, CV_RGB(128,128,128),8,8,0);
            circle(now_frame, corner_1, 1, CV_RGB(128,128,128),8,8,0);
            circle(now_frame, corner_2, 1, CV_RGB(128,128,128),8,8,0);
            circle(now_frame, corner_3, 1, CV_RGB(128,128,128),8,8,0);
            circle(now_frame, corner_4, 1, CV_RGB(128,128,128),8,8,0);
            line(now_frame, center_position_of_face, center_of_frame, CV_RGB(0,200,0),1,8);
            
        }
        
    }
    //flip(now_frame, now_frame, 1);
    imshow( "Facerecognizer", now_frame );
    ROIS = ROI(faces.back());
    return  faces.back();
}

int main(int argc, const char * argv[]) {
    std::cout << "Hello, World!\n";
    Mat frame;
    frame = imread("/Users/keerthikanratnarajah/PTU-Facetracker/templateMathing/sourceimg/man.jpg",CV_LOAD_IMAGE_GRAYSCALE);
    Rect face;
    while(waitKey(1) != 'y')
    {
        face = Facerecognizer(frame);
    }
    destroyAllWindows();
    Mat Source = imread("/Users/keerthikanratnarajah/PTU-Facetracker/templateMathing/sourceimg/man.jpg",CV_LOAD_IMAGE_GRAYSCALE);
    Point max = normCrossCorrelation(frame,ROI,CV_TM_CCOEFF_NORMED);
    circle(Source, max, 11, Scalar(0,0,255),8,2);
    imshow("template", ROIS);
    imshow("source", Source);
    waitKey();
    
    return 0;
}
