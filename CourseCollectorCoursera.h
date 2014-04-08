#ifndef COURSERACOURSECOLLECTOR_H
#define COURSERACOURSECOLLECTOR_H

#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <cpprest/json.h>
#include <iostream>
#include <sstream>

#include "ICourseCollector.h"

namespace steven{

class CourseraCourseCollector : public ICourseCollector{
    public:
        CourseraCourseCollector();
        virtual ~CourseraCourseCollector();
        virtual void run() /* throw() */;
    private:
        pplx::task<void> run_();

};



}
#endif // COURSERACOURSECOLLECTOR_H
