#pragma once

#include <string>
#include <vector>

#include "Relation.hpp"

namespace sr2tr {

class Condensed_representation;
class Unary_inclusion_dependency;

class Mapping {
   public:
    /**
            Algorithm of finding the mapping function from R to S
            @param r the source relation
                       s the target relation
                       satisfaction the inclusion metric chosen
    */
    std::pair<double, std::vector<std::pair<uint32_t, uint32_t>>> SR2TR(
        Relation &r, Relation &s, int satisfaction);

    /**
            Prints the results of the algorithm SR2TR
    */
    void print_results(std::vector<std::string> &colr,
                       std::vector<std::string> &cols);

   private:
    /**
            Method of finding the minimum weight matching from a matrix M
            @param M matrix
            @return
                            the minimum cost of the matching
                        an array of pairs of matched attributes
    */
    std::pair<double, std::vector<std::pair<uint32_t, uint32_t>>> FindMatching(
        std::vector<std::vector<double>> &M);

   private:
    // Number of attributes of R
    uint32_t n;

    // Number of attributes of S
    uint32_t m;

    Condensed_representation *cr;
    Unary_inclusion_dependency *unary_inclusion_dependency;

    std::vector<std::pair<uint32_t, uint32_t>> f;
    double cost;
};

}  // namespace sr2tr