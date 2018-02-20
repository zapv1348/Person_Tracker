// this file will define the functions that will be used to track a single human being

#ifndef CAPTURE_COPY_H
#define CAPTURE_COPY_H

#include <iostream>
#include <thread>
#include "semaphore.hpp"
#include "opencv2/objdetect.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"

class capture_copy
{
    private:
        VideoCapture capture;
        Mat current_frame;
        uint32_t sig_count;
    public:
        semaphore signal;
        capture_copy(uint32_t signal_count);
        void loop_for_Frame();
        std::thread wrap_lff();
        cv::Mat grab_frame();
};
#endif //CAPTURE_COPY_H
