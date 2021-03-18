#include "CSV_file_reader.hpp"

#include <vector>

namespace {
const char *characters_to_trim = " \t\n\r";
}

namespace sr2tr::reader {

CSV_file_reader::CSV_file_reader(const std::string &file_name)
    : stream(file_name), delimiter('\0') {}

std::vector<std::string> CSV_file_reader::split_line(const std::string &line,
                                                     char delimiter) const {
    std::vector<std::string> line_data;
    size_t position_begin = 0;
    size_t position_end = 0;
    while (position_begin < line.length()) {
        position_end = line.find_first_of(delimiter, position_begin);
        if (position_end == std::string::npos) {
            position_end = line.length();
        }
        std::string value =
            line.substr(position_begin, position_end - position_begin);
        size_t value_begin = value.find_first_not_of(characters_to_trim);
        size_t value_end = value.find_last_not_of(characters_to_trim) + 1;
        line_data.push_back(value.substr(value_begin, value_end - value_begin));
        position_begin = position_end + 1;
    }
    return line_data;
}

std::optional<std::string> CSV_file_reader::read_line() {
    std::string line;
    while (std::getline(stream, line)) {
        line.erase(line.find_last_not_of(characters_to_trim) + 1);
        line.erase(0, line.find_first_not_of(characters_to_trim));
        if (!line.empty()) {
            return line;
        }
    }
    return {};
}

std::vector<std::string> CSV_file_reader::get_columns() {
    std::vector<std::string> columns;
    std::optional<std::string> line_data = read_line();
    if (line_data.has_value()) {
        std::vector<char> candidate_delimiters = {',', ';', '\t'};
        for (char candidate_delimiter : candidate_delimiters) {
            std::vector<std::string> candidate_columns =
                split_line(line_data.value(), candidate_delimiter);
            if (candidate_columns.size() > columns.size()) {
                delimiter = candidate_delimiter;
                columns = std::move(candidate_columns);
            }
        }
    }
    nb_columns = columns.size();
    return columns;
}

std::vector<double> CSV_file_reader::get_line() {
    std::vector<double> line_values;
    std::optional<std::string> line_string = read_line();
    if (line_string.has_value()) {
        std::vector<std::string> line_string_values =
            split_line(line_string.value(), delimiter);
        for (const std::string &line_string_value : line_string_values) {
            line_values.push_back(std::stod(line_string_value));
        }
    }
    return line_values;
}

}  // namespace sr2tr::reader