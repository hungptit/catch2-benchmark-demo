#pragma once

#include <algorithm>
#include <vector>
#include <set>
#include <string>

namespace algorithm {
    std::vector<std::string> get_sorted_strings_using_map(const std::vector<std::string> &data){
        std::set<std::string> sorted_list(data.cbegin(), data.cend());
        return std::vector<std::string>(sorted_list.cbegin(), sorted_list.cend());;
    }
    std::vector<std::string> get_sorted_strings_using_sort(const std::vector<std::string> &data){
        std::vector<std::string> sorted_list(data.cbegin(), data.cend());
        std::sort(sorted_list.begin(), sorted_list.end());
        return sorted_list;
    }
}
