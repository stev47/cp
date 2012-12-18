#include <iostream>
#include <vector>
#include "../datastructures.h"

using namespace std;

int main (int argc, char* argv[]) {

	// Gebiet erstellen aus einer Polygonbeschreibung
	Domain mydomain("../data/beispielpolygon.txt");
	
	/*
	 * Flächenüberprüfung
	 */
	double area = mydomain.calculate_area();
	cout << "Die Fläche des eingelesenen Polygons beträgt: " << area << endl;

	if (area < 0)
		cout << "Warnung: Negative Fläche! "
			<< "Die Knoten des Polygonzugs wurden vermutlich fälschlicherweise"
			<< " im Uhrzeigersinn spezifiziert." << endl;

}
