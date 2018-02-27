# Person Tracker
### Zachary Vogel

## Introduction
The goal of this project is to create a system which gives an accurate estimate of the position of a person relative to a camera for a KNOWN individual. This includes registering said individual in a simple database, preferabbly through a GUI, so the application can detect that person in the future. The estimation system should work without making too many assumptions about the position of the camera or individual.

## Tools
This project will be written in C++ and Python because those languages have support for opencv and numpy. The vision system will be done in C++ and the mathematical estimation in Python. The main key technologies are:
* Facial Recognition (for registering individuals and detecting known individuals)
* Feature Tracking (for tracking feature points of a certain individual)
* State Estimator (for estimating the relative position of the individual and accounting for noise)
* Interface (for using this tool)

## Current Work
* Just got the first couple of classes written out in a single file
    * This uses the haar cascade classifier to detect a persons face and capture images on that face
    * TODO: need to add threads that use all the basic facial classifier for better capture of training data
    * Those faces will be used for training data below
* Probably need to move their definitions to a header
* Need to figure out how to use Convolutional Neural Networks for training

## Step by step guide (theoretically)
These are the very important steps to making the robot detect you as an individual
1. Walk up to robot
1. Say hello to robot (robot doesn't actually have a microphone, but it makes it feel good)
1. Begin registration with robot (probably by pressing a button)
    * Registration involves detecting your face and taking pictures so we can train the robot to detect only your face (YOUR FACE)
    * That means if there are multiple people in the shot it will disregard your face
    * Multiple lighting conditions and facial angles are ideal
    * also need to take photos of the whole body
1. Once the robot has taken enough photos it will drive around in a circle indicating it has registered you (maybe just put a speaker on it)
1. With training completed, the robot now will detect you and follow you around
    * This involves detecting face, associating a body of known height with said face and then getting distance
    * once we have distance very fancy controls algorithms will allow the robot to follow you around
