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

void CourseraCourseCollector::buildNewSessionAbdBuild(const json::value& val)
{
    auto session = std::make_shared<Session>();
    session->id = val.at("courseId").as_integer();
    session->homeLink = val.at("homeLink").as_string();
    //session->startDate = costructDate(val["startDay"], val["startMonth"], val["startYear"]);
    collectedSessions_.push_back(session);
}

    pplx::task<void> CourseraCourseCollector::run_()
    {
        collectSessions();

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
                    buildNewSessionAbdBuild(curVal);
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

tm constructDate(int d, int m, int y)
{
    tm date;
    return date;
}

}
