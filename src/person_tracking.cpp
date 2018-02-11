#include "person_tracking.hpp"
#include <iostream>
#include "stdio.h"

#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/objdetect.hpp"

using namespace std;
using namespace cv;


//The idea will be to run a thread with this class which just captures frames and returns the current one
//for now, it is just going to read
class capture_copy
{
private:
    VideoCapture capture;
    Mat current_frame;
    Mat old_frame;
public:
    int count=0;

    capture_copy(){
        capture.open(0);
        if(!capture.isOpened())
        {
            cout <<  "YO CONNECT A CAMERA FOOL" << endl;
            throw std::invalid_argument( "or it sucks and can't find it");
        }
    }
    Mat grab_frame(){
        capture.read(current_frame);
        count++;
        return current_frame;   
    }
};

class detect_face
{
private:
    int frame_number;
    size_t saved_image_count=0;
    Mat frame;
    Mat grey_frame;
    std::vector<Rect> face_rectangle;
    char output_image_string[256];
#ifdef LINUX
    string face_cascade_name = "/usr/share/opencv/haarcascades/haarcascade_frontalface_alt2.xml";
#elif DARWIN
    string face_cascade_name = "/usr/local/Cellar/opencv/3.4.0_1/share/OpenCV/haarcascades/haarcascade_frontalface_default.xml";
#endif

    CascadeClassifier face_cascade;
    string window_name = "YO FACE";

public:
    //currently have to call this for every frame when you want to detect a face.
    detect_face(){
        if(!face_cascade.load(face_cascade_name))
        {
            cout << "WTF, couldn't load the face cascade" << endl;
            throw std::invalid_argument( "Probably doesn't have the right file location" );;
        } 
    }
    void detect(Mat in_frame){
        frame=in_frame;
        cvtColor(frame, grey_frame, COLOR_BGR2GRAY);
        equalizeHist(grey_frame, grey_frame);

        face_cascade.detectMultiScale(grey_frame, face_rectangle, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30,30));
    }   

    //just puts it on the screen
    void display(){
        Mat dummy_frame=this->frame.clone();
        for (size_t i = 0; i< face_rectangle.size(); i++){
            Point topleft (face_rectangle[i].x,face_rectangle[i].y);
            Point botright(face_rectangle[i].x+face_rectangle[i].width,face_rectangle[i].y+face_rectangle[i].height);
            rectangle( dummy_frame, topleft, botright, Scalar( 255, 0, 255 ), 1, 8, 0 );
        }

        imshow(window_name, dummy_frame);
        waitKey(10);
    }

    //will store the image
    void capture_image(int count){
        Mat cropped_image;
        if ((face_rectangle.size()==1)&&(!(count%20))){
            cropped_image=frame(face_rectangle[0]);
            sprintf(output_image_string,"./training_data/data_%d.png",(int)saved_image_count);
            imwrite(output_image_string,cropped_image);
            saved_image_count++;
            if(30<saved_image_count) saved_image_count=0;
        }
    }
};

#define TEST 1
#if TEST==1

int main( void )
{
    capture_copy sup;
    detect_face foo;
    while(1){
        foo.detect(sup.grab_frame());
        foo.display();
        foo.capture_image(sup.count);
    }
}
#endif
