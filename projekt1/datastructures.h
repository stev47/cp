#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

#include <list>
#include <cstddef>
#include "math.h"

using namespace std;

class Triangle;	// forward declaration: wird in Vertex gebraucht
/**
 * Knotenpunkt
 */
class Vertex : public Vector {
	public:
		list<Triangle*> triangles;	//<! Liste von zugehörigen Dreiecken

		unsigned int id;	//<! Index, nur für die Ausgabefunktion nötig
		double t;			//<! Stelle auf der parametrisierten Kurve

		Vertex (double x, double y, double z) 
			: t(-1), Vector(x,y,z) {}
		Vertex (double x, double y, double z, double t)
			: t(t), Vector(x,y,z) {}

		bool is_margin ();

		void add_triangle (Triangle* t);
		void remove_triangle (Triangle* t);

		Vector get_gradient (Triangle* t);
		double get_surrounding_surface (Vector delta = Vector(0, 0, 0));

		Vertex operator+= (const Vector &v);
};

/**
 * Kante
 */
class Edge {
	public:
		Vertex *v1, *v2;		//<! Eckpunkte
		bool margin;			//<! Randkante?

		// Für das Verfeinern nötig:
		Vertex* m;				//<! Neuer Mittelpunkt bei Halbierung
		Edge *s1, *s2;			//<! Neue Kanten bei Halbierung

		Edge (Vertex* v1, Vertex* v2)
			: v1(v1), v2(v2), margin(false), m(NULL) {}
		Edge (Vertex* v1, Vertex* v2, bool margin) 
			: v1(v1), v2(v2), margin(margin), m(NULL) {}

		bool is_halved ();
		bool is_margin () {	return margin; }

		/**
		 * Gibt halbierte Kante an einem Punkt zurück
		 */
		Edge* subedge (Vertex* v);
};

/**
 * Dreieck
 */
class Triangle {
	public:
		Vertex *v1, *v2, *v3;		//<! Eckpunkte
		Edge *e1, *e2, *e3;			//<! Kanten
		Triangle *t1, *t2, *t3;		//<! Angrenzende Dreiecke

		Triangle (Vertex* v1, Vertex* v2, Vertex* v3, Edge* e1, Edge* e2, Edge* e3);

		pair<Vertex*, Vertex*> get_remote_points(Vertex* v);
};

#endif
