#pragma once

#include "Bitset.hpp"
#include "Util.hpp"

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
    vector<vector<double>> MEM(vector<Bitset> &cr, uint32_t rsize,
                               uint32_t ssize);

    /**
            Method used to print the state of the matrix
    */
    void print_matrix();

    /**
            Method used to print the state of the matrix
    */
    void print_matrix_web(vs &colr, vs &cols,
                          vector<pair<uint32_t, uint32_t>> &f);

  private:
    vector<vector<double>> M;
};