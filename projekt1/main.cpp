#include <iostream>
#include "net.h"
#include "curves.h"

using namespace std;

int main (int argc, char* argv[]) {

	Curves::Test my_curve;
	Net my_net( my_curve );

	my_net.init();

	my_net.refine_mesh();
	
	double area_before, area_new, improvement;
	cout.setf(ios::fixed, ios::floatfield);
	cout.precision(6);

	cout << my_net.Surface() <<endl;
	for (int i = 1; i <= 5; i++) {
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


	return 0;
}
