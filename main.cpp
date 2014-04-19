// stl headers
#include <iostream>

#include "dbClient.h"

#include "mooc_structs.h"
#include "CourseCollectorCoursera.h"


//// cpp rest api headers
//#include <cpprest/http_client.h>
//#include <cpprest/filestream.h>
//#include <cpprest/json.h>
//#include <iostream>
//#include <sstream>

//using namespace web;
//using namespace web::http;
//using namespace web::http::client;




//pplx::task<void> HTTPStreamingAsync()
//{
//    web::http::client::http_client client("https://api.coursera.org/api/catalog.v1/sessions?fields=courseId,startDay,startMonth,startYear");

//    // Make the request and asynchronously process the response.
//        return client.request(methods::GET).then([](http_response response) -> pplx::task<json::value>
//        {
//            if(response.status_code() == status_codes::OK)
//            {
//                return response.extract_json();
//            }

//            // Handle error cases, for now return empty json value...
//            return pplx::task_from_result(json::value());
//        })
//    .then([](pplx::task<json::value> previousTask)
//    {
//        try
//        {
//            const json::value& v = previousTask.get();
//            v.at("elements").at(0).serialize(std::cout);
//        }
//        catch (const std::exception& e)
//        {
//            // Print error.
//            std::wostringstream ss;
//            ss << e.what() << std::endl;
//            std::wcout << ss.str();
//        }
//    });

//    /* Sample output:
//    Server returned returned status code 200.
//    Content length is 63803 bytes.
//    */
//}


int main() {
    try {

        std::shared_ptr<mongo::DBClientConnection> conn = std::make_shared<mongo::DBClientConnection>();
        conn->connect("localhost");

        std::shared_ptr<steven::DBWriter> dbWriter = std::make_shared<steven::DBWriter>(conn);

        std::vector<std::shared_ptr<steven::ICourseCollector>> collectors;
        collectors.push_back(std::make_shared<steven::CourseraCourseCollector>(dbWriter));
        //steven::CourseraCourseCollector courseraCollector(dbWriter);
        //steven::ICourseCollector* collector(&courseraCollector);

        std::for_each(std::begin(collectors), std::end(collectors), [](std::shared_ptr<steven::ICourseCollector>& collector){
            collector->run();
        });

        //collector->run(sessions);
        //HTTPStreamingAsync().wait();


    } catch( const mongo::DBException &e ) {
        std::cout << "caught " << e.what() << std::endl;
    }
    return EXIT_SUCCESS;
}




