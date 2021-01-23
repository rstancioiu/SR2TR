#include "Condensed_representation.hpp"

#include <algorithm>
#include <iomanip>
#include <iostream>

void Condensed_representation::compute_canonical_adom(Relation &r,
                                                      Relation &s) {
    canonicalAttrAdom = new std::vector<double>[n + m];

    std::vector<std::pair<double, int>> *aux =
        new std::vector<std::pair<double, int>>[n + m];

    for (uint32_t i = 0; i < r.size(); ++i) {
        for (uint32_t j = 0; j < n; ++j) {
            aux[j].push_back(std::make_pair(r[i][j].first, -1));
            aux[j].push_back(std::make_pair(r[i][j].second, 1));
        }
    }
    for (uint32_t i = 0; i < s.size(); ++i) {
        for (uint32_t j = 0; j < m; ++j) {
            aux[j + n].push_back(std::make_pair(s[i][j].first, -1));
            aux[j + n].push_back(std::make_pair(s[i][j].second, 1));
        }
    }
    for (uint32_t i = 0; i < m + n; ++i) {
        sort(aux[i].begin(), aux[i].end());
        double start = aux[i][0].first;
        int cnt = 1;
        for (uint32_t j = 1; j < aux[i].size(); ++j) {
            cnt += -aux[i][j].second;
            if (cnt == 0) {
                canonicalAttrAdom[i].push_back(start);
                canonicalAttrAdom[i].push_back(aux[i][j].first);
                if (j + 1 < aux[i].size()) {
                    start = aux[i][j + 1].first;
                }
            }
        }
    }
}

void Condensed_representation::compute_classical_adom(Relation &r,
                                                      Relation &s) {
    classicalAttrAdom = new std::vector<Interval>[n + m];
    for (uint32_t i = 0; i < r.size(); ++i) {
        for (uint32_t j = 0; j < n; ++j) {
            classicalAttrAdom[j].push_back(r[i][j]);
        }
    }
    for (uint32_t i = 0; i < s.size(); ++i) {
        for (uint32_t j = 0; j < m; ++j) {
            classicalAttrAdom[j + n].push_back(s[i][j]);
        }
    }
    for (uint32_t i = 0; i < n + m; ++i) {
        std::sort(classicalAttrAdom[i].begin(), classicalAttrAdom[i].end());
        uint32_t k = 0;
        for (uint32_t j = 1; j < classicalAttrAdom[i].size(); ++j) {
            if (classicalAttrAdom[i][j].first !=
                classicalAttrAdom[i][j - 1].first) {
                k++;
                classicalAttrAdom[i][k] = classicalAttrAdom[i][j];
            } else {
                classicalAttrAdom[i][k].second =
                    std::max(classicalAttrAdom[i][k].second,
                             classicalAttrAdom[i][j].second);
            }
        }
        k++;
        classicalAttrAdom[i].resize(k);
    }
}

int Condensed_representation::binary_search_canonical_low(double a,
                                                          uint32_t attribute) {
    uint32_t low = 0;
    uint32_t high = canonicalAttrAdom[attribute].size();
    while (low + 1 < high) {
        uint32_t middle = (high + low) / 2;
        if (a >= canonicalAttrAdom[attribute][middle]) {
            low = middle;
        } else {
            high = middle;
        }
    }
    if (low > 0 && canonicalAttrAdom[attribute][low - 1] == a) low--;
    return low;
}

int Condensed_representation::binary_search_canonical_high(double a,
                                                           uint32_t attribute) {
    uint32_t low = -1;
    uint32_t high = canonicalAttrAdom[attribute].size();
    while (low + 1 < high) {
        uint32_t middle = (high + low) / 2;
        if (a <= canonicalAttrAdom[attribute][middle]) {
            high = middle;
        } else {
            low = middle;
        }
    }
    if (high + 1 < canonicalAttrAdom[attribute].size() &&
        canonicalAttrAdom[attribute][high + 1] == a)
        high++;
    return high;
}

int Condensed_representation::binary_search_classical(double a,
                                                      uint32_t attribute) {
    uint32_t low = 0;
    uint32_t high = classicalAttrAdom[attribute].size();
    while (low + 1 < high) {
        uint32_t middle = (high + low) / 2;
        if (classicalAttrAdom[attribute][middle].first <= a) {
            low = middle;
        } else {
            high = middle;
        }
    }
    return low;
}

bool Condensed_representation::check_inclusion(Interval i, uint32_t attribute,
                                               int satisfaction) {
    double a = i.first;
    double b = i.second;
    if (satisfaction == 2) {
        uint32_t p = canonicalAttrAdom[attribute].size();
        if (p == 0) {
            return false;
        } else if (a < canonicalAttrAdom[attribute][0]) {
            return false;
        } else if (b > canonicalAttrAdom[attribute][p - 1]) {
            return false;
        } else {
            int s = binary_search_canonical_low(a, attribute);
            int e = binary_search_canonical_high(b, attribute);
            if (s == e - 1 && s % 2 == 0) {
                return true;
            }
            return false;
        }
    }
    if (satisfaction == 1) {
        uint32_t p = classicalAttrAdom[attribute].size();
        if (p == 0) {
            return false;
        } else if (a < classicalAttrAdom[attribute][0].first) {
            return false;
        } else {
            int k = binary_search_classical(a, attribute);
            if (classicalAttrAdom[attribute][k].second >= b) {
                return true;
            } else {
                return false;
            }
        }
    }
    return false;
}

void Condensed_representation::init(Relation &r, Relation &s,
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

    if (satisfaction == 2) compute_canonical_adom(r, s);
    if (satisfaction == 1) compute_classical_adom(r, s);

    // ADOM(r \cup s)
    for (uint32_t i = 0; i < r.size(); ++i) {
        for (uint32_t j = 0; j < r[i].size(); ++j) {
            adom.push_back(r[i][j]);
        }
    }
    for (uint32_t i = 0; i < s.size(); ++i) {
        for (uint32_t j = 0; j < s[i].size(); ++j) {
            adom.push_back(s[i][j]);
        }
    }
    std::sort(adom.begin(), adom.end());

    // remove duplicates
    uint32_t k = 1;
    for (uint32_t i = 1; i < adom.size(); ++i) {
        if (adom[i] != adom[i - 1]) {
            adom[k] = adom[i];
            k++;
        }
    }
    adom.resize(k);
}

// Maps the tables r and s into an array of Bitsets
std::vector<Bitset> Condensed_representation::Preprocessing(Relation &r,
                                                            Relation &s,
                                                            int satisfaction) {
    init(r, s, satisfaction);

    uint32_t p = n + m;
    for (uint32_t i = 0; i < adom.size(); ++i) {
        Interval current_interval = adom[i];
        std::vector<bool> array(p, false);
        for (uint32_t j = 0; j < p; ++j) {
            if (check_inclusion(current_interval, j, satisfaction)) {
                array[j] = true;
            }
        }
        Bitset set(array);
        cr.push_back(set);
    }
    return cr;
}

void Condensed_representation::print_cr() {
    std::cout << "--------------------------------------------------"
              << std::endl;
    std::cout << "        CONDENSED REPRESENTATION CR(r,s)          "
              << std::endl;
    std::cout << "--------------------------------------------------"
              << std::endl;
    for (uint32_t i = 0; i < adom.size(); ++i) {
        std::cout << "[" << std::setw(4) << adom[i].first << ";" << std::setw(5)
                  << adom[i].second << "] || " << cr[i].toString() << std::endl;
    }
    std::cout << std::endl;
}