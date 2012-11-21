for ( list<Vertex*>::iterator v_it = this->vertices.begin(); v_it != this->vertices.end(); v_it++) { 
	Vertex& v = *(*v_it);

	if (!v.is_margin())
		continue;

	Vector gradient(0, 0, 0);
	// Gradienten der umliegenden Dreiecksflaechen aufsummieren
	for (list<Triangle*>::iterator t_it = v.triangles.begin(); t_it != v.triangles.end(); t_it++)
		gradient += v.get_gradient(*t_it);

	// Halbiere den Gradienten so lange, bis eine Verbesserung eintritt
	while (v.get_surrounding_surface(gradient) > v.get_surrounding_surface())
		gradient *= 0.5;

	v += gradient;
}
