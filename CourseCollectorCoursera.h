#ifndef COURSERACOURSECOLLECTOR_H
#define COURSERACOURSECOLLECTOR_H

#include "dbClient.h"

#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <cpprest/json.h>
#include <iostream>
#include <sstream>


#include "ICourseCollector.h"

namespace steven{

class CourseraCourseCollector : public ICourseCollector{
    public:
        CourseraCourseCollector(std::shared_ptr<DBWriter> dbWriter);
        virtual ~CourseraCourseCollector(){};
        virtual void run() /* throw() */;
    private:
        pplx::task<void> run_();
        pplx::task<void> collectSessions();

        std::vector<Session> collectedSessions_;

        const char* sessionRequest(){
            return "https://api.coursera.org/api/catalog.v1/sessions?fields=courseId,startDay,startMonth,startYear";
        }

    std::shared_ptr<DBWriter> dbWriter_;
};



}
#endif // COURSERACOURSECOLLECTOR_H
