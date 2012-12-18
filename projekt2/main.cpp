#include <iostream>
#include <vector>
#include "datastructures.h"

using namespace std;

int main (int argc, char* argv[]) {

	Domain mydomain("data/beispielpolygon.txt");
	
	mydomain.refine();

	mydomain.write_to_obj("test.obj");
	
	return 0;
}
