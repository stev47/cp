#include <iostream>
#include "net.h"
#include "curves.h"

using namespace std;

int main (int argc, char* argv[]) {

	int j, k;
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
	cout << "Wie oft soll verfeinert werden? " << endl;
	cin >> k;
	if(j == 1){
		Curves::Test my_curve;
		Net my_net( my_curve );
		my_net.init();
		my_net.refine_mesh();
		double area_before, area_new, improvement;
		cout.setf(ios::fixed, ios::floatfield);
		cout.precision(6);
		cout << my_net.Surface() <<endl;
		for (int i = 1; i <= k; i++) {
				cout << "Verfeinere ... ";
				my_net.refine_mesh();
				cout << "fertig" << endl;
				do {
				area_before = my_net.Surface();
				cout << "Minimiere ... ";
				my_net.minimize_mesh();
				cout << (area_new = my_net.Surface());
				improvement = (1 - (area_new / area_before));
				cout << " (" << improvement << "%)" << endl;
				} while (improvement > 1e-3);
		}
		my_net.print();
	}
	if(j == 2){
		Curves::Schnitt my_curve;
		Net my_net( my_curve );
		my_net.init();
		my_net.refine_mesh();
		double area_before, area_new, improvement;
		cout.setf(ios::fixed, ios::floatfield);
		cout.precision(6);

		cout << my_net.Surface() <<endl;
		for (int i = 1; i <= k; i++) {
				cout << "Verfeinere ... ";
				my_net.refine_mesh();
				cout << "fertig" << endl;
				do {
				area_before = my_net.Surface();
				cout << "Minimiere ... ";
				my_net.minimize_mesh();
				cout << (area_new = my_net.Surface());
				improvement = (1 - (area_new / area_before));
				cout << " (" << improvement << "%)" << endl;
				} while (improvement > 1e-3);
		}
		my_net.print();
	}
	if(j == 3){
		Curves::Circle my_curve;
		Net my_net( my_curve );
		my_net.init();
		my_net.refine_mesh();
		double area_before, area_new, improvement;
		cout.setf(ios::fixed, ios::floatfield);
		cout.precision(6);

		cout << my_net.Surface() <<endl;
		for (int i = 1; i <= k; i++) {
				cout << "Verfeinere ... ";
				my_net.refine_mesh();
				cout << "fertig" << endl;
				do {
				area_before = my_net.Surface();
				cout << "Minimiere ... ";
				my_net.minimize_mesh();
				cout << (area_new = my_net.Surface());
				improvement = (1 - (area_new / area_before));
				cout << " (" << improvement << "%)" << endl;
				} while (improvement > 1e-3);
		}
		my_net.print();
	}
	if(j == 4){
		Curves::Viviani my_curve;
		Net my_net( my_curve );
		my_net.init();
		my_net.refine_mesh();
		double area_before, area_new, improvement;
		cout.setf(ios::fixed, ios::floatfield);
		cout.precision(6);

		cout << my_net.Surface() <<endl;
		for (int i = 1; i <= k; i++) {
				cout << "Verfeinere ... ";
				my_net.refine_mesh();
				cout << "fertig" << endl;
				do {
				area_before = my_net.Surface();
				cout << "Minimiere ... ";
				my_net.minimize_mesh();
				cout << (area_new = my_net.Surface());
				improvement = (1 - (area_new / area_before));
				cout << " (" << improvement << "%)" << endl;
				} while (improvement > 1e-3);
		}
		my_net.print();
	}
	if(j == 5){
		Curves::TennisBall my_curve;
		Net my_net( my_curve );
		my_net.init();
		my_net.refine_mesh();
		double area_before, area_new, improvement;
		cout.setf(ios::fixed, ios::floatfield);
		cout.precision(6);

		cout << my_net.Surface() <<endl;
		for (int i = 1; i <= k; i++) {
				cout << "Verfeinere ... ";
				my_net.refine_mesh();
				cout << "fertig" << endl;
				do {
				area_before = my_net.Surface();
				cout << "Minimiere ... ";
				my_net.minimize_mesh();
				cout << (area_new = my_net.Surface());
				improvement = (1 - (area_new / area_before));
				cout << " (" << improvement << "%)" << endl;
				} while (improvement > 1e-3);
		}
		my_net.print();
	}
	if(j == 6){
		Curves::TennisBallB my_curve;
		Net my_net( my_curve );
		my_net.init();
		my_net.refine_mesh();
		double area_before, area_new, improvement;
		cout.setf(ios::fixed, ios::floatfield);
		cout.precision(6);

		cout << my_net.Surface() <<endl;
		for (int i = 1; i <= k; i++) {
				cout << "Verfeinere ... ";
				my_net.refine_mesh();
				cout << "fertig" << endl;
				do {
				area_before = my_net.Surface();
				cout << "Minimiere ... ";
				my_net.minimize_mesh();
				cout << (area_new = my_net.Surface());
				improvement = (1 - (area_new / area_before));
				cout << " (" << improvement << "%)" << endl;
				} while (improvement > 1e-3);
		}
		my_net.print();
	}

	return 0;
}
