#include "mooc_structs.h"
#include "CourseCollectorCoursera.h"

namespace steven{

    void CourseraCourseCollector::run()
    {
        run_().wait();
    }

    pplx::task<void> CourseraCourseCollector::run_()
    {

    }

}
