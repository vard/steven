#include "CourseCollectorCoursera.h"

namespace steven{

CourseraCourseCollector::CourseraCourseCollector(std::shared_ptr<DBWriter> dbWriter)
    :dbWriter_(dbWriter)
{

}

void CourseraCourseCollector::run()
{
    collectSessions().wait();
    collectCourses().wait();
    collectCategories().wait();
}

void CourseraCourseCollector::buildNewSessionAndInsert(const json::value& val)
{
    try{
        auto session = std::make_shared<Session>();
        session->id = val.at("id").as_integer();
        session->courseId = val.at("courseId").as_integer();
        session->homeLink = val.at("homeLink").as_string();
        //session->startDate = costructDate(val["startDay"], val["startMonth"], val["startYear"]);

        tm tmStruct;
        tmStruct.tm_sec = 0;
        tmStruct.tm_min = 0;
        tmStruct.tm_hour = 0;
        tmStruct.tm_mday = val.at("startDay").as_integer();
        tmStruct.tm_mon = val.at("startMonth").as_integer();
        tmStruct.tm_year = (val.at("startYear").as_integer() - 1900);
        tmStruct.tm_isdst = -1;

        session->startDate = tmStruct;

        auto instructors = val.at("links").at("instructors").as_array();
        std::for_each(instructors.begin(), instructors.end(), [&](const json::value& val){
            session->instructors.push_back(val.as_integer());
        });

        collectedSessions_.push_back(session);
    } catch (const std::exception& ex){
        std::cout << "caught exception: " << ex.what() << std::endl;
    }
}

void CourseraCourseCollector::buildNewCourseAndInsert(const json::value& val)
{
    try{
        auto course = std::make_shared<Course>();
        course->id = val.at("id").as_integer();
        course->shortName = val.at("shortName").as_string();
        course->language = val.at("language").as_string();
        course->smallIcon = val.at("smallIcon").as_string();
        course->recommendedBg = val.at("recommendedBackground").as_string();
        course->aboutTheCourse = val.at("aboutTheCourse").as_string();
        course->language = val.at("language").as_string();


        auto categories = val.at("links").at("categories").as_array();
        std::for_each(categories.begin(), categories.end(), [&](const json::value& val){
            course->categories.push_back(val.as_integer());
        });

        auto universities = val.at("links").at("universities").as_array();
        std::for_each(universities.begin(), universities.end(), [&](const json::value& val){
            course->universities.push_back(val.as_integer());
        });

        collectedCourses_.push_back(course);
    } catch (const std::exception& ex){
        std::cout << "caught exception: " << ex.what() << std::endl;
    }
}

void CourseraCourseCollector::buildNewCategoryAndInsert(const json::value& val)
{
    try{
        auto category = std::make_shared<Category>();
        category->id = val.at("id").as_integer();
        category->name = val.at("name").as_string();

        collectedCategories_.push_back(category);
    } catch (const std::exception& ex){
        std::cout << "caught exception: " << ex.what() << std::endl;
    }
}

pplx::task<void> CourseraCourseCollector::collectSessions()
{
    using namespace web;
    using namespace web::http;
    using namespace web::http::client;

    web::http::client::http_client client(sessionRequest());

    // Make the request and asynchronously process the response.
    return client.request(methods::GET).then([](http_response response) -> pplx::task<json::value>
    {
        if(response.status_code() == status_codes::OK)
        {
            return response.extract_json();
        }
         // Handle error cases, for now return empty json value...
        return pplx::task_from_result(json::value());
    })
    .then([&](pplx::task<json::value> previousTask)
    {
        try
        {
            const json::value& v = previousTask.get();
            //v.at("elements").at(0).serialize(std::cout);
             auto sessions = v.at("elements").as_array();
             std::for_each(std::begin(sessions), std::end(sessions), [&](json::value curVal){
                 buildNewSessionAndInsert(curVal);
                 curVal.serialize(std::cout);
                 std::cout << std::endl;
                 });

            this->dbWriter_->addSessions(collectedSessions_);
        }
        catch (const std::exception& e)
        {
            // Print error.
            std::wostringstream ss;
            ss << e.what() << std::endl;
            std::wcout << ss.str();
        }
    });
}

pplx::task<void> CourseraCourseCollector::collectCourses()
{
    using namespace web;
    using namespace web::http;
    using namespace web::http::client;

    web::http::client::http_client client(coursesRequest());

    // Make the request and asynchronously process the response.
    return client.request(methods::GET).then([](http_response response) -> pplx::task<json::value>
    {
        if(response.status_code() == status_codes::OK)
        {
            return response.extract_json();
        }
         // Handle error cases, for now return empty json value...
        return pplx::task_from_result(json::value());
    })
    .then([&](pplx::task<json::value> previousTask)
    {
        try
        {
            const json::value& v = previousTask.get();
             auto sessions = v.at("elements").as_array();
             std::for_each(std::begin(sessions), std::end(sessions), [&](json::value curVal){
                 buildNewCourseAndInsert(curVal);
                 curVal.serialize(std::cout);
                 std::cout << std::endl;
                 });

            this->dbWriter_->addCourses(collectedCourses_);
        }
        catch (const std::exception& e)
        {
            // Print error.
            std::wostringstream ss;
            ss << e.what() << std::endl;
            std::wcout << ss.str();
        }
});
}

pplx::task<void> CourseraCourseCollector::collectCategories()
{
    using namespace web;
    using namespace web::http;
    using namespace web::http::client;

    web::http::client::http_client client(categoriesRequest());

    // Make the request and asynchronously process the response.
    return client.request(methods::GET).then([](http_response response) -> pplx::task<json::value>
    {
        if(response.status_code() == status_codes::OK)
        {
            return response.extract_json();
        }
         // Handle error cases, for now return empty json value...
        return pplx::task_from_result(json::value());
    })
    .then([&](pplx::task<json::value> previousTask)
    {
        try
        {
            const json::value& v = previousTask.get();
             auto sessions = v.at("elements").as_array();
             std::for_each(std::begin(sessions), std::end(sessions), [&](json::value curVal){
                 buildNewCategoryAndInsert(curVal);
                 curVal.serialize(std::cout);
                 std::cout << std::endl;
                 });

            this->dbWriter_->addCategories(collectedCategories_);
        }
        catch (const std::exception& e)
        {
            // Print error.
            std::wostringstream ss;
            ss << e.what() << std::endl;
            std::wcout << ss.str();
        }
    });
}

tm constructDate(int d, int m, int y)
{
    tm date;
    return date;
}

}
