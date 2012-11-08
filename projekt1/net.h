#ifndef NET_H
#define NET_H

#include "datastructures.h"
#include "curves.h"

//template <Curve& curve>
class Net {
	Curves::Curve &curve;
	protected:
		list<Vertex*> vertices;		//!< Knotenliste
		list<Edge*> edges;			//!< Kantenliste
		list<Triangle*> triangles;	//!< Dreiecksliste

	public:
		Net (Curves::Curve &curve) : curve(curve) {};
		/**
		 * Berechne einen Randpunkt auf der Kurve an der Stelle t.
		 * Es muss stets 0 <= t <= 1 gelten.
		 * Wird von einer anderen Klasse implementiert
		 * Mathematisch betrachtet, ist das hier unsere parametrisierte Kurvenfunktion
		 */
		Vertex f (double t) { return curve.f(t); };

		Vertex* new_vertex (double x, double y, double z);
		Vertex* new_vertex (double t);
		Edge* new_edge (Vertex* v1, Vertex* v2, bool margin = false);
		Triangle* new_triangle (Vertex* v1, Vertex* v2, Vertex* v3, Edge* e1, Edge* e2, Edge* e3);

		/**
		 * Beginne mit einem Dreieck
		 */
		virtual void init (); 

		void print (std::string file);

		void refine_mesh ();
		/**
		 * Halbiert eine Kante
		 *
		 * Erstellt Mittelpunkt und Teilkanten. Gibt true zurück, falls halbiert wurde
		 * und false, falls die Kante bereits halbiert war.
		 */
		bool halve_edge (Edge* e);

		Vertex cross_product(Vertex v1, Vertex v2);
		double Vertex_Value(Vertex v1);
		Vertex sub(Vertex v1, Vertex v2);
		Vertex add(Vertex v1, Vertex v2, double n=1.0);

		Vertex norm(Vertex v);

		Vector Gradient(Vertex* v1, Triangle* t1);
		void minimize_mesh();
		double Surface(); 
		double VSurface(Vertex* v, Vector delta);
};


#endif
