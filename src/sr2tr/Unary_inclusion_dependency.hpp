#pragma once

#include "containers/Bitset.hpp"

namespace sr2tr {

class Unary_inclusion_dependency {
   public:
    /**
            Generate the matrix of error measures ( approximate unary inclusion
       dependencies) from a condensed representation
            @param cr condensed representation
                       rsize size of the source relation r
                       sszie size of the target relation s
            @return 2D-array corresponding to the matrix of error measures
    */
    std::vector<std::vector<double>> MEM(std::vector<containers::Bitset> &cr,
                                         uint32_t rsize, uint32_t ssize);

    /**
            Method used to print the state of the matrix
    */
    void print(std::ostream &stream);

   private:
    std::vector<std::vector<double>> M;
};

}  // namespace sr2tr