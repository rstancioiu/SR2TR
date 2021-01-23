#pragma once

#include "Bitset.hpp"

class UIND {

  public:
    /**
            Default constructor
    */
    UIND(){};

    /**
            Generate the matrix of error measures ( approximate unary inclusion
       dependencies) from a condensed representation
            @param cr condensed representation
                       rsize size of the source relation r
                       sszie size of the target relation s
            @return 2D-array corresponding to the matrix of error measures
    */
    std::vector<std::vector<double>> MEM(std::vector<Bitset> &cr, uint32_t rsize,
                                         uint32_t ssize);

    /**
            Method used to print the state of the matrix
    */
    void print_matrix();

    /**
            Method used to print the state of the matrix
    */
    void print_matrix_web(std::vector<std::string> &colr, std::vector<std::string> &cols,
                          std::vector<std::pair<uint32_t, uint32_t>> &f);

  private:
    std::vector<std::vector<double>> M;
};