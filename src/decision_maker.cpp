#include "decision_maker.hpp"

project_Dispatcher::project_Dispatcher(){
    capture_copy sup(5);
    main_dispatch=sup.wrap_lff();

}
