// stl headers
#include <iostream>
#include "dbClient.h"
#include "mooc_structs.h"
#include "CourseCollectorCoursera.h"


int main() {
    try {
        // create connection, writer, course collectors and tun them all
        std::shared_ptr<mongo::DBClientConnection> conn = std::make_shared<mongo::DBClientConnection>();
        conn->connect("localhost");
        std::shared_ptr<steven::DBWriter> dbWriter = std::make_shared<steven::DBWriter>(conn);

        std::vector<std::shared_ptr<steven::ICourseCollector>> collectors;
        collectors.push_back(std::make_shared<steven::CourseraCourseCollector>(dbWriter));

        std::for_each(std::begin(collectors), std::end(collectors), [](std::shared_ptr<steven::ICourseCollector>& collector){
            collector->run();
        });

    } catch( const mongo::DBException &e ) {
        std::cout << "caught " << e.what() << std::endl;
    }
    return EXIT_SUCCESS;
}




