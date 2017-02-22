/***  
	<Mapping : Given two relations r over a schema relation R and s over a 
			 schema relation S, it finds a mapping function from attributes 
			 of R to attributes of S >
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

#ifndef Mapping_H
#define Mapping_H
#include "Bitset.h"
#include "Util.h"
#include "CR.h"
#include "UIND.h"

class Mapping{	
	public:
		/**
			Default Constructor
		*/
		Mapping(){};

		/**
			Algorithm of finding the mapping function from R to S 
			@param r the source relation
				   s the target relation
				   satisfaction the inclusion metric chosen
		*/
		vector<pair<uint32_t, uint32_t> > SR2TR(Relation& r,Relation& s, int satisfaction);

		/**
			Prints the results of the algorithm SR2TR
		*/
		void print_results(vs& colr, vs& cols);

		/**
			Prints the results of the algorithm SR2TR for web
		*/
		void print_results_web(vs& colr, vs& cols);


	private:
		/**
			Method of finding the minimum weight matching from a matrix M
			@param M matrix 
			@return 
					the minimum cost of the matching
				    an array of pairs of matched attributes
		*/
		pair< double, vector<pair< uint32_t, uint32_t> > >  FindMatching(vector<vector<double> > &M);	
	private: 
		// Number of attributes of R
		uint32_t n;

		// Number of attributes of S
		uint32_t m;

		CR* cr;
		UIND* uind;

		vector<pair<uint32_t, uint32_t> > f;
		double cost;
};	
#endif // CR_H