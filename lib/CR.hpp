#pragma once

#include "Bitset.hpp"
#include "Relation.hpp"
#include "Util.hpp"

class CR {

  public:
    /**
            Default Constructor
    */
    CR(){};

    /**
            Computes the condensed representation (an array of binary relations)
            of two relations r and s, based on the satisfaction chosen
            @param  r source relation
                        s target relation
                        satisfaction chosen satisfaction, either 1 or 2
            @return an array of binary relations, i.e. the condensed
       representation
    */
    std::vector<Bitset> Preprocessing(Relation &r, Relation &s, int satisfaction);

    /**
            Shows the result of the preprocessing that can be inserted in a web
       page
    */
    void print_cr_web();

    /**
            Shows the result of the preprocessing
    */
    void print_cr();

  private:
    /**
            Checks if an interval is included into the domain active of an
       attribute with regard to the satisfaction chosen.
            @param  a interval to check
                        attribute integer identifying the attribute
                        satisfaction integer, either 1 or 2
    */
    bool check_inclusion(Interval a, uint32_t attribute, int satisfaction);

    /**
            Binary search used to compute the condensed representation with
       regard to satisfaction 2. It finds the lowest value in canonical(ADOM) of
            an attribute that is greater than a floating number a
            @param  a floating number
                        attribute integer identifying the attribute
            @return the position of the found value
    */
    int binary_search_canonical_low(double a, uint32_t attribute);

    /**
            Binary search used to compute the condensed representation with
       regard to satisfaction 2. It finds the highest value in canonical(ADOM)
       of an attribute that is smaller than a floating number a
            @param  a floating number
                        attribute integer identifying the attribute
            @return the position of the found value
    */
    int binary_search_canonical_high(double a, uint32_t attribute);

    /**
            Binary search used to compute the condensed representation with
       regard to satisfaction 1. It finds the highest value in ADOM of an
       attribute that is smaller than a floating number a
            @param  a floating number
                        attribute integer identifying the attribute
            @return the position of the found value
    */
    int binary_search_classical(double a, uint32_t attribute);

    /**
            Generates the data structure used for check_inclusion with regard to
            satisfaction 2 (canonicalAttrAdom).
            @param  r source relation
                            s target relation
    */
    void compute_canonical_adom(Relation &r, Relation &s);

    /**
            Generates the data structure used for check_inclusion with regard to
            satisfaction 1 (classicalAttrAdom).
            @param  r source relation
                            s target relation
    */
    void compute_classical_adom(Relation &r, Relation &s);

    /**
            Calls the methods compute_canonical_adom or compute_classical_adom
            based on the satisfaction. It also computes ADOM(r \cup s).
            @param  r source relation
                            s target relation
                            satisfaction integer, either 1 or 2
    */
    void init(Relation &r, Relation &s, int satisfaction);

    std::vector<double> *canonicalAttrAdom;
    std::vector<Interval> *classicalAttrAdom;

    std::vector<Interval> adom;

    uint32_t n, m;

    std::vector<Bitset> cr;
};