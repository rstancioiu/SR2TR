#pragma once

#include <string>

#include "Relation.hpp"

class Reader {
   public:
    /**
            From two files, the method calls "read" to transform the files into
            relations.
            @param  data_r input file to transform into the source relation
                        data_s input file to transform into the target relation
            @return a pair corresponding to the properties (a pair
       <relation,attributes>) of the source and target input
    */
    std::pair<std::pair<Relation, std::vector<std::string>>,
              std::pair<Relation, std::vector<std::string>>>
    readFiles(const char *data_r, const char *data_s);

   private:
    /**
            Reads an input file and transforms it into a relation
            @param  data input file
                        new_relation the relation that is filled from the input
       data attrName array of the name of the attributes
    */
    void read(const char *data, Relation &new_relation,
              std::vector<std::string> &attrName);
};