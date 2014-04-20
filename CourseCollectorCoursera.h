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

tm constructDate(int d, int m, int y);

using namespace web;
using namespace web::http;
using namespace web::http::client;

class CourseraCourseCollector : public ICourseCollector{

    public:
        CourseraCourseCollector(std::shared_ptr<DBWriter> dbWriter);
        virtual ~CourseraCourseCollector(){};
        virtual void run() /* throw() */;
    private:
        void buildNewSessionAbdBuild(const json::value& val);

        pplx::task<void> run_();
        pplx::task<void> collectSessions();

        std::vector<std::shared_ptr<Session>> collectedSessions_;

        const char* sessionRequest(){
            return "https://api.coursera.org/api/catalog.v1/sessions?fields=id,courseId,name,startDay,startMonth,startYear";
        }

    std::shared_ptr<DBWriter> dbWriter_;
};



}
#endif // COURSERACOURSECOLLECTOR_H
