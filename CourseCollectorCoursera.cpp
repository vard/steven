#include "CourseCollectorCoursera.h"

namespace steven{

CourseraCourseCollector::CourseraCourseCollector(std::shared_ptr<DBWriter> dbWriter)
    :dbWriter_(dbWriter)
{

}

void CourseraCourseCollector::run()
    {
    collectSessions().wait();
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

        collectedSessions_.push_back(session);
    } catch (const std::exception& ex){
        std::cout << "caught exception: " << ex.what() << std::endl;
    }
}

void CourseraCourseCollector::buildNewCourseAndInsert(const json::value& val)
{

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

}

tm constructDate(int d, int m, int y)
{
    tm date;
    return date;
}

}
