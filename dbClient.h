#ifndef DBCLIENT_H
#define DBCLIENT_H

#include "mongo/client/dbclient.h"

#include <vector>
#include "boost/noncopyable.hpp"
#include "mooc_structs.h"


namespace steven{

class DBWriter : private boost::noncopyable{
    public:
        DBWriter(std::shared_ptr<mongo::DBClientConnection> dbConnection);
        virtual ~DBWriter();

        virtual void addSessions(const std::vector<std::shared_ptr<Session>>& sessions) /* throw() */;
        virtual void addCourses(const std::vector<std::shared_ptr<Course>>& courses) /* throw() */;
        virtual void addCategories(const std::vector<std::shared_ptr<Category>>& categories) /* throw() */;


    private:
        std::shared_ptr<mongo::DBClientConnection> conn_;


};

}
#endif // DBCLIENT_H
