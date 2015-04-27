#include<ros/ros.h>
#include"sensor_msgs/Image.h"

//sensor_msgs::Image res;
void chatterCallback(const sensor_msgs::Image::ConstPtr& msg)
{ 		ROS_INFO_STREAM("hola");
		ROS_INFO_STREAM("Number of rows: " << msg->height);
		ROS_INFO_STREAM("Number of Collums: "<< msg->width);
		ROS_INFO_STREAM("Full row lenght in bytes: "<<  msg->step);
		ROS_INFO_STREAM(msg->encoding);
		//int data[msg->step][msg->height][3];
	//for(int i = 0; i < msg->step ; i++){
		//for(int j = 0; j < msg->height ; j++){
				//for(int k = 0; k< 3; k++){
					
					//data[i][j][k] = data[i*j];
					//data[i][j][k] = data[i*j];
					//data[i][j][k] = data[i*j];
					//ROS_INFO_STREAM( msg->data[i]);
				//}
		//}
	//}
}



int main(int argc, char** argv)
{

 	ros::init(argc, argv, "bumsub");
	ros::NodeHandle j;
	ROS_INFO_STREAM("HOLA Sj");
	ros::Subscriber sub = j.subscribe("/bumblebeePTU/left/image_rect_color",1,chatterCallback);
	
	ros::spin();

}
