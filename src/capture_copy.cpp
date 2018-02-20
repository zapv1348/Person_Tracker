#include "capture_copy.hpp"
#include "stdio.h"

#include "opencv2/highgui.hpp"

using namespace cv;


//The idea will be to run a thread with this class which just captures frames and returns the current one
//for now, it is just going to read
capture_copy::capture_copy(uint32_t signal_count){
    sig_count=signal_count;
    capture.open(0);
    if(!capture.isOpened())
    {
        cout <<  "YO CONNECT A CAMERA FOOL" << endl;
        throw std::invalid_argument( "or it sucks and can't find it");
    }
}

//should be run in a thread
void capture_copy::loop_for_Frame(){
    while(1){
        //capture.read stalls till a new frame is ready
        capture.read(current_frame);
        //give signal to worker threads
        signal.give_Mult(sig_count);
        //wait for done
        while(!(signal.is_Done())); 
    }
}

thread capture_copy::wrap_lff(){
    return  std::thread([=] {loop_for_Frame();});
}


//used by other threads to grab image
//safe because updates to clone don't happen while worker threads are still working
Mat capture_copy::grab_frame(){
    return current_frame.clone();
}

#ifdef TEST
//#if 1
int main( void )
{

}
#endif
