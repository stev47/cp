#define _USE_MATH_DEFINES	// Nötig für die Konstante M_PI
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
	cout.setf(ios::fixed, ios::floatfield);
	cout.precision(5);
	for (list<Vertex*>::iterator it = this->vertices.begin(); it != this->vertices.end(); it++) {
		cout << "v " << (*it)->x << " " << (*it)->y << " " << (*it)->z << endl;
		f << "v " << (*it)->x << " " << (*it)->y << " " << (*it)->z << endl;
		(*it)->id = i++;
	}
	int curve_begin = i;
	for (float t = 0; t < 1; t += 0.01) {
		Vertex v = this->f(t);
		cout << "v " << v.x << " " << v.y << " " << v.z << endl;
		f << "v " << v.x << " " << v.y << " " << v.z << endl;
		i++;
	}
	int curve_end = i - 1;
	cout << "l";
	f << "l";
	for (int i = curve_begin; i <= curve_end; i++) {
		cout << " " << i;
		f << " " << i;
	}
	cout << endl;
	f << endl;

	for (list<Triangle*>::iterator it = this->triangles.begin(); it != this->triangles.end(); it++) {
		cout << "f " << (*it)->v1->id << " " << (*it)->v2->id << " " << (*it)->v3->id << endl;
		f << "f " << (*it)->v1->id << " " << (*it)->v2->id << " " << (*it)->v3->id << endl;
	}
	for (list<Vertex*>::iterator it = this->vertices.begin(); it != this->vertices.end(); it++) {
		cout << "p " << (*it)->id << endl;
		f << "p " << (*it)->id << endl;
	}
	//anfang Gradienten Test (fügt Test Gradient als Punkt ein) (später löschen) 

	Triangle* t=this->triangles.front();
	Vertex* v=this->vertices.front();
	Vertex g=Gradient(v,t);
	f << "v " << g.x <<" "<< g.y << " " << g.z << endl ;
	f <<"p 105";
	//ende
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

Vertex Net::cross_product(Vertex v1, Vertex v2) {
	//Kreuzprodukt
	Vertex v((v1.y*v2.z)-(v1.z*v2.y),(v1.z*v2.x)-(v1.x*v2.z), (v1.x*v2.y)-(v1.y*v2.x)) ;

	return v;

}

double Net::Vertex_Value(Vertex v1) {
	//Betrag eines Vektors
	return sqrt((v1.x*v1.x)+(v1.y*v1.y)+(v1.z*v1.z));
}

Vertex Net::sub(Vertex v1, Vertex v2){
	Vertex v (v1.x-v2.x,v1.y-v2.y,v1.z-v2.z); 
	return v;
}
Vertex Net::add(Vertex v1, Vertex v2){
	Vertex v (v1.x+v2.x,v1.y+v2.y,v1.z+v2.z); 
	return v;
}

Vertex Net::norm(Vertex v) {
	double n= Vertex_Value(v);
	Vertex r (v.x/n,v.y/n,v.z/n);
	return r;
}

Vertex Net::Gradient(Vertex* v1, Triangle* t1) {
	//Gradient
	Triangle t=*t1;
	pair<Vertex*,Vertex*> p =t.rem_points(v1);
	Vertex p1= *p.first;
	Vertex p2=*p.second;
	Vertex v= *v1;
	Vertex n=cross_product(sub(v,p1),sub(v,p2));
	Vertex g=cross_product(norm(n),sub(p1,p2));
	return g;
}

void Net::minimize_mesh(){ //list<Vertex*> vertices;
	for (  list<Vertex*>::iterator it = this->vertices.begin();
			it != this->vertices.end(); it++)	{ 
		Vertex* v = *it;
		if (!v->is_margin()){
			//cout << "is margin" << endl;
			Vertex gradient(0,0,0);
			//cout << gradient.x << endl;
			for (list<Triangle*>::iterator t=v->triangles.begin();  t!=v->triangles.end(); t++) {
				//cout << gradient.x <<endl;
				gradient=add(gradient,Gradient(v,*t));
				//cout << gradient.x <<endl;
			}
			v->x+=gradient.x*1e-1;
			v->y+=gradient.y*1e-1;
			v->z+=gradient.z*1e-1;

		}

	}
}

double Net::Surface() {
	double surf=0;
	for (list<Triangle*>::iterator it = this->triangles.begin();
			it != this->triangles.end();it++){
		Triangle* t=*it;
		//Vertex v1=t.v1;
		pair<Vertex*,Vertex*> p =t->rem_points(t->v1);
		Vertex p1= *p.first;
		Vertex p2=*p.second;
		Vertex v= *t->v1;
		Vertex n=cross_product(sub(v,p1),sub(v,p2));
		surf+=Vertex_Value(n)/2;
	}
	return surf;
}
