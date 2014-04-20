#include "dbClient.h"

namespace steven{

mongo::Date_t convert(const boost::posix_time::ptime& pt)
{
    boost::posix_time::ptime epoch(boost::gregorian::date(1970,boost::date_time::Jan,1));
    boost::posix_time::time_duration d = pt - epoch;
    return mongo::Date_t(d.total_milliseconds());
}

DBWriter::DBWriter(std::shared_ptr<mongo::DBClientConnection> dbConnection)
    :conn_(dbConnection){

}

DBWriter::~DBWriter()
{

}

void DBWriter::addSessions(const std::vector<std::shared_ptr<Session>>& sessions)
{
    std::for_each(std::begin(sessions), std::end(sessions), [&](const std::shared_ptr<Session>& session){

        // construct start date
        auto tTime = std::mktime(&session->startDate);
        auto ptime = boost::posix_time::from_time_t(tTime);
        mongo::Date_t  dt = convert(ptime);


        mongo::BSONObj p = BSON( "csID" << session->id <<
                                 "ccID" << session->courseId <<
                                 "hl" << session->homeLink <<
                                 "sd" << dt);


        conn_->update("steven.sessions",
                      QUERY("csID" << session->id),
                      p, true, false);

        std::string err = conn_->getLastError();
        if(!err.empty()){
            std::cout << "error: " << err;
        }
    });
}



}
