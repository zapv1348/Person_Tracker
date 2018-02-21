#include "decision_maker.hpp"
#include "capture_copy.hpp"
#include "detect_face.hpp"
#include <string>

#define NUM_HAAR_DETECTORS 3


capture_copy * sup;
detect_face * face_det[NUM_HAAR_DETECTORS];


std::string detector_strings[NUM_HAAR_DETECTORS]={"haarcascade_frontalface_alt2.xml","haarcascade_frontalface_alt.xml","haarcascade_frontalface_default.xml"}; 

void detect_display_thread(detect_face * detector){
    while(1){
        //std::cout<<"got into detector thread\n";
        sup->signal.take();
        detector->detect(sup->grab_frame()); 
        detector->display(); 
    }
}

project_Dispatcher::project_Dispatcher(){
    sup=new capture_copy(NUM_HAAR_DETECTORS);
    for (int i=0;i<NUM_HAAR_DETECTORS;i++){
        face_det[i]=new detect_face(detector_strings[i]);
    }
    std::cout << "initialized detectors\n";
    main_dispatch=sup->wrap_lff();
    std::cout << "in capture loop\n";
    for (int i=0;i<NUM_HAAR_DETECTORS;i++){
        workers.emplace_back(std::thread([=] {detect_display_thread(face_det[i]);}));
    }
    while(1);
}
