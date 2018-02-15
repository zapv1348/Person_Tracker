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
