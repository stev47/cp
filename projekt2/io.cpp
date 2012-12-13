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

	// Neuman bzw. Dirichletfunktion abfragen ob vorhanden
	ifs >> dirichletf >> neumannf;
	
	cout << "Dirichletfunktion vorhanden: " << dirichletf << ", Neumannfunktion vorhanden: " << neumannf << endl;
	
	// Ersten Knoten auslesen
	ifs >> x >> y >> dirichlet >> neumann >> unterteilung;

	// Erstellen und eintragen
	if(dirichletf == true) {
		dirichlet = get_dirichlet(x, y);
	}

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
		}

		if(dirichletf == true){
			dirichlet = get_dirichlet(x, y);
		}
		// Knoten erstellen
		current_vertex = new Vertex(x, y, dirichlet);
		vertices.push_back(current_vertex);

		if(neumannf == true){
			previous_neumann = get_neumann(previous_vertex->x, current_vertex->x, previous_vertex->y, current_vertex->y);
		}
		// Kante zum vorhergehenden Knoten aufbauen
		Edge* last_edge = new Edge(previous_vertex, current_vertex, previous_neumann, prev_unterteilung);
		previous_vertex = current_vertex;
	}
	if(neumannf == true){
		neumann = get_neumann(previous_vertex->x, vertices.front()->x, previous_vertex->y, vertices.front()->y);
	}
	// Letzten Knoten zum Anfang hin verbinden
	new Edge(previous_vertex, vertices.front(), neumann, unterteilung);

	cout.setf(ios::fixed, ios::floatfield);
	cout.precision(2);
	for (
		list<Vertex*>::iterator v_it = vertices.begin();
		v_it != vertices.end();
		v_it++
	) {
		cout << "x: " << (*v_it)->x << " y: " << (*v_it)->y << " d: " << (*v_it)->dirichlet << " n: " << (*v_it)->next->neumann << " u: " << (*v_it)->next->unterteilung << endl;
	}
}

void Domain::write_to_obj (string file) {
	remove( file.c_str() );
	ofstream ofs( file.c_str() );
	cout.setf(ios::fixed, ios::floatfield);
	cout.precision(2);

	// Knoten ausgeben
	for (
		list<Vertex*>::iterator v_it = vertices.begin();
		v_it != vertices.end();
		v_it++
	) {
		ofs << "v " << (*v_it)->previous->v1->x << " " << (*v_it)->next->v2->y << " 0" << endl;
		cout << "x: " << (*v_it)->x << " y: " << (*v_it)->y << " d: " << (*v_it)->dirichlet << " n: " << (*v_it)->next->neumann << " u: " << (*v_it)->next->unterteilung << endl;
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
