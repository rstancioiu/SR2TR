#include "UIND.h"

vector<vector<double> > UIND::MEM(vector<Bitset>& cr,uint32_t rsize, uint32_t ssize){

	for(uint32_t A=0; A < rsize; ++A){
		// used to compute the support of 2 degree
		vector<int> count(ssize, 0);

		// compute the support sup(A)
		uint32_t support = 0;
		for(uint32_t j=0;j<cr.size();++j) {
			if(cr[j].check(A)) {
				support++;
			}
		}

		// compute the support sup(AB) for each B in S
		for(uint32_t j=0;j<cr.size();++j){
			if(cr[j].check(A)){
				for(uint32_t B=0;B<ssize;++B){
					if(cr[j].check(B+rsize)){
						count[B]++;
					}
				}
			}
		}

		// update the matrix
		vector<double> array(ssize, 1.0);
		for(uint32_t B=0; B<array.size();++B){
			array[B] -= (double)count[B]/support;
		}
		M.push_back(array);

	}

	vector<vector<double> > ret_M = M;

	// if rsize!=ssize we complete the matrix so that it becomes a square matrix
	// this will be used for the hungarian algorithm
	for(uint32_t i = rsize ; i < ssize; ++i) {
		vector<double> aux(ssize,0);
		ret_M.push_back(aux);
	}

	return ret_M;
}

void UIND::print_matrix() {
	cout<<"--------------------------------------------------"<<endl;
    cout<<"        MATRIX ERROR BETWEEN R AND S              "<<endl;
    cout<<"--------------------------------------------------"<<endl;
	for(uint32_t i=0;i<M.size();++i) {
		for(uint32_t j=0;j<M[i].size();++j) {
			cout<<fixed<<setprecision(3)<<M[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
}

void UIND::print_matrix_web(vs &colr, vs& cols, vector<pair<uint32_t, uint32_t> >& f) {
	cout<<"<p> MATRIX ERROR BETWEEN R AND S </p>"<<"\n";
	cout<<"<table border=\"1\">"<<"\n";
	cout<<"<tr>\n";
	cout<<"<td>\n </td>\n";
	for(uint32_t i=0; i<M[0].size();++i) {
		cout<<"<td>\n";
		cout<<cols[i]<<"\n";
		cout<<"</td>\n";
	}
	cout<<"</tr>\n";
	for(uint32_t i=0;i<M.size();++i) {
		cout<<"<tr>\n";
		cout<<"<td>\n";
		cout<<colr[i]<<"\n";
		cout<<"</td>\n";
		for(uint32_t j=0;j<M[i].size();++j) {
			if(f[i].second == j) cout<<"<td bgcolor=\"#FF0000\">\n"; 
			else cout<<"<td>\n";
			cout<<fixed<<setprecision(3)<<M[i][j]<<"\n";
			cout<<"</td>\n";
		}
		cout<<"</tr>\n";
	}
	cout<<"</table>\n";
}
