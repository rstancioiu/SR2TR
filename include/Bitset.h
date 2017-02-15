/***  
	<Bitset : Custom bitset data structure >
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
    
#ifndef BITSET_H
#define BITSET_H
#include "Util.h"

class Bitset{	

	public:
		/**
			Default Constructor
		*/
		Bitset();

		/**
			Constructor from an array of bits (booleans)
		*/
		Bitset(vector<bool>& new_bitset);

		/**
			Constructor of copy
		*/
		Bitset(const Bitset &obj);

		/**
			Destructor
		*/
		~Bitset();

		/**
			Clears the sequence of bits in the bitset
		*/
		void clear();

		/**
			Checks if the sequence of bits is empty
			@return true if array is empty
					false if otherwise
		*/
		bool empty() const;

		/**
			Sets the value of the bit found at the ith position to bit
			@param i position of bit to change
				   value in which the bit will change
		*/
		void set(uint32_t i, bool value);

		/**
		 	@return the number of bits that are equal to 1 in the sequence		
		*/
		uint32_t count() const;

		/**
			Checks if the value of the bit found at the ith position is 1
			@param x position to check
			@return true if array[i]=1
					false if otherwise
		*/
		bool check(uint32_t i) const;

		/**
			@return the size of the sequence
		*/
		uint32_t size();

		/**
			Modifies the size of the sequence
			@param n new size of the sequence
		*/
		void resize(uint32_t n);

		/**
			Transforms the sequence of bits into a string of characters
			@return the corresponding string
		*/
		string toString();

		/**
			Operator to compare two bitsets
		*/
		bool operator<(Bitset const& b) const;

		/**
			Operator to compare two bitsets
		*/
		bool operator>(Bitset const& b) const;

		/**
			Operator to check if two bitsets are equal
		*/
		bool operator==(const Bitset& b) const;

		/*
			Operator to check if two bitsets are different
		*/
		bool operator!=(const Bitset& b) const;


	private:
		// Default size of the bitset
		static const unsigned int DEFAULT_SIZE = 256;

		// Array that corresponds to the sequence of the bitset
		vector<bool> array = vector<bool>(DEFAULT_SIZE,0);

};

#endif // BITSET_H