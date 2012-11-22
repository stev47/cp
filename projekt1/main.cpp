#include <iostream>
#include <sstream>
#include "net.h"
#include "curves.h"


#define IMPROVEMENT_THRESHOLD 1e-6 


using namespace std;

int main (int argc, char* argv[]) {

	int j, k;
	double a;
	bool min;
	string file("out");

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

	/*
	 * Ausgabeformat für floating point Zahlen
	 */
	cout.setf(ios::fixed, ios::floatfield);
	cout.precision(8);

	// Initialisiere mit Anfangsdreieck
	my_net.init();

	double area_before, area_new, improvement;
	cout << (area_new = my_net.Surface()) << endl;
	for (int i = 1; i <= k; i++) {
		// Ausgabe von Zwischenstadien
		std::stringstream tmp;
		tmp << file << i - 1 << ".obj";
		my_net.print(tmp.str());

		cout << i << ". Verfeinern ... ";
		cout.flush();	// Damit obige Ausgabe sofort erscheint
		area_before = my_net.Surface();
		my_net.refine_mesh();
		cout << "fertig ... " << (area_new = my_net.Surface());
		improvement = (1 - (area_new / area_before));
		area_before = area_new;
		cout << " (" << improvement * 100 << "%)" << endl;
		if (!min)
			continue;

		do {
			cout << "Minimiere ... ";
			my_net.minimize_mesh();
			cout << (area_new = my_net.Surface());
			improvement = (1 - (area_new / area_before));
			area_before = area_new;
			cout << " (" << improvement * 100 << "%)" << endl;
		} while (improvement > IMPROVEMENT_THRESHOLD);
	}
	std::stringstream tmp;
	tmp << file << k << ".obj";
	my_net.print(tmp.str());
	

	return 0;
}
