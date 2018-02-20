#include "capture_copy.hpp"
#include "detect_face.hpp"
#include <thread>
#include <vector>

using namespace std;

/** The idea is that this class will act as a main loop
 * that means it must maintain all threads that will be launched
 * it must also decide shich threads need to be launched
 */

class project_Dispatcher{
    public:
        project_Dispatcher();
};
