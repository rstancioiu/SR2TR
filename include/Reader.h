// Reader.h
#ifndef READER_H
#define READER_H
#include "Util.h"
#include "ReadTextFile.h"

/***
	Purpose: Given two input files, it transforms the input data into 
			 two relations and it finds the attribute names associated
	@author: Nicu-Razvan Stancioiu
*/
class Reader{	

	public:
		/**
			Default constructor
		*/
		Reader(){};

		/**
			From two files, the method calls "read" to transform the files into
			relations.
			@param  data_r input file to transform into the source relation
				    data_s input file to transform into the target relation
			@return a pair corresponding to the properties (a pair <relation,attributes>) 
					of the source and target input 
		*/
		pair< pair<Relation, vs>, pair<Relation, vs> > readFiles(const char* data_r,const char* data_s);

	private:
		/**
			Reads an input file and transforms it into a relation
			@param  data input file
				    new_relation the relation that is filled from the input data
				    attrName array of the name of the attributes
		*/
		void read(const char* data, Relation& new_relation, vs& attrName);
};
#endif // READER_H