#ifndef MOOC_STRUCTS_H
#define MOOC_STRUCTS_H

#include <ctime>
#include <string>
#include <list>
#include <memory>
#include <boost/noncopyable.hpp>


namespace steven {

    struct University{
            std::int32_t id;
            std::string name;
            std::string shortName;
            std::string homeLink;
            std::string website;
    };

    struct Category{
            std::int32_t id;
            std::string name;
    };

    struct Course{
            std::int64_t id;
            std::string shortName;
            std::string name;
            std::string language;
            std::string smallIcon;
            std::string recommendedBg;
            std::string aboutTheCourse;
            std::vector<int> categories;
            std::vector<int> universities;
    };

    struct Instructor{
            std::int32_t id;
            std::string firstName;
            std::string lastName;
            std::string title;
            std::string photo;
    };


    struct Session{
        std::int64_t courseId;
        std::int64_t id;
        std::string homeLink;
        struct tm startDate;
        std::vector<int> instructors;
    };



}

#endif // MOOC_STRUCTS_H
