#include <iostream>
#include <list>
#include <cstddef>
#include "datastructures.h"

using namespace std;

/*
 * Vertex
 */
bool Vertex::is_margin () {
	return !(this->t < 0);
}
void Vertex::add_triangle (Triangle* t) {
	this->triangles.push_back(t);		
}
void Vertex::remove_triangle (Triangle* t) {
	this->triangles.remove(t);		
}
Vector Vertex::operator- (const Vertex &v) const {
	return Vector(this->x - v.x, this->y - v.y, this->z - v.z);
}
Vertex& Vertex::operator+= (const Vector &v) {
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
	return *this;
}
Vertex& Vertex::operator-= (const Vector &v) {
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
	return *this;
}
Vertex& Vertex::operator*= (const double lambda) {
	this->x *= lambda;
	this->y *= lambda;
	this->z *= lambda;
	return *this;
}
Vertex& Vertex::operator/= (const double lambda) {
	this->x /= lambda;
	this->y /= lambda;
	this->z /= lambda;
	return *this;
}
Vertex& Vertex::operator= (const Vector &v) {
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
	return *this;
}

Vector Vertex::get_gradient (Triangle* t) {
	pair<Vertex*, Vertex*> p = t->get_remote_points(this);
	Vertex& p1 = *p.first;
	Vertex& p2 = *p.second;
	
	Vector h = (*this - p1) ^ (*this - p2);
	
	// Normieren, um den echten Gradienten zu erhalten
	double norm = h.norm();
	if (norm != 0) { // unschön: Teilung durch 0 umgehen
		h /= norm;
	} else {
		h *= 1e100;
	}

	return h ^ (p2 - p1);
}

Vector Vertex::get_gradient () {
	Vector gradient(0, 0, 0);

	// Gradienten der umliegenden Dreiecksflächen aufsummieren
	for (list<Triangle*>::iterator t_it = triangles.begin(); t_it != triangles.end(); t_it++)
		gradient += this->get_gradient(*t_it);

	return gradient;
}

double Vertex::get_surrounding_surface (Vector delta) {
	Vector deltaVertex = *this + delta;
	double surface = 0;
	for (
		list<Triangle*>::iterator t_it = this->triangles.begin();
		t_it != this->triangles.end();
		t_it++
	){
		pair<Vertex*, Vertex*> p = (*t_it)->get_remote_points(this);
	
		Vector m = ( deltaVertex - *p.first ) ^ ( deltaVertex - *p.second );
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
