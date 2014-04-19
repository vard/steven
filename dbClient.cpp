#include "dbClient.h"

namespace steven{

DBWriter::DBWriter(std::shared_ptr<mongo::DBClientConnection> dbConnection)
    :conn_(dbConnection){

}

DBWriter::~DBWriter()
{

}

void DBWriter::addSessions(const std::vector<std::shared_ptr<Session>>& sessions)
{
    std::for_each(std::begin(sessions), std::end(sessions), [&](const std::shared_ptr<Session>& session){
        mongo::BSONObj p = BSON( "sId" << session->id << "hl" << session->homeLink);

        conn_->insert("steven.sessions", p);
    });
}



}
