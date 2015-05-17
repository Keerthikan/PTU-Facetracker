# PTU-Facetracker

This repository will contain my work related to my bachelor thesis.
The goal of the thesis is to create an application capable of detection a face, and track its movement such that a PTU is capable of keeping it at the center of the frame. 

PTU - Flir PTU D48E => Controlled using ROS node: http://wiki.ros.org/flir_ptu_driver


Face-tracking mechanishm: 

Facetracking/detection is divided into two states. 

1. state -  Face detection. 

The Facedetection is done using Haarcascades.  
The program tries to detect find faces using Haar classifiers which has been trained using Adaboost. 
When a face has been detected, the user then tells the program that it has been detected by pressing the letter 'y'. 
(This is redundant, and will be removed in the final version). 
As the user confirms, a Rect will be created around the location of the face, which will be given to the next state. 

2. state - Face tracking.

This State used the Rect which it has received from state 1, and create a mask, such that the face the is only being analysed. 
Before tracking can be initialized GoodFeatures will be found using Shi-Thomasi corner detection approach. 
These corner are then fed to Lukas Kanade Optical flow, which does the tracking. 

A known issue using the Lukas Kanade optical flow it is known to drift. 
To overcome this issue different strategies has been used applied to keep the drifting as minimum as possible, and relocate the mask, when certain criterias has been met. 
Strategies such as Foward  - Backward error estimation, Simple statistics and SURF - Speeded Up Robust Features. 


Controller: Is at moment a simple P-controller => no transfer function has been determined yet :(


More info will be added later :) 
Enjoy.
