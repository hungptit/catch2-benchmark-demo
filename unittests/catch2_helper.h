#pragma once

#include <ostream>
#include <set>
#include <string>
#include <tuple>

namespace unittests
{
    struct Person
    {
        std::string first_name;
        std::string last_name;
        int age;
    };

    bool operator==(const Person& lhs, const Person& rhs)
    {
        return std::tie(lhs.first_name, lhs.last_name, lhs.age) ==
               std::tie(rhs.first_name, rhs.last_name, rhs.age);
    }

    std::ostream& operator<<(std::ostream& os, const Person& person)
    {
        os << "{\"first_name\":\"" << person.first_name;
        os << "\",\"last_name\":\"" << person.last_name;
        os << "\",\"age\":" << person.age << "}";
        return os;
    }
}
