#include "Reader.h"


pair< pair<Relation, vs>,pair<Relation, vs> > Reader::readFiles(const char* data_r,const char* data_s){
	Relation r,s;
	vs cr, cs;
	read(data_r, r, cr);
	read(data_s, s, cs);
	return make_pair(make_pair(r,cr), make_pair(s,cs));
}

void Reader::read(const char* data, Relation& relation, vs& attrName){

	// search the column names in the input data
	char _cDelim = '\0';
	ReadTextFile textFile(_cDelim);
	if ( ! textFile.openTextFile(data, attrName) )
		return;

	// array used to find the error measurement associated to a certain parameter
	// i.e. if A is an attribute, search for err_A
	vector<pair<int,int> > aux;

	// array used to check if an attribute was already taken into consideration
	vector<bool> vis(attrName.size(),false);

	// array of names of columns without error measures ("err_A")
	vs attrNameWithoutErrors;

	for(uint32_t i=0;i<attrName.size();++i) {
		bool found = false;

		// we check if the error is in the array of attributes
		string s = "err_"+attrName[i];

		for(uint32_t j=0;j<attrName.size();++j) {
			if(attrName[j]==s) {
				found = true;
				aux.push_back(make_pair(i,j));
				attrNameWithoutErrors.push_back(attrName[i]);
				vis[i] = true;
				vis[j] = true;
				break;
			}
		}
		// if it is not the case
		if(!found && !vis[i]) aux.push_back(make_pair(i,-1)),vis[i] = true, attrNameWithoutErrors.push_back(attrName[i]);
	}

	attrName = attrNameWithoutErrors;

	// generate the relation
	vector<string> vstring;
	while(textFile.getline(vstring)){
		vector<Interval> new_attribute;
		for(uint32_t i=0;i<aux.size();++i){
			double value;
 			sscanf(vstring[aux[i].first].c_str(), "%lf", &value);
			if(aux[i].second!=-1)
			{
				double error;
				sscanf(vstring[aux[i].second].c_str(), "%lf", &error);
				error = abs(error);
				new_attribute.push_back(Interval(value-error,value+error));
			}
			else new_attribute.push_back(Interval(value,value));
		}
		relation.push_back(new_attribute);
	}
}