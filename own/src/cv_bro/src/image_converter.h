#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "sensor_msgs/JointState.h"
#include "facedetect.h"
#include <cmath>

  const int MAX_COUNT = 500;
  const int Outlierthreshold = 0.01;
  int window = 100;
  double qualitylevel = 0.001;
  TermCriteria termcrit(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS, 20, 0.03);
  Size subPixWinSize(10,10),winSize(31,31);

using namespace cv;
using namespace std;

static const std::string OPENCV_WINDOW = "Image window";


class ImageConverter
{
  ros::NodeHandle nh_;
  image_transport::ImageTransport it_;
  image_transport::Subscriber image_sub_;
  image_transport::Publisher image_pub_;
  std::vector<double> pos;
  std::vector<double> vel;
  double position_prev_pan;
  Mat ROI;
  double position_prev_tilt;
  double velocity_prev_pan;
  double velocity_prev_tilt;
  pair<double,double> displacement;
  ros::Subscriber sub;
  ros::Publisher facedetect_pub;
  Rect face;
  bool state;
  bool reinit;
  bool redetect;
  Point2f point;
  Mat gray, prevGray, image,test;
  int frames;
  vector<Point2f> points[2];
  vector<Point2f> point_final;
  vector<Point2f> goodFeatures;
  CascadeClassifier frontalface_alt2;
  CascadeClassifier frontal_alt;
  CascadeClassifier frontal_alt_tree;
  CascadeClassifier frontal_face;
  Point center_of_frame;
  Point center_of_frame_small;
  static uint64_t c;
  RotatedRect ka;
  Mat smallIMG;
  Mat ROI_IMAGE;
  Point2f backup_center;
  Point2f backup_center2;
  Point punkt2;
  bool sendCommands;

  int errorCnt;

public:
	  void chatterCallback(const sensor_msgs::JointState::ConstPtr& msg);
	  ImageConverter();
	  ~ImageConverter();
	  void imageDetect(const sensor_msgs::ImageConstPtr& msg);
	  Point normCrossCorrelation(Mat imgI, Mat imgJ,vector<Point2f> points1, vector<uchar> status, int method);


};
