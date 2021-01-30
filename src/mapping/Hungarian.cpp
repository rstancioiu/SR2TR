#include "Hungarian.hpp"

#include <iostream>

Hungarian::Hungarian(std::vector<std::vector<double>> &cost_matrix) {
    n = cost_matrix.size();
    m = 2 * n + 2;
    cost = new double *[n + 1];
    init_cost = new double *[n + 1];
    g = new std::vector<uint32_t>[m];
    vis = new bool[m];
    cover = new bool[m];
    l = new uint32_t[m];
    r = new uint32_t[m];
    for (uint32_t i = 1; i <= n; ++i) {
        cost[i] = new double[n + 1];
        init_cost[i] = new double[n + 1];
        for (uint32_t j = 1; j <= n; ++j) {
            cost[i][j] = cost_matrix[i - 1][j - 1];
            init_cost[i][j] = cost_matrix[i - 1][j - 1];
        }
    }
    std::fill(l, l + m, 0);
    std::fill(r, r + m, 0);
}

// used to compute an augmenting path for Hopcroft-Karp algorithm
bool Hungarian::dfs_hopcroft_karp(uint32_t v) {
    if (vis[v]) return false;
    vis[v] = true;
    for (uint32_t u = 0; u < g[v].size(); ++u) {
        if (!r[g[v][u]]) {
            l[v] = g[v][u];
            r[g[v][u]] = v;
            return true;
        }
    }
    for (uint32_t u = 0; u < g[v].size(); ++u) {
        if (dfs_hopcroft_karp(r[g[v][u]])) {
            l[v] = g[v][u];
            r[g[v][u]] = v;
            return true;
        }
    }
    return false;
}

bool Hungarian::hopcroft_karp() {
    bool change = true;
    while (change) {
        change = false;
        std::fill(vis, vis + n + 1, false);
        for (uint32_t i = 1; i <= n; ++i) {
            if (!l[i]) {
                change |= dfs_hopcroft_karp(i);
            }
        }
    }

    bool matching = true;
    for (uint32_t i = 1; i <= n; ++i) {
        if (!l[i]) {
            matching = false;
        }
    }
    return matching;
}

void Hungarian::dfs_minimum_set_cover(uint32_t v) {
    cover[v] = true;
    for (uint32_t u = 0; u < g[v].size(); ++u) {
        if (g[v][u] != l[v] && !cover[g[v][u]] && r[g[v][u]] != 0) {
            cover[g[v][u]] = true;
            dfs_minimum_set_cover(r[g[v][u]]);
        }
    }
}

void Hungarian::minimum_set_cover() {
    std::fill(cover, cover + 2 * n + 1, 0);  // set denoted with Z
    for (uint32_t i = 1; i <= n; ++i) {
        if (!l[i]) {
            dfs_minimum_set_cover(i);
        }
    }
    // konig theorem : K = (L\Z) union (R interset Z)
    // L\Z
    for (uint32_t i = 1; i <= n; ++i) {
        if (l[i] && !cover[i]) {
            cover[i] = true;
        } else {
            cover[i] = false;
        }
    }
    // R intersect Z
    for (uint32_t i = n + 1; i <= 2 * n; ++i) {
        if (r[i] && cover[i]) {
            cover[i] = true;
        } else {
            cover[i] = false;
        }
    }
}

void Hungarian::row_minima() {
    for (uint32_t i = 1; i <= n; ++i) {
        double minimum = 1e15;
        for (uint32_t j = 1; j <= n; ++j) {
            minimum = std::min(minimum, cost[i][j]);
        }
        for (uint32_t j = 1; j <= n; ++j) {
            cost[i][j] -= minimum;
            if (cost[i][j] == 0) {
                g[i].push_back(j + n);
            }
        }
    }
}

void Hungarian::col_minima() {
    std::vector<double> minimum(n + 1, 1e15);
    for (uint32_t i = 1; i <= n; ++i) {
        for (uint32_t j = 1; j <= n; ++j) {
            minimum[j] = std::min(minimum[j], cost[i][j]);
        }
    }
    for (uint32_t i = 1; i <= n; ++i) {
        for (uint32_t j = 1; j <= n; ++j) {
            if (cost[i][j] > 0) {
                cost[i][j] -= minimum[j];
                if (cost[i][j] == 0) {
                    g[i].push_back(j + n);
                }
            }
        }
    }
}

void Hungarian::additional_zeros() {
    double minimum = 1e15;
    for (uint32_t i = 1; i <= n; ++i) {
        for (uint32_t j = 1; j <= n; ++j) {
            if (!cover[i] && !cover[n + j]) {
                if (cost[i][j] < minimum) {
                    minimum = cost[i][j];
                }
            }
        }
    }
    for (uint32_t i = 1; i <= n; ++i) {
        for (uint32_t j = 1; j <= n; ++j) {
            if (!cover[i] && !cover[n + j]) {
                cost[i][j] -= minimum;
                if (cost[i][j] == 0) {
                    g[i].push_back(j + n);
                }
            } else if (cover[i] && cover[n + j]) {
                cost[i][j] += minimum;
            }
        }
    }
}

void Hungarian::print_matrix() {
    for (uint32_t i = 1; i <= n; ++i) {
        for (uint32_t j = 1; j <= n; ++j) {
            std::cout << cost[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

std::pair<double, std::vector<std::pair<uint32_t, uint32_t>>>
Hungarian::compute_hungarian() {
    // step 1
    row_minima();
    // step 2
    col_minima();
    // step 3
    while (!hopcroft_karp()) {
        minimum_set_cover();
        // step 4
        additional_zeros();
    }

    // step 5 - prepare matching and return minimum_cost
    std::vector<std::pair<uint32_t, uint32_t>> matching;
    double minimum_cost = 0;
    for (uint32_t i = 1; i <= n; ++i) {
        matching.push_back(std::make_pair(i, l[i]));
        minimum_cost += init_cost[i][l[i] - n];
    }
    return make_pair(minimum_cost, matching);
}