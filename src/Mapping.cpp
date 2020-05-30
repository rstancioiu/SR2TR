#include "Mapping.hpp"
#include "Hungarian.hpp"

vector<pair<uint32_t, uint32_t>> Mapping::SR2TR(Relation &r, Relation &s,
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

    cr = new CR();
    uind = new UIND();

    vector<Bitset> bitsets = cr->Preprocessing(r, s, satisfaction);

    vector<vector<double>> M = uind->MEM(bitsets, n, m);

    pair<double, vector<pair<uint32_t, uint32_t>>> matching = FindMatching(M);

    cost = matching.first;

    f = matching.second;

    return f;
}

pair<double, vector<pair<uint32_t, uint32_t>>>
Mapping::FindMatching(vector<vector<double>> &M) {

    Hungarian *hungarian = new Hungarian(M);

    pair<double, vector<pair<uint32_t, uint32_t>>> res =
        hungarian->compute_hungarian();
    vector<pair<uint32_t, uint32_t>> f;

    double cost = res.first;

    for (uint32_t i = 0; i < n; ++i) {
        f.push_back(make_pair(res.second[i].first, res.second[i].second - m));
    }

    return make_pair(cost, f);
}

void Mapping::print_results(vs &colr, vs &cols) {
    cr->print_cr();
    uind->print_matrix();

    cout << "--------------------------------------------------" << endl;
    cout << "        RESULTS OF THE MATCHING BETWEEN R AND S   " << endl;
    cout << "--------------------------------------------------" << endl;

    cout << "Cost of matching:   " << cost << endl;

    // print mapping
    for (uint32_t i = 0; i < f.size(); ++i) {
        int x = f[i].first - 1;
        int y = f[i].second - 1;
        cout << "f[" << colr[x] << "] = " << cols[y] << endl;
    }

    cout << endl;
}

void Mapping::print_results_web(vs &colr, vs &cols) {
    cr->print_cr_web();

    uind->print_matrix_web(colr, cols, f);

    cout << "<p> Cost of matching is equal to: " << cost << "</p>"
         << "\n";
    cout << "<p> Results of the mapping found: ";
    // print mapping
    cout << "<ul>\n";
    for (uint32_t i = 0; i < f.size(); ++i) {
        int x = f[i].first - 1;
        int y = f[i].second - 1;
        cout << "<li>"
             << "f[" << colr[x] << "] = " << cols[y] << "</li>\n";
    }
    cout << "</ul>\n";
    cout << "</p>\n";
}
