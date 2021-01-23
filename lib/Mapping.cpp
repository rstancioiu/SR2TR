#include "Mapping.hpp"

#include <iostream>
#include <vector>

#include "Hungarian.hpp"

std::vector<std::pair<uint32_t, uint32_t>> Mapping::SR2TR(Relation &r,
                                                          Relation &s,
                                                          int satisfaction) {
    if (r.size() == 0) {
        n = 0;
    } else {
        n = r[0].size();
    }
    if (s.size() == 0) {
        m = 0;
    } else {
        m = s[0].size();
    }

    cr = new Condensed_representation();
    uind = new UIND();

    std::vector<Bitset> bitsets = cr->Preprocessing(r, s, satisfaction);

    std::vector<std::vector<double>> M = uind->MEM(bitsets, n, m);

    std::pair<double, std::vector<std::pair<uint32_t, uint32_t>>> matching =
        FindMatching(M);

    cost = matching.first;

    f = matching.second;

    return f;
}

std::pair<double, std::vector<std::pair<uint32_t, uint32_t>>>
Mapping::FindMatching(std::vector<std::vector<double>> &M) {
    Hungarian *hungarian = new Hungarian(M);

    std::pair<double, std::vector<std::pair<uint32_t, uint32_t>>> res =
        hungarian->compute_hungarian();
    std::vector<std::pair<uint32_t, uint32_t>> f;

    double cost = res.first;

    for (uint32_t i = 0; i < n; ++i) {
        f.push_back(
            std::make_pair(res.second[i].first, res.second[i].second - m));
    }

    return make_pair(cost, f);
}

void Mapping::print_results(std::vector<std::string> &colr,
                            std::vector<std::string> &cols) {
    cr->print_cr();
    uind->print_matrix();

    std::cout << "--------------------------------------------------"
              << std::endl;
    std::cout << "        RESULTS OF THE MATCHING BETWEEN R AND S   "
              << std::endl;
    std::cout << "--------------------------------------------------"
              << std::endl;

    std::cout << "Cost of matching:   " << cost << std::endl;

    // print mapping
    for (uint32_t i = 0; i < f.size(); ++i) {
        int x = f[i].first - 1;
        int y = f[i].second - 1;
        std::cout << "f[" << colr[x] << "] = " << cols[y] << std::endl;
    }

    std::cout << std::endl;
}
