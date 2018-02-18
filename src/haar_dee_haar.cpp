#include "haar_dee_haar.hpp"
#include "stdio.h"

#include "opencv2/highgui.hpp"

using namespace std;
using namespace cv;


//The idea will be to run a thread with this class which just captures frames and returns the current one
//for now, it is just going to read
capture_copy::capture_copy(){
    capture.open(0);
    if(!capture.isOpened())
    {
        cout <<  "YO CONNECT A CAMERA FOOL" << endl;
        throw std::invalid_argument( "or it sucks and can't find it");
    }
}

Mat capture_copy::grab_frame(){
    capture.read(current_frame);
    count++;
    return current_frame;   
}

    //currently have to call this for every frame when you want to detect a face.
detect_face::detect_face(string classifier_xml){
    if(!face_cascade.load(path_prefix+classifier_xml))
    {
        cout << "WTF, couldn't load the face cascade" << endl;
        throw std::invalid_argument( "Probably doesn't have the right file location" );;
    } 
}
void detect_face::detect(Mat in_frame){
    frame=in_frame;
    cvtColor(frame, grey_frame, COLOR_BGR2GRAY);
    equalizeHist(grey_frame, grey_frame);

    face_cascade.detectMultiScale(grey_frame, face_rectangle, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30,30));
}   

//just puts it on the screen
void detect_face::display(){
    Mat dummy_frame=this->frame.clone();
    for (size_t i = 0; i< face_rectangle.size(); i++){
        Point topleft (face_rectangle[i].x,face_rectangle[i].y);
        Point botright(face_rectangle[i].x+face_rectangle[i].width,face_rectangle[i].y+face_rectangle[i].height);
        rectangle( dummy_frame, topleft, botright, Scalar( 255, 0, 255 ), 1, 8, 0 );
    }

    imshow(window_name, dummy_frame);
    waitKey(30);
}

//will store the image
void detect_face::capture_image(int count){
    Mat cropped_image;
    if ((face_rectangle.size()==1)&&(!(count%20))){
        cropped_image=frame(face_rectangle[0]);
        sprintf(output_image_string,"./training_data/data_%d.png",(int)saved_image_count);
        imwrite(output_image_string,cropped_image);
        saved_image_count++;
        if(30<saved_image_count) saved_image_count=0;
    }
}

#ifdef TEST
//#if 1
int main( void )
{
    capture_copy sup;
    detect_face alt2("haarcascade_frontalface_alt2.xml");
    //detect_face alt_tree("haarcascade_frontalface_alt_tree.xml");
    //detect_face alt("haarcascade_frontalface_alt.xml");
    //detect_face default("haarcascade_frontalface_default.xml");
    //detect_face profileface("haarcascade_profileface.xml");  
    while(1){
        alt2.detect(sup.grab_frame());
        alt2.display();
        alt2.capture_image(sup.count);
    }
}
#endif
