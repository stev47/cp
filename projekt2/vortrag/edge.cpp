struct Edge {
	// Eckpunkte
	Vertex *v1, *v2;
	// Neumannwert
	double neumann;
	int unterteilung;

	// Ermittle den Mittelpunkt
	Vector get_center();
	// Ermittle den Normalenvektor zu dieser Kante
	Vector get_normal();

	Vector get_interpoint(double t);

	Edge (Vertex *v1, Vertex *v2, double neumann, int unterteilung);
};