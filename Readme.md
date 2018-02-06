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

## TBD
More to come
