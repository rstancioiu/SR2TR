#include "lib/ReadTextFile.hpp"
#include "lib/Bitset.hpp"

#include <iostream>

const char* data_r;
std::vector<std::string> col;
void read(const char* data_r);

int main(int args, char* argv[]){
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);
	data_r = argv[1];
	read(data_r);
	return 0;
}

void read(const char* data_r)
{
	char _cDelim = '\0';
	ReadTextFile textfile(_cDelim);
	if( ! textfile.openTextFile(data_r,col)) return;
	std::vector<std::string> vstring;
	std::ofstream target("target1.csv");
	std::ofstream source("source1.csv");
	target<<col[0];source<<col[0];
	for(uint32_t i=1;i<col.size();++i){target<<","<<col[i];source<<","<<col[i];}
	target<<std::endl;
	source<<std::endl;
	int p = 0;
	while(textfile.getline(vstring)){
		std::vector<double> values;
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
			source<<std::endl;
		}
		else
		{
			p++;
			target<<vstring[0];
			for(uint32_t i=1;i<values.size();++i)
				target<<","<<vstring[i];
			target<<std::endl;
		}
	}
	target.close();
	source.close();
}
