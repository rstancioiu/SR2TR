#include "Unary_inclusion_dependency.hpp"

#include <iomanip>
#include <iostream>

namespace sr2tr {
using namespace containers;

std::vector<std::vector<double>> Unary_inclusion_dependency::MEM(
    std::vector<Bitset> &cr, uint32_t rsize, uint32_t ssize) {
    for (uint32_t A = 0; A < rsize; ++A) {
        // used to compute the support of 2 degree
        std::vector<int> count(ssize, 0);

        // compute the support sup(A)
        uint32_t support = 0;
        for (uint32_t j = 0; j < cr.size(); ++j) {
            if (cr[j].test(A)) {
                support++;
            }
        }

        // compute the support sup(AB) for each B in S
        for (uint32_t j = 0; j < cr.size(); ++j) {
            if (cr[j].test(A)) {
                for (uint32_t B = 0; B < ssize; ++B) {
                    if (cr[j].test(B + rsize)) {
                        count[B]++;
                    }
                }
            }
        }

        // update the matrix
        std::vector<double> array(ssize, 1.0);
        for (uint32_t B = 0; B < array.size(); ++B) {
            array[B] -= (double)count[B] / support;
        }
        M.push_back(array);
    }

    std::vector<std::vector<double>> ret_M = M;

    // if rsize!=ssize we complete the matrix so that it becomes a square matrix
    // this will be used for the hungarian algorithm
    for (uint32_t i = rsize; i < ssize; ++i) {
        std::vector<double> aux(ssize, 0);
        ret_M.push_back(aux);
    }

    return ret_M;
}

void Unary_inclusion_dependency::print(std::ostream &stream) {
    stream << "--------------------------------------------------" << std::endl;
    stream << "        MATRIX ERROR BETWEEN R AND S              " << std::endl;
    stream << "--------------------------------------------------" << std::endl;
    for (uint32_t i = 0; i < M.size(); ++i) {
        for (uint32_t j = 0; j < M[i].size(); ++j) {
            stream << std::fixed << std::setprecision(3) << M[i][j] << " ";
        }
        stream << std::endl;
    }
    stream << std::endl;
}

}  // namespace sr2tr