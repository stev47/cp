#include <iostream>
#include <vector>
#include "../datastructures.h"

using namespace std;

class Funktionen_Domain : public Domain {
	public:

	Funktionen_Domain(string file) {
		import(file);
	}

	double get_dirichlet(double x, double y) {
		//Funktion die Dirichlet Werte errechnet
		double erg= x+3*y;
		return(erg);
	}
		// Funktion für die Nemanndaten
	double get_neumann(double x1, double x2, double y1, double y2) {
		//Funktion die Neumann Werte errechnet
		double erg= 65*x1+3*y1*x2*x2;
		return(erg);
	}


};
int main (int argc, char* argv[]) {

	
	// Gebiet erstellen aus einer Polygonbeschreibung
	Funktionen_Domain mydomain("../data/beispielpolygon.txt");


}
