class Edge {
	Vertex *v1, *v2;		// Eckpunkte

	bool margin;			// Randkante oder nicht?
	Vertex* m;				// Neuer Mittelpunkt bei Halbierung
	Edge *s1, *s2;			// Neue Kanten bei Halbierung
};
