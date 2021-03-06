#include <iostream>
#include <cmath>
#include <limits>

#include "datastructures.h"

using namespace std;



Vertex Vertex::operator+ (const Vector &v) {
	Vertex out(*this);

	out.x += v.x;
	out.y += v.y;
	
	return out;
}
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
	Vector temp = (~(*v1 - *v2));
	return temp * (-1.0 /sqrt(temp * temp));
}

Vector Edge::get_center () {
	return Vector( 0.5 * (v1->x + v2->x), 0.5 * (v1->y + v2->y) );
}

Vector Edge::get_interpoint (double t) {
	return ((*v2 - *v1) * t) + *v1;
}
/*
 * Gebiet
 */

Domain::Domain (string file) {
	import(file);
}

double Domain::get_dirichlet(double x, double y) {
	cout << "virtual old" << endl;
	return 0.0;
}

double Domain::get_neumann(double x1, double x2, double y1, double y2) {
	return 0.0;
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


void Domain::refine() {
	for (
		list<Vertex*>::iterator v_it = vertices.begin();
		v_it != vertices.end();
	){
		Vertex* vbegin = *v_it;
		Vertex* vend = vbegin->next->v2;

		int num_edges = vbegin->next->unterteilung;

		
		Vector richtung = (*vend - *vbegin) / num_edges;
		bool got_neumann = true;
		double neumann = vbegin->next->neumann;
		if (isnan(neumann)){
			got_neumann = false;
		}

		
		// v_it zeigt jetzt auf vend
		v_it++;
		
		Vertex* v1 = vbegin;
		for (int i = 1; i < num_edges; i++) {
			
			Vertex* v2 = new Vertex(*v1 + richtung);
			//Wenn Neumann Wert existiert Dirichlet nicht Interpolieren/mit Funktion errechnen
			if (got_neumann == false) {
				
				if(dirichletf == true){
					v2->dirichlet = get_dirichlet(v2->x, v2->y);
				} else {
					v2->dirichlet = vbegin->dirichlet + ((double(i)/(num_edges)) * (vend->dirichlet - vbegin->dirichlet)); //Interpolation
				}
			}
			else v2->dirichlet = numeric_limits<double>::quiet_NaN();
			
			vertices.insert(v_it, v2);
			
			// Hier keien Abfrage, denn: wenn Neuman nicht existent wird NAN übernommen
			Edge* edge = new Edge(v1, v2, neumann, 1);
			
			if(neumannf == true){
				edge->neumann = get_neumann(v1->x, v2->x, v1->y, v2->y);
			}
			
			v1->next = edge;
			v2->previous = edge;

			v1 = v2;
		}
		
		Edge* edge = new Edge(v1, vend, neumann, 1);
		if(neumannf == true){
			edge->neumann = get_neumann(v1->x, vend->x, v1->y, vend->y);
		}
		v1->next = edge;
		vend->previous = edge;

	}
	
}


