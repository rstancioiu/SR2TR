// Mapping.h
#ifndef Mapping_H
#define Mapping_H
#include "Bitset.h"
#include "Util.h"
#include "CR.h"
#include "UIND.h"

/***
	Purpose: Given two relations r over a schema relation R and s over a 
			 schema relation S, it finds a mapping function from attributes 
			 of R to attributes of S  
	@author: Nicu-Razvan Stancioiu
*/
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
		vector<pair<int,int> > SR2TR(Relation& r,Relation& s, int satisfaction);

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
		pair< double, vector<pair<int,int> > >  FindMatching(vector<vector<double> > &M);	
	private: 
		// Number of attributes of R
		uint32_t n;

		// Number of attributes of S
		uint32_t m;

		CR* cr;
		UIND* uind;

		vector<pair<int,int> > f;
		double cost;
};	
#endif // CR_H