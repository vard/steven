#include "dbClient.h"

namespace steven{

template<typename ElemType>
mongo::BSONArray bsonArrFromVector(const std::vector<ElemType>& vect){
    mongo::BSONArrayBuilder arrayBuilder;
    std::for_each(std::begin(vect), std::end(vect), [&](ElemType elem){
        arrayBuilder.append(elem);
    });
    return arrayBuilder.arr();
}

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


        auto instructors = bsonArrFromVector(session->instructors);


        mongo::BSONObj p = BSON( "csID" << session->id <<
                                 "ccID" << session->courseId <<
                                 "hl" << session->homeLink <<
                                 "sd" << dt <<
                                 "ins" << instructors);


        conn_->update("steven.sessions",
                      QUERY("csID" << session->id),
                      p, true, false);

        std::string err = conn_->getLastError();
        if(!err.empty()){
            std::cout << "error: " << err;
        }
    });
}

void DBWriter::addCourses(const std::vector<std::shared_ptr<Course> >& courses)
{
    std::for_each(std::begin(courses), std::end(courses), [&](const std::shared_ptr<Course>& course){

        auto categories = bsonArrFromVector(course->categories);
        auto universities = bsonArrFromVector(course->universities);


        mongo::BSONObj p = BSON("ccID" << course->id <<
                                "shNm" << course->shortName <<
                                "name" << course->name <<
                                "lang" << course->language <<
                                "smIc" << course->smallIcon <<
                                "rcBg" << course->recommendedBg <<
                                "abt" << course->aboutTheCourse <<
                                "cat" << categories <<
                                "uns" << universities

                                );





        conn_->update("steven.courses",
                      QUERY("ccID" << course->id),
                      p, true, false);

        std::string err = conn_->getLastError();
        if(!err.empty()){
            std::cout << "error: " << err;
        }
    });
}

void DBWriter::addCategories(const std::vector<std::shared_ptr<Category> >& categories)
{
    std::for_each(std::begin(categories), std::end(categories), [&](const std::shared_ptr<Category>& cat){

        mongo::BSONObj p = BSON( "ctID" << cat->id <<
                                 "name" << cat->name);

        conn_->update("steven.categories",
                      QUERY("ctID" << cat->id),
                      p, true, false);

        std::string err = conn_->getLastError();
        if(!err.empty()){
            std::cout << "error: " << err;
        }
    });
}

void DBWriter::addUniversities(const std::vector<std::shared_ptr<University> >& universities)
{
    std::for_each(std::begin(universities), std::end(universities), [&](const std::shared_ptr<University>& uni){

        mongo::BSONObj p = BSON( "cuID" << uni->id <<
                                 "name" << uni->name <<
                                 "hl" << uni->homeLink <<
                                 "webs" << uni->website);

        conn_->update("steven.universities",
                      QUERY("cuID" << uni->id),
                      p, true, false);

        std::string err = conn_->getLastError();
        if(!err.empty()){
            std::cout << "error: " << err;
        }
    });
}

void DBWriter::addInstructors(const std::vector<std::shared_ptr<Instructor> >& instructors)
{
    std::for_each(std::begin(instructors), std::end(instructors), [&](const std::shared_ptr<Instructor>& ins){

        // std::cout << "put instuctor " << ins->id << std::endl;
        mongo::BSONObj p = BSON( "ciID" << ins->id <<
                                 "phto" << ins->photo <<
                                 "fn" << ins->firstName <<
                                 "ln" << ins->lastName <<
                                 "ttle" << ins->title);

        conn_->update("steven.instructors",
                      QUERY("ciID" << ins->id),
                      p, true, false);

        std::string err = conn_->getLastError();
        if(!err.empty()){
            std::cout << "error: " << err;
        }
    });
}

} // namespace steven




