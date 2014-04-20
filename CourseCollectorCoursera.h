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
        virtual ~CourseraCourseCollector(){}
        virtual void run() /* throw() */;
    private:
        void buildNewSessionAndInsert(const json::value& val);
        void buildNewCourseAndInsert(const json::value& val);
        void buildNewCategoryAndInsert(const json::value& val);
        void buildNewUniversityAndInsert(const json::value& val);
        void buildNewInstructorAndInsert(const json::value& val);

        pplx::task<void> collectSessions();
        pplx::task<void> collectCourses();
        pplx::task<void> collectCategories();
        pplx::task<void> collectUniversities();
        pplx::task<void> collectInstructors();

        std::vector<std::shared_ptr<Session>> collectedSessions_;
        std::vector<std::shared_ptr<Course>> collectedCourses_;
        std::vector<std::shared_ptr<Category>> collectedCategories_;
        std::vector<std::shared_ptr<University>> collectedUniversities_;
        std::vector<std::shared_ptr<Instructor>> collectedInstructors_;

        const char* sessionRequest(){
            return "https://api.coursera.org/api/catalog.v1/sessions?fields=id,courseId,name,startDay,startMonth,startYear&includes=instructors";
        }

        const char* coursesRequest(){
            return "https://api.coursera.org/api/catalog.v1/courses?fields=id,shortName,name,language,smallIcon,recommendedBackground,aboutTheCourse,instructor&includes=categories,universities,instructors";
        }

        const char* categoriesRequest(){
            return "https://api.coursera.org/api/catalog.v1/categories?fields=id,name";
        }

        const char* universitiesRequest(){
            return "https://api.coursera.org/api/catalog.v1/universities?fields=id,name,homeLink,website";
        }

        const char* instructorsRequest(){
            return "https://api.coursera.org/api/catalog.v1/instructors?fields=id,photo,firstNme,lastName";
        }


        std::shared_ptr<DBWriter> dbWriter_;
};



}
#endif // COURSERACOURSECOLLECTOR_H
