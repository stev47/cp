#include <iostream>
#include "datastructures.h"
#include <vector>


using namespace std;

Domain::Domain(string file) {
	import(file);

}

Domain::Domain() {
	

}

Domain::import(string file) {
	fstream f(file.c_str());
	f.open(file.c_str(), ios::in);
	
	getLineIntoTokens(f);

}

Domain::getLineIntoTokens(istream& str){

	string line;
	getline(str, line);
	
	stringstream lineStream(line);
	string cell;


	vector<string> result;
	while ( getline(lineStream, cell, ',') ) {
		result.push_back(cell);
		
	}
	return(result);
}