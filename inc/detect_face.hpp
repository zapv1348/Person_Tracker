// this file will define the functions that will be used to track a single human being

#ifndef DETECT_FACE_H
#define DETECT_FACE_H

#include <iostream>

#include "opencv2/objdetect.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"

using namespace cv;
using namespace std;


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
        string path_prefix = "/usr/share/opencv/haarcascades/";
#elif DARWIN
        string path_prefix = "/usr/local/Cellar/opencv/3.4.0_1/share/OpenCV/haarcascades/";
#endif
        CascadeClassifier face_cascade;
        string window_name = "YO_FACE";
    public:
        detect_face(string classifier_xml);
        void detect(Mat in_frame);
        void display();
        void capture_image(int count);
};
#endif //DETECT_FACE_H
