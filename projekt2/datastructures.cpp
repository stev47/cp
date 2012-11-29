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
	vector<string> line=getLineIntoTokens(f);

	//überprüfung ob genug einträge fehlt


	istringstream tmp;
while(line.size() < 4)
	line=getLineIntoTokens(f);

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
	//neumann wert für nächste erstellte kante
	tmp.clear();
	tmp.str(line[3]);
	double neumann;
	tmp >> neumann;
	
	vertices.push_back(Vertex(x, y, d));
	Vertex* v_prev = &(vertices.back());
	
	while (!f.eof()){
		line=getLineIntoTokens(f);

		if (line.size() < 4)
			continue;
		

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
		//Edge erstellen
		Edge *edge = new Edge(v_prev,&vertices.back(), neumann);
		v_prev->next=edge;
		(vertices.back()).previous=edge;
		//edge fertig

		//Neumann Wert für nächste erstellte kante(im nächsten Schleifen-Durchlauf, oder auserhalb)
		tmp.clear();
		tmp.str(line[3]);
		tmp >> neumann;

		//Vertex als vorherigen eintragen
		v_prev = &(vertices.back());
		
	}
	//letzten Vertex mit erstem verbinden (den Polygonenzug schließen)
	//Edge erstellen
	Edge* edge = new Edge(v_prev,&(*vertices.begin()), neumann);
	v_prev->next=edge;
	(*vertices.begin()).previous=edge;
	//testdurchlauf und ausgabe
	for (list<Vertex>::iterator it = vertices.begin(); it != vertices.end(); it++) {
		//cout<< (*it)
		cout << (*it).previous->v1->x;
		cout << (*it).x;
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