#include <thread>
#include <vector>


/** The idea is that this class will act as a main loop
 * that means it must maintain all threads that will be launched
 * it must also decide shich threads need to be launched
 */

class project_Dispatcher{
    private: 
        std::thread main_dispatch;
        std::vector<std::thread> workers;
    public:
        project_Dispatcher();
};
