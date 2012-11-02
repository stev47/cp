#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

#include <list>
#include <cstddef>

using namespace std;

struct Triangle;	// forward declaration: wird in Vertex gebraucht
/**
 * Knotenpunkt
 */
struct Vertex {
	unsigned int id;	//<! Index, nur für die Ausgabefunktion nötig
	double x, y, z;		//<! Koordinaten (public für die Ausgabe)
	double t;			//<! Stelle auf der parametrisierten Kurve
	list<Triangle*> triangles;	//<! Liste von zugehörigen Dreiecken

	Vertex (double x, double y, double z) 
		: x(x), y(y), z(z), t(-1) {}
	Vertex (double x, double y, double z, double t)
		: x(x), y(y), z(z), t(t) {}

	bool is_margin () {
		return (this->t >= 0);
	}
	void add_triangle (Triangle* t) {
		this->triangles.push_back(t);		
	}
	void remove_triangle (Triangle* t) {
		this->triangles.remove(t);		
	}
};

/**
 * Kante
 */
struct Edge {
	Vertex *v1, *v2;		//<! Eckpunkte
	bool margin;			//<! Randkante?

	// Für das Verfeinern nötig:
	Vertex* m;				//<! Neuer Mittelpunkt bei Halbierung
	Edge *s1, *s2;			//<! Neue Kanten bei Halbierung

	Edge (Vertex* v1, Vertex* v2)
		: v1(v1), v2(v2), margin(false), m(NULL) {}
	Edge (Vertex* v1, Vertex* v2, bool margin) 
		: v1(v1), v2(v2), margin(margin), m(NULL) {}

	bool is_halved () {
		return (this->m != NULL);
	}
	bool is_margin () {
		return margin;
	}
	/**
	 * Gibt halbierte Kante an einem Punkt zurück
	 */
	Edge* subedge (Vertex* v) {
		if (v == this->v1) 
			return this->s1;
		if (v == this->v2)
			return this->s2;
		return NULL;
	}
};

/**
 * Dreieck
 */
struct Triangle {
	Vertex *v1, *v2, *v3;		//<! Eckpunkte
	Edge *e1, *e2, *e3;			//<! Kanten
	Triangle *t1, *t2, *t3;		//<! Angrenzende Dreiecke

	Triangle (Vertex* v1, Vertex* v2, Vertex* v3, Edge* e1, Edge* e2, Edge* e3) 
		: v1(v1), v2(v2), v3(v3), e1(e1), e2(e2), e3(e3) {}
		
	pair<Vertex*&,Vertex*&> rem_points(Vertex* v) {
		if (v == this->v1) 
			return pair<Vertex*&,Vertex*&>(this->v2,this->v3);
		if (v == this->v2)
			return pair<Vertex*&,Vertex*&>(this->v1,this->v3);
		else
		      return pair<Vertex*&,Vertex*&>(this->v2,this->v1);
	}
};

#endif
