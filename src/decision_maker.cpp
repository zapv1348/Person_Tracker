#include "decision_maker.hpp"

using namespace std;

project_Dispatcher::project_Dispatcher(){
    capture_copy sup(5);
    //it is annoying it doesn't work this way
    thread super([=] {return std::thread(sup.loop_for_Frame())});
}
