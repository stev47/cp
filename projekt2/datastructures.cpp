#include <iostream>
#include "datastructures.h"

using namespace std;

/*
 * Kante
 */

Edge::Edge (Vertex* v1, Vertex* v2, double neumann, int unterteilung)
		: v1(v1), v2(v2), neumann(neumann), unterteilung(unterteilung) {
	// Sich bei den Knoten bekannt machen
	v1->next = this;
	v2->previous = this;
}

Vector Edge::get_normal () {
	return ~(*v1 - *v2);
}

Vector Edge::get_center () {
	return Vector( 0.5 * (v1->x + v2->x), 0.5 * (v1->y + v2->y) );
}

/*
 * Gebiet
 */

Domain::Domain (string file) {
	import(file);
}

double Domain::calculate_area () {

	double area = 0;
	for (
		list<Vertex*>::iterator v_it = vertices.begin();
		v_it != vertices.end()--;
	) {
		Vertex* current = *v_it;
		Vertex* next = *(++v_it);

		// Kreuzprodukt
		area += (current->x * next->y) - (next->x * current->y);
	}
	area += (vertices.back()->x * vertices.front()->y) - (vertices.front()->x * vertices.back()->y);
	area *= 0.5;
	
	return area;
}

