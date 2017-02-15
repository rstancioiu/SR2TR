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



