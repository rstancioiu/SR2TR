#include "Reader.h"
#include "Util.h"
#include "Mapping.h"

#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>

#include <cgicc/CgiDefs.h>
#include <cgicc/Cgicc.h>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>


using namespace std;
using namespace cgicc;

const char* data_r;
const char* data_s;
int satisfaction;
Relation r,s;
uint32_t n,m;
vs colr,cols;
void computeMapping();
bool readFiles();
void writeFile(const char* name, string data);

int main() {
   Cgicc cgi;

   cout << "Content-type:text/html\r\n\r\n";
   cout << "<html>\n";
   cout << "<head>\n";
   cout << "<title>File Upload in CGI</title>\n";
   cout << "</head>\n";
   cout << "<body>\n";

   form_iterator fi = cgi.getElement("satisfaction");
   if( !fi->isEmpty() ) {
   		string chosen_satisfaction = (**fi);
   		if(chosen_satisfaction == "classical")
   			satisfaction = 1;
   		else 
   			satisfaction = 2;
   }

   // get list of files to be uploaded
   // get list of files to be uploaded
   const_file_iterator source = cgi.getFile("source");
   const_file_iterator target = cgi.getFile("target");

   string data_source = source->getData();
   string data_target = target->getData();

   data_r = "source.csv";
   data_s = "target.csv";
   writeFile(data_r, data_source);
   writeFile(data_s, data_target);
   
   cout<<data_source<<endl;
   cout<<data_target<<endl;

   computeMapping();

   cout << "<File uploaded successfully>\n";
   cout << "</body>\n";
   cout << "</html>\n";

   return 0;
}

void writeFile(const char* name, string data) {
	ofstream outputFile(name);
	outputFile<<data;
	outputFile.close();
}

bool readFiles() {
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
		return false;
	}
	if(s.size()==0) {
		cout<<"The target relation is empty"<<endl;
		return false;
	}
	if(r[0].size()>s[0].size()) {
		cout<<"The number of attributes of source relation is bigger "
			<<"than the number of attributes of target relation"<<endl;
		return false;
	}
	
	return true;
}

void computeMapping(){
	bool result = readFiles();
	if(!result) return;
	// compute mapping
	Mapping* mapping = new Mapping();
	vector<pair<int,int> >  f = mapping->SR2TR(r,s,satisfaction);

	mapping->print_results_web(colr,cols);
}

