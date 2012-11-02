#include <list>
#include <cstddef>
#include "datastructures.h"

using namespace std;

bool Vertex::is_margin () {
	return (this->t >= 0);
}
void Vertex::add_triangle (Triangle* t) {
	this->triangles.push_back(t);		
}
void Vertex::remove_triangle (Triangle* t) {
	this->triangles.remove(t);		
}

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

/**
 * Dreieck
 */
pair<Vertex*, Vertex*> Triangle::rem_points(Vertex* v) {
	if (v == this->v1) 
		return pair<Vertex*, Vertex*>(this->v2, this->v3);
	if (v == this->v2)
		return pair<Vertex*, Vertex*>(this->v1, this->v3);
	else
		return pair<Vertex*, Vertex*>(this->v2, this->v1);
}
