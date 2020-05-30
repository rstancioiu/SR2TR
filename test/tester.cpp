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
    
#include "ReadTextFile.h"
#include "Bitset.h"
#include "Util.h"
#include <bits/stdc++.h>

using namespace std;

const char* data_r;
vs col;
void read(const char* data_r);

int main(int args, char* argv[]){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	data_r = argv[1];
	read(data_r);
	return 0;
}

void read(const char* data_r)
{
	char _cDelim = '\0';
	ReadTextFile textfile(_cDelim);
	if( ! textfile.openTextFile(data_r,col)) return;
	vector<string> vstring;
	ofstream target("target1.csv");
	ofstream source("source1.csv");
	target<<col[0];source<<col[0];
	for(uint32_t i=1;i<col.size();++i){target<<","<<col[i];source<<","<<col[i];}
	target<<endl;
	source<<endl;
	int p = 0;
	while(textfile.getline(vstring)){
		vector<double> values;
		for(uint32_t i=0;i<vstring.size();++i)
			values.push_back(atof(vstring[i].c_str()));
		bool neg = false;
		for(uint32_t i=0;i<values.size();++i)
			if(values[i]<-20 || (col[i][0]=='e' && col[i][1]=='r' && values[i]>20)) neg = true;
		if(neg)
		{
			source<<vstring[0];
			for(uint32_t i=1;i<values.size();++i)
				source<<","<<vstring[i];
			source<<endl;
		}
		else
		{
			p++;
			target<<vstring[0];
			for(uint32_t i=1;i<values.size();++i)
				target<<","<<vstring[i];
			target<<endl;
		}
	}
	target.close();
	source.close();
}
