#pragma once

#include <string>
#include <tuple>

#include "Relation.hpp"

namespace sr2tr {

class Reader {
   public:
    static std::tuple<Relation, std::vector<std::string>> Read_file(
        const std::string &file_name);

   private:
    static std::vector<std::pair<int32_t, int32_t>>
    Read_column_name_with_error_list(
        const std::vector<std::string> &column_names);

    static void Fill_attribute_names(
        const std::vector<std::string> &column_names,
        const std::vector<std::pair<int, int>> &column_name_with_error_list,
        std::vector<std::string> &attribute_names);

    static void Fill_relation(
        const std::vector<double> &line_values,
        const std::vector<std::pair<int, int>> &column_name_with_error_list,
        Relation &relation);
};

}  // namespace sr2tr