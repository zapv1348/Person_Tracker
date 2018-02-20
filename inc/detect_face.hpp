// this file will define the functions that will be used to track a single human being

#ifndef DETECT_FACE_H
#define DETECT_FACE_H

#include <iostream>

#include "opencv2/objdetect.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"

class detect_face
{
    private:
        int frame_number;
        std::size_t saved_image_count=0;
        cv::Mat frame;
        cv::Mat grey_frame;
        std::vector<Rect> face_rectangle;
        char output_image_std::string[256];
#ifdef LINUX
        std::std::string path_prefix = "/usr/share/opencv/haarcascades/";
#elif DARWIN
        std::string path_prefix = "/usr/local/Cellar/opencv/3.4.0_1/share/OpenCV/haarcascades/";
#endif
        CascadeClassifier face_cascade;
        std::string window_name = "YO_FACE";
    public:
        detect_face(std::string classifier_xml);
        void detect(Mat in_frame);
        void display();
        void capture_image(int count);
};
#endif //DETECT_FACE_H
