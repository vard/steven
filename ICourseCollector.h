#ifndef ICOURSECOLLECTOR_H
#define ICOURSECOLLECTOR_H

#include "boost/noncopyable.hpp"

namespace steven {

class ICourseCollector : private boost::noncopyable{
    public:
        virtual ~ICourseCollector() = 0;
        virtual void run() = 0;
};

}
#endif // ICOURSECOLLECTOR_H
