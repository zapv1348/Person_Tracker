#include "person_tracking.hpp"
#include <iostream>
#include "stdio.h"

#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/objdetect.hpp"

using namespace std;
using namespace cv;

string face_cascade_name = "/usr/share/opencv/haarcascades/haarcascade_frontalface_default.xml";
CascadeClassifier face_cascade;
string window_name = "YO FACE";

void detectAndDisplay(Mat frame){
    std::vector<Rect> faces;
    Mat frame_gray;
    cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );
    //-- Detect faces
    face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30, 30) );
    for ( size_t i = 0; i < faces.size(); i++ )
    {
        Point topleft (faces[i].x,faces[i].y);
        Point botright(faces[i].x+faces[i].width,faces[i].y+faces[i].height);
        rectangle( frame, topleft, botright, Scalar( 255, 0, 255 ), 1, 8, 0 );
        Mat faceROI = frame_gray( faces[i] );
    }
    //-- Show what you got
    imshow( window_name, frame );
}


#define TEST 1
#if TEST==1

int main( void )
{
    VideoCapture capture;
    Mat frame;
    //-- 1. Load the cascades
    if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading face cascade\n"); return -1; };
    //-- 2. Read the video stream
    capture.open( -1 );
    if ( ! capture.isOpened() ) { printf("--(!)Error opening video capture\n"); return -1; }
    while ( capture.read(frame) )
    {
        if( frame.empty() )
        {
            printf(" --(!) No captured frame -- Break!");
            break;
        }
        //-- 3. Apply the classifier to the frame
        detectAndDisplay( frame );
        char c = (char)waitKey(10);
        if( c == 27 ) { break; } // escape
    }
    return 0;
}


#endif
