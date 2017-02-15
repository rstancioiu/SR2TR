/***  
	<UIND : Based on the condensed representation of two relations r and s,
			 it generates the matrix of error measures >
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
    
#ifndef UIND_H
#define UIND_H
#include "Bitset.h"
#include "Util.h"

class UIND{	

	public:
		/**
			Default constructor
		*/
		UIND(){};

		/**
			Generate the matrix of error measures ( approximate unary inclusion dependencies)
			from a condensed representation
			@param cr condensed representation
				   rsize size of the source relation r
				   sszie size of the target relation s
			@return 2D-array corresponding to the matrix of error measures
		*/
		vector<vector<double> > MEM(vector<Bitset>& cr, uint32_t rsize, uint32_t ssize);

		/**
			Method used to print the state of the matrix
		*/
		void print_matrix();

		/**
			Method used to print the state of the matrix
		*/
		void print_matrix_web();

	private:

		vector<vector<double> > M;
};
#endif // UIND_H