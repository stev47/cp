#include <cmath>
#include <list>
#include <iostream>
#include <fstream>
#include "net.h"

Vertex* Net::new_vertex (double x, double y, double z) {
	this->vertices.push_back(new Vertex(x,y,z));
	return this->vertices.back();
}
Vertex* Net::new_vertex (double t) {
	this->vertices.push_back(new Vertex(this->f(t)));
	return this->vertices.back();
}
Edge* Net::new_edge (Vertex* v1, Vertex* v2, bool margin) {
	this->edges.push_back(new Edge(v1, v2, margin));
	return this->edges.back();
}
Triangle* Net::new_triangle (Vertex* v1, Vertex* v2, Vertex* v3, Edge* e1, Edge* e2, Edge* e3) {
	this->triangles.push_front(new Triangle(v1, v2, v3, e1, e2, e3));
	Triangle* t = this->triangles.front();
	//Dreieck in Knoten-Dreieckslisten eintragen 
	t->v1->add_triangle(t);
	t->v2->add_triangle(t);
	t->v3->add_triangle(t);
	return t;
}

/**
 * Beginne mit einem Dreieck
 */
void Net::init () {
	Vertex* v1 = this->new_vertex(0.0);
	Vertex* v2 = this->new_vertex(1.0/3);
	Vertex* v3 = this->new_vertex(2.0/3);

	Edge* e1 = this->new_edge(v2, v3, true);
	Edge* e2 = this->new_edge(v1, v3, true);
	Edge* e3 = this->new_edge(v1, v2, true);

	Triangle* t = this->new_triangle(v1, v2, v3, e1, e2, e3);

	v1->add_triangle(t);
	v2->add_triangle(t);
	v3->add_triangle(t);
}

void Net::print () {
	unsigned int i = 1;
	remove("test.obj");
	fstream f("test.obj");
	f.open("test.obj", ios::out);
	f.setf(ios::fixed, ios::floatfield);
	f.precision(5);
	for (list<Vertex*>::iterator it = this->vertices.begin(); it != this->vertices.end(); it++) {
		f << "v " << (*it)->x << " " << (*it)->y << " " << (*it)->z << endl;
		(*it)->id = i++;
	}
	int curve_begin = i;
	for (double t = 0; t < 1; t += 0.008) {
		Vertex v = this->f(t);
		f << "v " << v.x << " " << v.y << " " << v.z << endl;
		i++;
	}
	int curve_end = i - 1;
	f << "l";
	for (int i = curve_begin; i <= curve_end; i++) {
		f << " " << i;
	}
	f << " " << curve_begin;

	f << endl;
	for (list<Triangle*>::iterator it = this->triangles.begin(); it != this->triangles.end(); it++) {
		f << "f " << (*it)->v1->id << " " << (*it)->v2->id << " " << (*it)->v3->id << endl;
	}
	/*for (list<Vertex*>::iterator it = this->vertices.begin(); it != this->vertices.end(); it++) {
		f << "p " << (*it)->id << endl;
	}*/

	f.close();
}

void Net::refine_mesh () {
	for (
			list<Triangle*>::iterator it = this->triangles.begin();
			it != this->triangles.end(); 
		)	{
		Triangle* t = (*it);	// Aktuelles Dreieck

		// Kanten halbieren (dabei werden die Teilkanten erstellt)
		bool e1_halved = this->halve_edge(t->e1);
		bool e2_halved = this->halve_edge(t->e2);
		bool e3_halved = this->halve_edge(t->e3);
		// Neue innere Kanten erzeugen
		Edge* ei1 = this->new_edge(t->e2->m, t->e3->m);
		Edge* ei2 = this->new_edge(t->e1->m, t->e3->m);
		Edge* ei3 = this->new_edge(t->e1->m, t->e2->m);
		// Neue Dreiecke erzeugen
		this->new_triangle(		// Linkes Dreieck
				t->v1, t->e3->m, t->e2->m,
				ei1, t->e2->subedge(t->v1), t->e3->subedge(t->v1)
				);
		this->new_triangle(		// Rechtes Dreieck
				t->v2, t->e1->m, t->e3->m,
				ei2, t->e3->subedge(t->v2), t->e1->subedge(t->v2)
				);
		this->new_triangle(		// Oberes Dreieck
				t->v3, t->e2->m, t->e1->m,
				ei3, t->e1->subedge(t->v3), t->e2->subedge(t->v3)
				);
		this->new_triangle(		// Inneres Dreieck
				t->e1->m, t->e2->m, t->e3->m,
				ei1, ei2, ei3
				);

		// Aufräumen

		this->triangles.erase(it++);
		t->v1->remove_triangle(t);
		t->v2->remove_triangle(t);
		t->v3->remove_triangle(t);
		delete t;

		if (!e1_halved) {
			this->edges.remove(t->e1);
			delete t->e1;
		}
		if (!e2_halved) {
			this->edges.remove(t->e2);
			delete t->e2;
		}
		if (!e3_halved) {
			this->edges.remove(t->e3);
			delete t->e3;
		}
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

	Vertex* m;

	if (e->is_margin()) {
		// Neuen Punkt auf der Kurve berechnen
		double t1 = e->v1->t;
		double t2 = e->v2->t;

		double t = (t1 + t2) / 2;
		if (fabs(t1 - t2) > 0.5) 
			t += 0.5;
		if (t > 1)
			t -= 1;

		m = this->new_vertex(t);
	} else {
		// Mittelpunkt
		m = this->new_vertex(
				(e->v1->x + e->v2->x) / 2,
				(e->v1->y + e->v2->y) / 2,
				(e->v1->z + e->v2->z) / 2
				);
	}
	// Der Kante den Mittelpunkt zuweisen
	e->m = m;

	// Neue Kanten erzeugen
	// Die Teilkanten sind genau dann Randkanten, wenn die
	// aktuelle Kante eine Randkante ist
	e->s1 = this->new_edge(e->v1, e->m, e->is_margin());
	e->s2 = this->new_edge(e->m, e->v2, e->is_margin());

	return true;
}

Vector Net::Gradient(Vertex* v, Triangle* t) {
		
	pair<Vertex*,Vertex*> p = t->rem_points(v);
	Vertex p1 = *p.first;
	Vertex p2 = *p.second;
	
	Vector n = (*v - p1) ^ (*v - p2);
	Vector g = (n / n.norm()) ^ (p1 - p2);
	return g;
}

void Net::minimize_mesh(){ //list<Vertex*> vertices;
	for (  list<Vertex*>::iterator it = this->vertices.begin();
			it != this->vertices.end(); it++)	{ 
		Vertex* v = *it;
	
		if (!v->is_margin()){
			Vector gradient(0, 0, 0);
			// Gradienten der umliegenden Dreiecksflächen aufsummieren
			for (list<Triangle*>::iterator t = v->triangles.begin(); t != v->triangles.end(); t++)
				gradient += Gradient(v, *t);

			Vector delta = gradient;
			while (VSurface(v, delta) > VSurface(v, Vertex(0, 0, 0)))
				delta *= 0.5;

			*v += delta;
		}
	}
}

double Net::Surface() {
	double surf = 0;
	for (
		list<Triangle*>::iterator it = this->triangles.begin();
		it != this->triangles.end();
		it++
	) {
		Triangle* t = *it;
		
		pair<Vertex*,Vertex*> p = t->rem_points(t->v1);
		Vertex p1 = *p.first;
		Vertex p2 = *p.second;
		
		Vector n = (*(t->v1) - p1) ^ (*(t->v1) - p2);
		surf += n.norm() / 2;
	}
	return surf;
}

double Net::VSurface(Vertex* v, Vector delta) {
	double surf = 0;
	for (
		list<Triangle*>::iterator it = v->triangles.begin();
		it != v->triangles.end();
		it++
	){
		Triangle* t = *it;
	
		pair<Vertex*,Vertex*> p = t->rem_points(v);
		Vertex p1 = *p.first;
		Vertex p2 = *p.second;
	
		Vector m = ((*v + delta) - p1) ^ ((*v + delta) - p2);
		surf += (m.norm() / 2);
	}
	return surf;
}
