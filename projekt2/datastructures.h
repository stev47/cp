#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

#include <string>
#include <list>
#include <vector>
#include "math.h"

using namespace std;

class Edge;

struct Vertex : Vector {
	// Dirichletwert
	double dirichlet;
	// Angrenzende Kanten im Polynomzug
	Edge *previous, *next;

	Vertex operator+ (const Vector &v);
	
	Vertex (double x, double y, double dirichlet)
		: dirichlet(dirichlet), Vector(x, y) {}
};

struct Edge {
	// Eckpunkte
	Vertex *v1, *v2;
	// Neumannwert
	double neumann;
	int unterteilung;

	// Ermittle den Mittelpunkt
	Vector get_center();
	// Ermittle den Normalenvektor zu dieser Kante
	Vector get_normal();

	Vector get_interpoint(double t);
	
	Edge (Vertex *v1, Vertex *v2, double neumann, int unterteilung);
};

class Domain {
	private:
		// Eine Zeile einlesen (Knoten und Neumanndaten der nächsten Kante)
		pair<Vertex, double> parse_line(string line);
		// Importiert einen Polygonzug
		void import(string file);

	public:
		// Knotenliste
		list<Vertex*> vertices;
		
		// Funktion für die Dirichletdaten
		double dirichlet(Vertex& v);
		// Funktion für die Nemanndaten
		double neumann(Edge& e);

		// Exportiert einen Polygonzug in eine Datei
		void write_to_obj(string file);
		// Berechnet die Fläche
		double calculate_area();

		void refine();
		
		vector<double> get_x_coordinates();
		
		vector<double> get_y_coordinates();

		// Kontruktor, der aus einer Datei den Polygonzug einliest
		Domain(string file);
};


#endif
