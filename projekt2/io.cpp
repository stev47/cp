#include <iostream>
#include <fstream>
#include "datastructures.h"


using namespace std;

void Domain::import (string file) {
	// Datei öffnen
	ifstream ifs( file.c_str() );

	double x, y, dirichlet, neumann;
	Vertex *previous_vertex, *current_vertex;

	// Ersten Knoten auslesen
	ifs >> x >> y >> dirichlet >> neumann;		
	cout << "x: " << x << ", y: " << y << ", d: " << dirichlet << ", n: " << neumann << endl;

	// Erstellen und eintragen
	current_vertex = new Vertex(x, y, dirichlet);
	vertices.push_back(current_vertex);

	previous_vertex = current_vertex;

	// Tolle While-Schleife
	while (true) {
		double previous_neumann = neumann;

		// Daten auslesen
		ifs >> x >> y >> dirichlet >> neumann;		

		if (ifs.fail()) {
			// Abbrechen, falls Lesefehler und nicht am Ende der Datei
			if (!ifs.eof()) {
				cerr << "Fehler beim Einlesen der Daten!" << endl;
				return;
			} else 
				break;
		} else 
			cout << "x: " << x << ", y: " << y << ", d: " << dirichlet << ", n: " << neumann << endl;

		// Knoten erstellen
		current_vertex = new Vertex(x, y, dirichlet);
		vertices.push_back(current_vertex);

		// Kante zum vorhergehenden Knoten aufbauen
		Edge* last_edge = new Edge(previous_vertex, current_vertex, previous_neumann);
		
		previous_vertex = current_vertex;
	}
	// Letzten Knoten zum Anfang hin verbinden
	new Edge(previous_vertex, vertices.front(), neumann);
}

void Domain::write_to_obj (string file) {
	ofstream ofs( file.c_str() );
	
	// Knoten ausgeben
	for (
		list<Vertex*>::iterator v_it = vertices.begin();
		v_it != vertices.end();
		v_it++
	) {
		ofs << "v " << (*v_it)->x << " " << (*v_it)->y << " 0" << endl;
	}
	
	// Kantenlinien zeichnen
	for (int i = 2; i <= vertices.size(); i++) {
		ofs << "l " << (i - 1) << " " << i << endl;
	}
	ofs << "l " << vertices.size() << " " << 1 << endl;
}
