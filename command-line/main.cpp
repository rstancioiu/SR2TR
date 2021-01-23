#include "lib/Mapping.hpp"
#include "lib/Reader.hpp"

#include <iostream>
#include <string>
#include <vector>

const char *data_r;
const char *data_s;
int satisfaction;
Relation r, s;
uint32_t n, m;
std::vector<std::string> colr, cols;
void computeMapping();
void readFiles();

int main(int argc, char *argv[]) {
    data_r = argv[1];
    data_s = argv[2];
    std::cout << "Please choose the satisfaction metric (type 1 or 2) :" << std::endl;
    std::cin >> satisfaction;
    if (satisfaction != 1 && satisfaction != 2) {
        std::cout << "There is no satisfaction " << satisfaction << std::endl;
        return 0;
    }
    computeMapping();

    return 0;
}

void readFiles() {
    // read files
    Reader *reader = new Reader();
    std::pair<std::pair<Relation, std::vector<std::string>>, std::pair<Relation, std::vector<std::string>>> prs =
        reader->readFiles(data_r, data_s);
    delete reader;

    r = prs.first.first;
    s = prs.second.first;

    colr = prs.first.second;
    cols = prs.second.second;
    if (r.size() == 0) {
        std::cout << "The source relation is empty" << std::endl;
        exit(0);
    }
    if (s.size() == 0) {
        std::cout << "The target relation is empty" << std::endl;
        exit(0);
    }
    if (r[0].size() > s[0].size()) {
        std::cout << "The number of attributes of source relation is bigger "
                  << "than the number of attributes of target relation" << std::endl;
        exit(0);
    }
}

void computeMapping() {
    readFiles();

    // compute mapping
    Mapping *mapping = new Mapping();
    std::vector<std::pair<uint32_t, uint32_t>> f = mapping->SR2TR(r, s, satisfaction);

    mapping->print_results(colr, cols);
}
