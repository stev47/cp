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

	double area = 0.0;
	for (
		list<Vertex*>::iterator v_it = vertices.begin();
		v_it != --vertices.end();
	) {
		Vertex* current = *v_it;
		Vertex* next = *(++v_it);

		// Kreuzprodukt
		area += (current->x * next->y) - (next->x * current->y);
		cout << current->x << next->x << current->y << next->y << endl;
		cout << area << endl;
	}
	area += (vertices.back()->x * vertices.front()->y) - (vertices.front()->x * vertices.back()->y);
	area *= 0.5;
	
	return area;
}

vector<double> Domain::get_x_coordinates () {

	vector<double> x_coords;
	for (
		list<Vertex*>::iterator v_it = vertices.begin();
		v_it != vertices.end();
		v_it++
	) {
		x_coords.push_back((*v_it)->x);
	}

	return x_coords;
}

vector<double> Domain::get_y_coordinates () {

	vector<double> x_coords;
	for (
		list<Vertex*>::iterator v_it = vertices.begin();
		v_it != vertices.end();
		v_it++
	) {
		x_coords.push_back((*v_it)->y);
	}

	return x_coords;
}

/*
void Domain::refine() {
	for (
		list<Vertex*>::iterator v_it = vertices.begin();
		v_it != vertices.end();
		v_it++;
	){
		Vertex* v = *v_it;
		
		cout << v->x << endl;
		
		Vertex vend=v1.next.v2;
		int u=v1.next.unterteilung;
		Vektor richtung=(v2-v1)/u;
		int neumann=u1.v1.next.neumann;
		//hier eventuell alte kanten löschen
		for (int i =1; i<=u; i++){
			v2=v1+richtung;
			next=new edge(v1,v2, neumann, 1);
			v1.next=*next
			
		}

	}
	
}

*/
