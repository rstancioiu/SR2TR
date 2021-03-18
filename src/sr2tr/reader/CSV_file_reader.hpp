#pragma once

#include <fstream>
#include <optional>
#include <string>
#include <vector>

namespace sr2tr::reader {

class CSV_file_reader {
   public:
    CSV_file_reader(const std::string &file_name);

    std::vector<std::string> get_columns();

    std::vector<double> get_line();

   private:
    size_t nb_columns = 0;
    std::ifstream stream;
    char delimiter;

    std::vector<std::string> split_line(const std::string &line,
                                        char delimiter) const;

    std::optional<std::string> read_line();
};

}  // namespace sr2tr::reader
