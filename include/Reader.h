/***  
	<Reader : Given two input files, it transforms the input data into 
			 two relations and it finds the attribute names associated >
    Copyright (C) <2017>  <Razvan STANCIOIU>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef READER_H
#define READER_H
#include "Util.h"
#include "ReadTextFile.h"

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