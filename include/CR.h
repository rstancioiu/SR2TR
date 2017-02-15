/***  
	<CR : Processes the condensed representation of two relations >
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
    
#ifndef CR_H
#define CR_H
#include "Bitset.h"
#include "Util.h"

class CR{	

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
			@return an array of binary relations, i.e. the condensed representation
		*/
		vector<Bitset> Preprocessing(Relation& r, Relation& s, int satisfaction);

		/**
			Shows the result of the preprocessing that can be inserted in a web page
		*/
		void print_cr_web();

		/**
			Shows the result of the preprocessing
		*/
		void print_cr();

	private: 

		/**
			Checks if an interval is included into the domain active of an attribute
			with regard to the satisfaction chosen.
			@param  a interval to check
				    attribute integer identifying the attribute
				    satisfaction integer, either 1 or 2
		*/
		bool check_inclusion(Interval a, uint32_t attribute,int satisfaction);

		/**
			Binary search used to compute the condensed representation with regard
			to satisfaction 2. It finds the lowest value in canonical(ADOM) of 
			an attribute that is greater than a floating number a
			@param  a floating number
				    attribute integer identifying the attribute
			@return the position of the found value 
		*/
		int binary_search_canonical_low(double a, uint32_t attribute);

		/**
			Binary search used to compute the condensed representation with regard
			to satisfaction 2. It finds the highest value in canonical(ADOM) of 
			an attribute that is smaller than a floating number a
			@param  a floating number
				    attribute integer identifying the attribute
			@return the position of the found value
		*/
		int binary_search_canonical_high(double a, uint32_t attribute);

		/**
			Binary search used to compute the condensed representation with regard
			to satisfaction 1. It finds the highest value in ADOM of 
			an attribute that is smaller than a floating number a
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
		void compute_canonical_adom(Relation& r, Relation& s);

		/**
			Generates the data structure used for check_inclusion with regard to 
			satisfaction 1 (classicalAttrAdom). 
			@param  r source relation
					s target relation
		*/
		void compute_classical_adom(Relation &r, Relation& s);

		/**
			Calls the methods compute_canonical_adom or compute_classical_adom
			based on the satisfaction. It also computes ADOM(r \cup s).
			@param  r source relation
					s target relation
					satisfaction integer, either 1 or 2
		*/
		void init(Relation& r, Relation& s,int satisfaction);

		vector<double> *canonicalAttrAdom;
		vector<Interval> *classicalAttrAdom;

		vector<Interval> adom;

		uint32_t n,m;

		vector<Bitset> cr;
};
#endif // CR_H