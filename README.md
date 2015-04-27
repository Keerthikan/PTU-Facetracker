# PTU-Facetracker

This repository will contain my the work done on my Bachelor on creating a application capable of tracking the movement of a face and convert them into proper movements for the PTU system. 

PTU - Flir PTU D48E => Controlled using ROS node: http://wiki.ros.org/flir_ptu_driver


Face-tracking mechanishm: '\t'
The program starts by using Cascade Classifiers to detect Faces using the HaarCascades. 
After a Face a has been detected  the user press 'y' to enter the next stage. 
A ROI will be created of the Face which in the next stage will be used to find goodFeaturesToTrack.
These features are then using Lukas-kanade to used track the movement of the face. 
Lukas kanade drifting issue  tries to be minimized by keeping Features used for tracking close to each other. 

Controller: Is at moment a simple P-controller => no transfer function has been determined yet :(


More info will be added later :) 
Enjoy.
