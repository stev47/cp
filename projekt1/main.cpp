#include <iostream>
#include "net.h"
#include "curves.h"

using namespace std;

int main (int argc, char* argv[]) {

	Curves::Circle my_curve;
	Net my_net( my_curve );

	my_net.init();

	my_net.refine_mesh();
	
	double area_before;
	cout << my_net.Surface() <<endl;
	for (int i = 1; i <= 4; i++) {
		my_net.refine_mesh();
		cout << "Verfeinere" <<endl;
		do {
				area_before = my_net.Surface();
				my_net.minimize_mesh();
				cout << my_net.Surface() <<endl;
		} while (my_net.Surface() / area_before <  1 - 1e-3);
	}


	my_net.print();


	return 0;
}
