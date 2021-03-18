#include "sr2tr/Reader.hpp"

#include "reader/CSV_file_reader.hpp"

namespace sr2tr {
using namespace reader;

std::tuple<Relation, std::vector<std::string>> Reader::Read_file(
    const std::string &file_name) {
    Relation relation;
    std::vector<std::string> attribute_names;
    CSV_file_reader file_reader(file_name);
    std::vector<std::string> column_names = file_reader.get_columns();
    std::vector<std::pair<int, int>> column_name_with_error_list =
        Read_column_name_with_error_list(column_names);
    Fill_attribute_names(column_names, column_name_with_error_list,
                         attribute_names);

    std::vector<double> line_values = file_reader.get_line();
    while (!line_values.empty()) {
        Fill_relation(line_values, column_name_with_error_list, relation);
        line_values = file_reader.get_line();
    }
    return {relation, attribute_names};
}

std::vector<std::pair<int32_t, int32_t>>
Reader::Read_column_name_with_error_list(
    const std::vector<std::string> &column_names) {
    std::vector<std::pair<int32_t, int32_t>> column_name_with_error_list;
    for (uint32_t index_i = 0; index_i < column_names.size(); ++index_i) {
        static const std::string Error_prefix = "err_";
        const auto result =
            std::mismatch(Error_prefix.begin(), Error_prefix.end(),
                          column_names[index_i].begin());
        if (result.first == Error_prefix.end()) {
            continue;
        }
        const std::string column_name_with_error =
            Error_prefix + column_names[index_i];
        auto column_name_with_error_position = std::find(
            column_names.begin(), column_names.end(), column_name_with_error);
        int32_t index_j = -1;
        if (column_name_with_error_position != column_names.end()) {
            index_j = static_cast<int32_t>(std::distance(
                column_names.begin(), column_name_with_error_position));
        }
        column_name_with_error_list.push_back(std::make_pair(index_i, index_j));
    }
    return column_name_with_error_list;
}

void Reader::Fill_attribute_names(
    const std::vector<std::string> &column_names,
    const std::vector<std::pair<int, int>> &column_name_with_error_list,
    std::vector<std::string> &attribute_names) {
    for (auto column_name_with_error : column_name_with_error_list) {
        attribute_names.push_back(column_names[column_name_with_error.first]);
    }
}

void Reader::Fill_relation(
    const std::vector<double> &line_values,
    const std::vector<std::pair<int, int>> &column_name_with_error_list,
    Relation &relation) {
    std::vector<Interval> attribute_values;
    for (const auto column_name_with_arror : column_name_with_error_list) {
        double value = line_values[column_name_with_arror.first];
        double error = 0;
        if (column_name_with_arror.second != -1) {
            error = abs(line_values[column_name_with_arror.second]);
        }
        attribute_values.push_back(Interval(value - error, value + error));
    }
    relation.push_back(attribute_values);
}

}  // namespace sr2tr