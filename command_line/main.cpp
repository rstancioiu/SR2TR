#include <iostream>
#include <vector>

#include "sr2tr/Mapping.hpp"
#include "sr2tr/Reader.hpp"

using namespace sr2tr;

void Compute_mapping(const std::string &source_file_name,
                     const std::string &target_file_name,
                     int32_t satisfaction) {
    auto [source_relation, column_names_source_relation] =
        Reader::Read_file(source_file_name);
    auto [target_relation, column_names_target_relation] =
        Reader::Read_file(target_file_name);
    if (source_relation.size() == 0) {
        std::cerr << "The source relation is empty" << std::endl;
        return;
    }
    if (target_relation.size() == 0) {
        std::cerr << "The target relation is empty" << std::endl;
        return;
    }
    if (source_relation[0].size() > target_relation[0].size()) {
        std::cerr << "The number of attributes of source relation is bigger "
                  << "than the number of attributes of target relation"
                  << std::endl;
        return;
    }

    Mapping mapping;
    std::vector<std::pair<uint32_t, uint32_t>> best_mapping =
        mapping.SR2TR(source_relation, target_relation, satisfaction).second;

    mapping.print_results(column_names_source_relation,
                          column_names_target_relation);
}

int main(int argc, char *argv[]) {
    const std::string source_file_name = argv[1];
    const std::string target_file_name = argv[2];
    std::cout << source_file_name << " " << target_file_name << std::endl;
    std::cout << "Please choose the satisfaction metric (type 1 or 2) :"
              << std::endl;
    int32_t satisfaction;
    std::cin >> satisfaction;
    if (satisfaction != 1 && satisfaction != 2) {
        std::cout << "There is no satisfaction " << satisfaction << std::endl;
        return 0;
    }
    Compute_mapping(source_file_name, target_file_name, satisfaction);

    return 0;
}