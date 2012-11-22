#include <cmath>
#include <list>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "net.h"

Vertex* Net::new_vertex (double x, double y, double z) {
	Vertex* v = new Vertex(x, y, z);
	this->vertices.push_back(v);
	return v;
}

Vertex* Net::new_vertex (double t) {
	Vertex* v = new Vertex( f(t) );
	this->vertices.push_back(v);
	return v;
}

Edge* Net::new_edge (Vertex* v1, Vertex* v2, bool margin) {
	Edge* e = new Edge(v1, v2, margin);
	//this->edges.push_back(e);
	return e;
}

Triangle* Net::new_triangle (Vertex* v1, Vertex* v2, Vertex* v3, Edge* e1, Edge* e2, Edge* e3) {
	Triangle* t = new Triangle(v1, v2, v3, e1, e2, e3);
	this->triangles.push_front(t);	// Wichtig! (Beim Durchlaufen einer Liste)
	return t;
}

/**
 * Aufbau des Anfangsdreiecks
 */
void Net::init () {
	Vertex* v1 = this->new_vertex(0.0);
	Vertex* v2 = this->new_vertex(1.0 / 3);
	Vertex* v3 = this->new_vertex(2.0 / 3);

	Triangle* t = this->new_triangle(
		v1, v2, v3,
		this->new_edge(v2, v3, true),
		this->new_edge(v1, v3, true),
		this->new_edge(v1, v2, true)
	);
}

void Net::print (std::string file) {
	remove(file.c_str());
	fstream f(file.c_str());
	f.open(file.c_str(), ios::out);
	f.setf(ios::fixed, ios::floatfield);
	f.precision(5);

	/*
	 * Ausgabe der Dreiecksknoten
	 */
	unsigned int i = 1;
	for (list<Vertex*>::iterator it = this->vertices.begin(); it != this->vertices.end(); it++) {
		f << "v " << (*it)->x << " " << (*it)->y << " " << (*it)->z << endl;
		(*it)->id = i++;
	}

	/*
	 * Ausgabe der Kurve
	 * Wir zerlegen die Kurve in Teilkurven für die Ausgabe,
	 * weil Paraview nicht so viele Punkte pro Linie unterstützt.
	 */
	int curve_output_begin = i;
	int curve_output = curve_output_begin;
	double t = 0;
	while (t < 1) {
		while (i - curve_output < OUT_MAX_CURVE_POINTS && t < 1) {
			Vertex v = this->f(t);
			f << "v " << v.x << " " << v.y << " " << v.z << endl;
			i++;
			t += OUT_CURVE_STEP;
		}
		f << "l";
		while (curve_output < i) {
			f << " " << curve_output++;
		}
		curve_output--;
		f << endl;
	}
	f << "l " << curve_output << " " << curve_output_begin << endl;

	/*
	 * Ausgabe der Dreiecksflächen
	 */
	for (list<Triangle*>::iterator it = this->triangles.begin(); it != this->triangles.end(); it++) {
		f << "f " << (*it)->v1->id << " " << (*it)->v2->id << " " << (*it)->v3->id << endl;
	}

	f.close();
}

void Net::refine_mesh () {
	for (
			list<Triangle*>::iterator t_it = this->triangles.begin();
			t_it != this->triangles.end(); 
	) {
		Triangle& t = *(*t_it);	// Aktuelles Dreieck

		// Kanten halbieren (dabei werden die Teilkanten erstellt)
		bool e1_halved = this->halve_edge(t.e1);
		bool e2_halved = this->halve_edge(t.e2);
		bool e3_halved = this->halve_edge(t.e3);

		// Neue innere Kanten erzeugen
		Edge* ei1 = this->new_edge(t.e2->m, t.e3->m);
		Edge* ei2 = this->new_edge(t.e1->m, t.e3->m);
		Edge* ei3 = this->new_edge(t.e1->m, t.e2->m);

		// Neue Dreiecke erzeugen
		this->new_triangle(		// Linkes Dreieck
				t.v1, t.e3->m, t.e2->m,
				ei1, t.e2->subedge(t.v1), t.e3->subedge(t.v1)
			);
		this->new_triangle(		// Rechtes Dreieck
				t.v2, t.e1->m, t.e3->m,
				ei2, t.e3->subedge(t.v2), t.e1->subedge(t.v2)
			);
		this->new_triangle(		// Oberes Dreieck
				t.v3, t.e2->m, t.e1->m,
				ei3, t.e1->subedge(t.v3), t.e2->subedge(t.v3)
			);
		this->new_triangle(		// Inneres Dreieck
				t.e1->m, t.e2->m, t.e3->m,
				ei1, ei2, ei3
			);

		// Aufräumen
		this->triangles.erase(t_it++);

		t.v1->remove_triangle(&t);
		t.v2->remove_triangle(&t);
		t.v3->remove_triangle(&t);
		delete &t;

		if (!e1_halved) 
			delete t.e1;
		if (!e2_halved) 
			delete t.e2;
		if (!e3_halved) 
			delete t.e3;
	}
}

/**
 * Halbiert eine Kante
 *
 * Erstellt Mittelpunkt und Teilkanten. Gibt true zurück, falls halbiert wurde
 * und false, falls die Kante bereits halbiert war.
 */
bool Net::halve_edge (Edge* e) {
	if (e->is_halved())
		return false;

	if (e->is_margin()) {
		// Neuen Punkt auf der Kurve berechnen
		double t1 = e->v1->t;
		double t2 = e->v2->t;

		// Parameter-Mittelungs-Magic
		double t = (t1 + t2) / 2;
		if (fabs(t1 - t2) > 0.5) 
			t += 0.5;
		if (t > 1)
			t -= 1;

		e->m = this->new_vertex(t);
	} else {
		// Mittelpunkt
		e->m = this->new_vertex(
				(e->v1->x + e->v2->x) / 2,
				(e->v1->y + e->v2->y) / 2,
				(e->v1->z + e->v2->z) / 2
			);
	}

	// Neue Kanten erzeugen
	// Die Teilkanten sind genau dann Randkanten, wenn die
	// aktuelle Kante eine Randkante ist
	e->s1 = this->new_edge(e->v1, e->m, e->is_margin());
	e->s2 = this->new_edge(e->m, e->v2, e->is_margin());

	return true;
}

void Net::minimize_mesh(){ //list<Vertex*> vertices;
	for ( 
		list<Vertex*>::iterator v_it = this->vertices.begin();
		v_it != this->vertices.end();
		v_it++
	) { 
		Vertex& v = *(*v_it);
	
		if (!v.is_margin()){
			Vector gradient(0, 0, 0);

			// Gradienten der umliegenden Dreiecksflächen aufsummieren
			for (list<Triangle*>::iterator t_it = v.triangles.begin(); t_it != v.triangles.end(); t_it++)
				gradient += v.get_gradient(*t_it);

			// Halbiere den Gradienten so lange, bis eine Verbesserung eintritt
			while (v.get_surrounding_surface(gradient) > v.get_surrounding_surface())
				gradient *= 0.5;

			v += gradient;
		}
	}
}

double Net::Surface() {
	double surface = 0;
	for (
		list<Triangle*>::iterator t_it = this->triangles.begin();
		t_it != this->triangles.end();
		t_it++
	) {
		Triangle& t = *(*t_it);
		
		// Kreuzprodukt beider Seiten ...
		Vector n = ( *t.v1 - *t.v2 ) ^ ( *t.v1 - *t.v3 );
		// ... halbiert ergibt die Fläche des Dreiecks
		surface += (0.5 * n.norm());
	}
	return surface;
}
