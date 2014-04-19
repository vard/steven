#ifndef ICOURSECOLLECTOR_H
#define ICOURSECOLLECTOR_H

#include <vector>
#include <memory>
#include "boost/noncopyable.hpp"

namespace steven {

class ICourseCollector : private boost::noncopyable{
    public:
        ICourseCollector(){}
        virtual ~ICourseCollector(){}
        virtual void run() = 0;
};



}
#endif // ICOURSECOLLECTOR_H
