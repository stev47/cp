#include <iostream>
#include <vector>
#include "../datastructures.h"

using namespace std;

int main (int argc, char* argv[]) {

	// Gebiet erstellen aus einer Polygonbeschreibung
	Domain mydomain("../data/beispielpolygon.txt");
	
	/*
	 * Die Koordinaten der Punkte als C++-Vector abspeichern
	 */
	vector<double> x_coords = mydomain.get_x_coordinates();
	vector<double> y_coords = mydomain.get_y_coordinates();

	/*
	 * Irgendetwas mit diesen Daten anstellen, z.B. ausgeben:
	 */
	for (int i = 0; i < x_coords.size(); i++) {
		cout << "Punkt " << i << " : ( " 
			 << x_coords[i] << " | " << y_coords[i] << " )" << endl;
	}

}
