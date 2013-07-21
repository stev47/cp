#include <iostream>
#include <sstream>
#include <cmath>
#include "net.h"
#include "curves.h"

// Schwellwert für die relative Verbesserung
// unter der die Minimierung abgebrochen wird.
#define IMPROVEMENT_THRESHOLD 1e-7 


using namespace std;

int main (int argc, char* argv[]) {

	int j, k;
	double a;
	bool min;
	string file("out.obj");

	if (argc > 1)
		file = argv[1];
	
	cout << "Wählen Sie eine Kurve aus: " << endl;
	cout << "(1) Test " << endl;
	cout << "(2) Schnitt " << endl;
	cout << "(3) Circle " << endl;
	cout << "(4) Welle " << endl;
	cout << "(5) Viviani " << endl;
	cout << "(6) TennisBall " << endl;
	cout << "(7) TennisBallB " << endl;
	cout << "(8) Spirale " << endl;
	cout << "(9) Doppelhelix " << endl;
	cin >> j;
	if(j == 4){
		cout << "Geben Sie bitte den gewünschten Abstand ein " << endl;
		cin >> a;
	}
	cout << "Wie oft soll verfeinert werden? [0-10] " << endl;
	cin >> k;
	cout << "Soll minimiert werden? [0,1]" << endl;
	cin >> min;
	
	Curves::Curve *my_curve;
	switch (j) {
		case 1: my_curve = new Curves::Test(); break;
		case 2: my_curve = new Curves::Schnitt(); break;
		case 3: my_curve = new Curves::Circle(); break;
		case 4: my_curve = new Curves::Welle(a); break;
		case 5: my_curve = new Curves::Viviani(); break;
		case 6: my_curve = new Curves::TennisBall(); break;
		case 7: my_curve = new Curves::TennisBallB(); break;
		case 8: my_curve = new Curves::Spirale(); break;
		case 9: my_curve = new Curves::Helix(); break;
		default: my_curve = new Curves::Test();
	}
	Net my_net( *my_curve );

	cout << "=========================================" << endl;


	/*
	 * Ausgabeformat für floating point Zahlen
	 */
	cout.setf(ios::fixed, ios::floatfield);
	cout.precision(8);

	/*
	 * Initialisiere mit Anfangsdreieck
	 */
	my_net.init();

	double area_before, area, improvement;
	cout << "Anfang ...\t" << (area = my_net.surface()) << endl;
	for (int i = 1; i <= k; i++) {
		/*
		 * Verfeinerung und Flächen(änderungs)berechnung
		 */
		cout << "Verfeinern ...\t";
		cout.flush();	// Damit obige Ausgabe sofort erscheint
		area_before = my_net.surface();
		my_net.refine_mesh();
		cout << (area = my_net.surface());
		improvement = (1 - (area / area_before));
		area_before = area;
		cout << " (" << improvement * 100 << "%)" << endl;

		if (!min)
			continue;

		/*
		 * Test zum zusätzlichen Optimieren der Dreiecksnetzstruktur
		 *
		double area_new;
		cout << "\rOptimieren ...\t" << endl;
		cout.flush();	// Damit obige Ausgabe sofort erscheint
		area_before = my_net.surface();
		//for (int j = 0; j < 50; j++)
		cout << "fertig ... " << (area_new = my_net.surface());
		improvement = (1 - (area_new / area_before));
		area_before = area_new;
		cout << " (" << improvement * 100 << "%)";

		*/

		/*
		 * Minimierung und Flächen(änderungs)berechnung
		 */
		do {
			cout << "\rMinimieren ...\t";
			cout.flush();	// Damit obige Ausgabe sofort erscheint

			double delta = my_net.minimize_mesh();

			cout << (area + delta); // Neue Fläche
			improvement = 1 - ((area + delta) / area); // Relative Verbesserung
			cout << " (" 
				<< improvement * 100
				<< "%)";//	<< endl; 

			area += delta;
		} while (improvement > IMPROVEMENT_THRESHOLD);
		cout << endl;

	}
	my_net.print(file);
	

	return 0;
}
