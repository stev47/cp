#include <iostream>
#include <vector>
#include "datastructures.h"

using namespace std;

int main (int argc, char* argv[]) {

	Domain mydomain("beispielpolygon.txt");

	/*
	 * Für die Gruppe, die die Koordinaten als Vector braucht:
	 */
	vector<double> x_coords = mydomain.get_x_coordinates();
	vector<double> y_coords = mydomain.get_y_coordinates();

	for (int i = 0; i < x_coords.size(); i++) {
		cout << x_coords[i] << " " << y_coords[i] << endl;
	}

	mydomain.write_to_obj("test.obj");

	/*
	 * Flächenüberprüfung
	 */
	/*
	double area = mydomain.calculate_area();
	cout << "Die Fläche des Polygons beträgt: " << area << endl;

	if (area < 0)
		cout << "Warnung: Negative Fläche! "
			<< "Die Knoten des Polygonzugs wurden vermutlich fälschlicherweise"
			<< " im Uhrzeigersinn spezifiziert." << endl;
	*/
	
	return 0;
}
