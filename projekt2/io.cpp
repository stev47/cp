#include <iostream>
#include <fstream>
#include "datastructures.h"


using namespace std;

void Domain::import (string file) {
	// Datei öffnen
	ifstream ifs( file.c_str() );

	double x, y, dirichlet, neumann;
	int unterteilung, prev_unterteilung;
	Vertex *previous_vertex, *current_vertex;

	// Ersten Knoten auslesen
	ifs >> x >> y >> dirichlet >> neumann >> unterteilung;
	cout << "x: " << x << ", y: " << y << ", d: " << dirichlet << ", n: " << neumann << ", Unterteilung: "<< unterteilung <<endl;

	// Erstellen und eintragen
	current_vertex = new Vertex(x, y, dirichlet);
	vertices.push_back(current_vertex);

	previous_vertex = current_vertex;

	// Tolle While-Schleife
	while (true) {
		double previous_neumann = neumann;

		// Daten auslesen
		prev_unterteilung= unterteilung;
		ifs >> x >> y >> dirichlet >> neumann >> unterteilung;		

		if (ifs.fail()) {
			// Abbrechen, falls Lesefehler und nicht am Ende der Datei
			if (!ifs.eof()) {
				cerr << "Fehler beim Einlesen der Daten!" << endl;
				return;
			} else 
				break;
		} else
			cout << "x: " << x << ", y: " << y << ", d: " << dirichlet << ", n: " << neumann  << ", Unterteilung: "<< unterteilung << endl;

		// Knoten erstellen
		current_vertex = new Vertex(x, y, dirichlet);
		vertices.push_back(current_vertex);

		// Kante zum vorhergehenden Knoten aufbauen
		Edge* last_edge = new Edge(previous_vertex, current_vertex, previous_neumann, prev_unterteilung);
		
		previous_vertex = current_vertex;
	}
	// Letzten Knoten zum Anfang hin verbinden
	new Edge(previous_vertex, vertices.front(), neumann, unterteilung);
}

void Domain::write_to_obj (string file) {
	remove( file.c_str() );
	ofstream ofs( file.c_str() );

	// Knoten ausgeben
	for (
		list<Vertex*>::iterator v_it = vertices.begin();
		v_it != vertices.end();
		v_it++
	) {
		ofs << "v " << (*v_it)->previous->v1->x << " " << (*v_it)->next->v2->y << " 0" << endl;
	}
	
	// Kantenlinien zeichnen
	for (int i = 2; i <= vertices.size(); i++) {
		ofs << "l " << (i - 1) << " " << i << endl;
	}
	ofs << "l " << vertices.size() << " " << 1 << endl;

		// Knoten ausgeben
	for (int i = 1; i <= vertices.size(); i++) {
		ofs << "p " << i << endl;
	}
}
