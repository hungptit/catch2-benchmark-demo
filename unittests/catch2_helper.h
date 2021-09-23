#pragma once

#include <set>
#include <tuple>
#include <string>
#include <ostream>

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
        return std::tie(lhs.first_name, lhs.last_name, lhs.age) == std::tie(rhs.first_name, rhs.last_name, rhs.age);
    }

    std::ostream& operator<<(std::ostream& os, const Person& person)
    {
        os << "{"
           << "\"first_name\":\"" << person.first_name << "\",\"last_name\":\"" << person.last_name
           << "\",\"age\":" << person.age << "}";
        return os;
    }
}
