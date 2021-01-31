#pragma once

#include <cstdint>
#include <ostream>
#include <vector>

namespace sr2tr::mapping {

class Hungarian {
   public:
    Hungarian(){};

    /**
        Constructs the weighted bipartite graph from the cost matrix
        In case that the matrix is not n*n, then the matrix is extended
        with rows composed by zero.
    */
    Hungarian(std::vector<std::vector<double>> &cost_matrix);

    /**
        Computes the hungarian algorithm for the graph formed
        @return a pair composed of the minimum cost of the matching
                and a vector corresponding to the matching
    */
    std::pair<double, std::vector<std::pair<uint32_t, uint32_t>>>
    compute_hungarian();

   private:
    /**
        Recursive Method that realizes a Depth First Search from
        given vertex v. It is used in the hopcroft_karp method.
        @param vertex v
    */
    bool dfs_hopcroft_karp(uint32_t v);

    /**
        The algorithm hopcroft karp that checks if for a given bipartite
        graph, there is a perfect matching.
        @return true if perfect matching
                false if otherwise
    */
    bool hopcroft_karp();

    /**
            Recursive Method that realizes a Depth First Search from a given
            vertex v. It is used in computing the minimum set cover.
            @param vertex v
    */
    void dfs_minimum_set_cover(uint32_t v);

    /**
            Computes the minimum set cover of a bipartite graph based on the
            maximum matching found.
            This method is based on the Konig Theorem:
            Let a graph G=(V,E), where V is partitioned into the left side L and
            the right side R. U the set of unmatched vertexes from the L. Z is
       the set of vertexes that are either in U or are connected with U by
            alternating paths:
            K = (L\Z) \cup (R \cap Z).
            K is the vertex cover of G.
    */
    void minimum_set_cover();

    /**
            For each row, decreases the values of elements in the row
            with the minimum value of that row.
    */
    void row_minima();

    /**
            For each column, decreases the values of elements in the column
            with the minimum value of that column.
    */
    void col_minima();

    /**
            Transforms the cost matrix based on the last minimum set cover V
       found: Let delta = min(cost_matrix[i][j]) where i,j are not in the V. For
       each element of the matrix we have the following transformations:
            cost[i][j] = | cost[i][j] - delta, if i,j not in V
                                 | cost[i][j] 	     , if one of i,j is in V,
       but not both | cost[i][j] + delta, if both i,j are in V
    */
    void additional_zeros();

    void print(std::ostream &stream);

   private:
    // the size of the initial cost matrix
    uint32_t n, m;

    // matrix that stores the initial cost matrix
    double **init_cost;

    // the cost matrix used during the hungarian algorithm
    double **cost;

    // the structure of the bipartite graph
    std::vector<uint32_t> *g;

    // array of booleans that checks whether or not a vertex was visited
    // during a DFS
    bool *vis;

    // array of booleans that checks wheter or not a vertex is in
    // the minimum set cover
    bool *cover;

    // array corresponding to the left side L of the bipartite graph
    uint32_t *l;

    // array corresponding to the right side R of the bipartite graph
    uint32_t *r;
};

}  // namespace sr2tr::mapping