#include <iostream>
#include "datastructures.h"

using namespace std;

int main (int argc, char* argv[]) {

	Domain mydomain("beispielpolygon.txt");

	mydomain.write_to_obj("test.obj");
	
	double area = mydomain.calculate_area();
	cout << "Die Fläche des Polygons beträgt: " << area << endl;

	if (area < 0)
		cout << "Warnung: Negative Fläche! "
			<< "Die Knoten des Polygonzugs wurden vermutlich fälschlicherweise"
			<< " im Uhrzeigersinn spezifiziert." << endl;
	
	return 0;
}
