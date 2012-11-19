#include <iostream>
#include <list>
#include <cstddef>
#include "datastructures.h"

using namespace std;

/*
 * Vertex
 */
bool Vertex::is_margin () {
	return (this->t >= 0);
}
void Vertex::add_triangle (Triangle* t) {
	this->triangles.push_back(t);		
}
void Vertex::remove_triangle (Triangle* t) {
	this->triangles.remove(t);		
}
Vertex Vertex::operator+= (const Vector &v) {
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
	return *this;
}

Vector Vertex::get_gradient (Triangle* t) {
	pair<Vertex*, Vertex*> p = t->get_remote_points(this);
	Vertex p1 = *p.first;
	Vertex p2 = *p.second;
	
	return ((*this - p1) ^ (*this - p2)) ^ (p1 - p2);
}

double Vertex::get_surrounding_surface (Vector delta) {
	double surface = 0;
	for (
		list<Triangle*>::iterator t_it = this->triangles.begin();
		t_it != this->triangles.end();
		t_it++
	){
		pair<Vertex*, Vertex*> p = (*t_it)->get_remote_points(this);
	
		Vector m = ( (*this + delta) - *p.first ) ^ ( (*this + delta) - *p.second );
		surface += (0.5 * m.norm());
	}
	return surface;
}

/*
 * Edge
 */
bool Edge::is_halved () {
	return (this->m != NULL);
}
Edge* Edge::subedge (Vertex* v) {
	if (v == this->v1) 
		return this->s1;
	if (v == this->v2)
		return this->s2;
	return NULL;
}

/*
 * Triangle
 */
Triangle::Triangle(Vertex* v1, Vertex* v2, Vertex* v3, 
			Edge* e1, Edge* e2, Edge* e3)
		: v1(v1), v2(v2), v3(v3), e1(e1), e2(e2), e3(e3) {
	v1->add_triangle(this);
	v2->add_triangle(this);
	v3->add_triangle(this);
}

pair<Vertex*, Vertex*> Triangle::get_remote_points(Vertex* v) {
	if (v == this->v1) {
		return pair<Vertex*, Vertex*>(this->v2, this->v3);
	} else if (v == this->v2) {
		return pair<Vertex*, Vertex*>(this->v1, this->v3);
	} else if (v == this->v3) {
		return pair<Vertex*, Vertex*>(this->v2, this->v1);
	} else {
		cout << "Methode get_remote_points() falsch aufgerufen!" << endl;
	}
}
