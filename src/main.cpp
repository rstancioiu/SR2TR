/***  
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
    
#include "Reader.h"
#include "Util.h"
#include "Mapping.h"


using namespace std;

const char* data_r;
const char* data_s;
int satisfaction;
Relation r,s;
uint32_t n,m;
vs colr,cols;
void computeMapping();
void readFiles();

int main(int argc, char* argv[] ){
	data_r = argv[1];
	data_s = argv[2];
	cout<<"Please choose the satisfaction metric (type 1 or 2) :"<<endl;
	cin>>satisfaction;
	if(satisfaction!=1 && satisfaction!=2) {
		cout<<"There is no satisfaction "<<satisfaction<<endl;
		return 0;
	}
	computeMapping();

	return 0;
}

void readFiles() {
	// read files
	Reader* reader = new Reader();
	pair< pair<Relation,vs> , pair<Relation,vs> > prs = reader->readFiles(data_r,data_s);
	delete reader;

	r = prs.first.first;
	s = prs.second.first;

	colr = prs.first.second;
	cols = prs.second.second;
	if(r.size()==0) {
		cout<<"The source relation is empty"<<endl;
		exit(0);
	}
	if(s.size()==0) {
		cout<<"The target relation is empty"<<endl;
		exit(0);
	}
	if(r[0].size()>s[0].size()) {
		cout<<"The number of attributes of source relation is bigger "
			<<"than the number of attributes of target relation"<<endl;
		exit(0);
	}
}

void computeMapping(){
	readFiles();
	
	// compute mapping
	Mapping* mapping = new Mapping();
	vector<pair<uint32_t, uint32_t> >  f = mapping->SR2TR(r,s,satisfaction);

	mapping->print_results(colr,cols);
}

