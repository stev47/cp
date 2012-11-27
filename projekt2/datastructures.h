#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

#include <string>
#include <list>

using namespace std;

struct Edge;

struct Vertex {
	// Koordinaten des Punktes
	double x, y;
	// Dirichletwert
	double dirichlet;
	// Angrenzende Kanten im Polynomzug
	Edge &previous, &next;
};

struct Edge {
	// Eckpunkte
	Vertex& v1, v2;
	// Neumannwert
	double neumann;

	// Ermittle den Mittelpunkt
	Vertex get_center();
};

class Domain {
	private:
		// Importiert einen Polygonzug
		void import(string file);

	public:
		// Knotenliste
		list<Vertex> vertices;
		
		// Funktion für die Dirichletdaten
		double dirichlet(Vertex& v);
		// Funktion für die Nemanndaten
		double neumann(Edge& e);

		// Kontruktor, der aus einer Datei den Polygonzug einliest
		Domain(string file);
};


#endif