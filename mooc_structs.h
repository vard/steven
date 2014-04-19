#ifndef MOOC_STRUCTS_H
#define MOOC_STRUCTS_H

#include <ctime>
#include <string>
#include <list>
#include <memory>
#include <boost/noncopyable.hpp>


namespace steven {

    struct University{
            std::string name;
            std::string shortName;
            std::string description;
            std::string homeLink;
            std::string webSite;
    };

    struct Category{
            std::string name;
            std::string shortName;
            std::string description;
    };

    struct Course{
            std::string shortName;
            std::string name;
            std::string language;
            std::string aboutTheCourse;
            std::list<Category>categories;
    };

    struct Instructor{
            std::string firstName;
            std::string lastName;
            std::string title;
            std::string photoUrl;
            std::string photoUrl150;
    };


    struct Session{
        std::int64_t id;
        std::string homeLink;
        tm startDate;
        Course course;
        std::list<Instructor> instructors;
    };



}

#endif // MOOC_STRUCTS_H
