#include <iostream>
#include "net.h"
#include "curves.h"

using namespace std;

int main (int argc, char* argv[]) {

	int j, k;
	bool min;
	string file("out.obj");

	if (argc > 1)
		file = argv[1];
	
	cout << "Waehlen Sie eine Kurve aus: " << endl;
	cout << "(1) Test " << endl;
	cout << "(2) Schnitt " << endl;
	cout << "(3) Circle " << endl;
	cout << "(4) Viviani " << endl;
	cout << "(5) TennisBall " << endl;
	cout << "(6) TennisBallB " << endl;
	cin >> j;
	if(j != 1 && j != 2 && j != 3 && j != 4 && j != 5 && j != 6){
		cout << "Fehler Kurvenauswahl " << endl;
		return 0;
	}
	cout << "Wie oft soll verfeinert werden? [0-10] " << endl;
	cin >> k;
	cout << "Soll minimiert werden? [0,1]" << endl;
	cin >> min;
	
	Curves::Curve *my_curve;
	if(j == 1){
		my_curve = new Curves::Test();
	}
	if(j == 2){
		my_curve = new Curves::Schnitt();
	}
	if(j == 3){
		my_curve = new Curves::Circle();
	}
	if(j == 4){
		my_curve = new Curves::Viviani();
	}
	if(j == 5){
		my_curve = new Curves::TennisBall();
	}
	if(j == 6){
		my_curve = new Curves::TennisBallB();
	}
	Net my_net( *my_curve );
	my_net.init();
	double area_before, area_new, improvement;
	cout.setf(ios::fixed, ios::floatfield);
	cout.precision(8);

	cout << (area_new = my_net.Surface()) << endl;
	for (int i = 1; i <= k; i++) {
		cout << "Verfeinere ... ";
		my_net.refine_mesh();
		area_before = my_net.Surface();
		cout << "fertig" << endl;
		do {
			cout << "Minimiere ... ";
			if (min)
				my_net.minimize_mesh();
			cout << (area_new = my_net.Surface());
			improvement = (1 - (area_new / area_before));
			area_before = area_new;
			cout << " (" << improvement * 100 << "%)" << endl;
		} while (improvement > 1e-7);
	}
	my_net.print(file);
	

	return 0;
}
