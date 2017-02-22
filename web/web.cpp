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
   cout<< "<meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
   cout<< "<link rel=\"stylesheet\" href=\"/lib/w3.css\">";
   cout<< "<link rel=\"stylesheet\" href=\"https://fonts.googleapis.com/css?family=Lato\">";
   cout<< "<link rel=\"stylesheet\" href=\"https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css\">";
   cout<<"<style> html,body,h1,h2,h3,h4 {font-family:\"Lato\",sans-serif}.mySlides {display:none}.w3-tag, .fa {cursor:pointer}.w3-tag {height:15px;width:15px;padding:0;margin-top:6px}</style>\n";
   cout << "<head>\n";
   cout << "<title>Results</title>\n";
   cout << "</head>\n";
   cout << "<body>\n";
   cout<< "<div class=\"w3-content\" style=\"max-width:1100px;margin-top:80px;margin-bottom:80px\">\n";
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

   computeMapping();

   cout << "</div>\n";
   cout << "</body>\n";
   cout << "</html>\n";

   return 0;
}

void writeFile(const char* name, string data) {
	 ofstream outputFile(name);
	if(outputFile.is_open())
	cout<<"<p> We write a file "<<name <<" </p>\n";
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
	vector<pair< uint32_t, uint32_t> >  f = mapping->SR2TR(r,s,satisfaction);

	mapping->print_results_web(colr,cols);
}

