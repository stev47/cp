#include <iostream>
#include "curves.h"

using namespace std;



int main () {
	TennisBallCurveNet my_curve;

	my_curve.init();

	my_curve.refine_mesh();
	my_curve.refine_mesh();
	cout << my_curve.Surface() <<endl;
	my_curve.minimize_mesh();
	my_curve.minimize_mesh();
	my_curve.minimize_mesh();

	my_curve.refine_mesh();
	cout << my_curve.Surface() <<endl;
	my_curve.minimize_mesh();
	my_curve.minimize_mesh();
	my_curve.minimize_mesh();
	
	my_curve.refine_mesh();
	cout << my_curve.Surface() <<endl;
	my_curve.minimize_mesh();
	my_curve.minimize_mesh();
	my_curve.minimize_mesh();
	cout << my_curve.Surface() <<endl;

	my_curve.refine_mesh();
	cout << my_curve.Surface() <<endl;
	my_curve.minimize_mesh();
	my_curve.minimize_mesh();
	my_curve.minimize_mesh();



	my_curve.print();

	return 0;
}
