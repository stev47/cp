#include <iostream>
#include <fstream>
#include <sstream>
#include "datastructures.h"
#include <vector>


using namespace std;

Domain::Domain(string file) {
	import(file);

}

void Domain::import(string file) {
	fstream f(file.c_str());
	//f.open(file.c_str(), ios::in);
	//getLineIntoTokens(f);
	while (!f.eof()){
		vector<string> line=getLineIntoTokens(f);

		if (line.size() < 4)
			continue;
		
		cout << "test";		
		istringstream tmp;

		tmp.str(line[0]);
		double x;
		tmp >> x;

		
		tmp.clear();
		tmp.str(line[1]);
		double y;
		tmp >> y;


		tmp.clear();
		tmp.str(line[2]);
		double d;
		tmp >> d;

		
		vertices.push_back(Vertex(x, y, d));
		
	}
	list<Vertex>::iterator it = this->vertices.begin();
	Vertex& previous = *it++;
	while (it != this->vertices.end()) {
		Vertex& current = *it;

		Edge& edge = new Edge(previous, next, );
	}
}

vector<string> Domain::getLineIntoTokens(istream& str){

	string line;
	getline(str, line);
	
	stringstream lineStream(line);
	string cell;


	vector<string> result;
	while ( getline(lineStream, cell, ',') ) {
		result.push_back(cell);
		
	}
	return result;
}