#include "image_converter.cpp"


int main( int argc, char** argv )
{

   ros::init(argc, argv, "image_converter");
   ImageConverter ic;
   ros::spin();
   return 0;
}
