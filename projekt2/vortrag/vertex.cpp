struct Vertex : Vector {
	// Dirichletwert
	double dirichlet;
	// Angrenzende Kanten im Polynomzug
	Edge *previous, *next;

	Vertex (double x, double y, double dirichlet)
		: dirichlet(dirichlet), Vector(x, y) {}
};
