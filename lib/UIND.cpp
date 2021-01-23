#include "UIND.hpp"

#include <iomanip>
#include <iostream>

std::vector<std::vector<double>> UIND::MEM(std::vector<Bitset> &cr,
                                           uint32_t rsize, uint32_t ssize) {
    for (uint32_t A = 0; A < rsize; ++A) {
        // used to compute the support of 2 degree
        std::vector<int> count(ssize, 0);

        // compute the support sup(A)
        uint32_t support = 0;
        for (uint32_t j = 0; j < cr.size(); ++j) {
            if (cr[j].check(A)) {
                support++;
            }
        }

        // compute the support sup(AB) for each B in S
        for (uint32_t j = 0; j < cr.size(); ++j) {
            if (cr[j].check(A)) {
                for (uint32_t B = 0; B < ssize; ++B) {
                    if (cr[j].check(B + rsize)) {
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

void UIND::print_matrix() {
    std::cout << "--------------------------------------------------"
              << std::endl;
    std::cout << "        MATRIX ERROR BETWEEN R AND S              "
              << std::endl;
    std::cout << "--------------------------------------------------"
              << std::endl;
    for (uint32_t i = 0; i < M.size(); ++i) {
        for (uint32_t j = 0; j < M[i].size(); ++j) {
            std::cout << std::fixed << std::setprecision(3) << M[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void UIND::print_matrix_web(std::vector<std::string> &colr,
                            std::vector<std::string> &cols,
                            std::vector<std::pair<uint32_t, uint32_t>> &f) {
    std::cout << "<p> MATRIX ERROR BETWEEN R AND S </p>"
              << "\n";
    std::cout << "<table border=\"1\">"
              << "\n";
    std::cout << "<tr>\n";
    std::cout << "<td>\n </td>\n";
    for (uint32_t i = 0; i < M[0].size(); ++i) {
        std::cout << "<td>\n";
        std::cout << cols[i] << "\n";
        std::cout << "</td>\n";
    }
    std::cout << "</tr>\n";
    for (uint32_t i = 0; i < M.size(); ++i) {
        uint32_t target_mapping = 0;
        for (uint32_t j = 0; j < M[0].size(); ++j) {
            if (f[j].first - 1 == i) target_mapping = f[j].second - 1;
        }
        std::cout << "<tr>\n";
        std::cout << "<td>\n";
        std::cout << colr[i] << "\n";
        std::cout << "</td>\n";
        for (uint32_t j = 0; j < M[i].size(); ++j) {
            if (target_mapping == j)
                std::cout << "<td bgcolor=\"#FF0000\">\n";
            else
                std::cout << "<td>\n";
            std::cout << std::fixed << std::setprecision(3) << M[i][j] << "\n";
            std::cout << "</td>\n";
        }
        std::cout << "</tr>\n";
    }
    std::cout << "</table>\n";
}
