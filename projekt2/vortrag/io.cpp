void Domain::import (string file) {

	ifs >> x >> y >> dirichlet;
	if (ifs.fail()) {
		dirichlet = numeric_limits<double>::quiet_NaN();
	}
	ifs >> neumann;
	if (ifs.fail()) {
		neumann = numeric_limits<double>::quiet_NaN();
	}
	ifs >> unterteilung;

	while (true) {
		ifs >> x >> y >> dirichlet;
		if (ifs.fail() && !ifs.eof()) {
			dirichlet = numeric_limits<double>::quiet_NaN();
		}
		...


}