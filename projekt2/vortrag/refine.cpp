void Domain::refine() {
	for (
		list<Vertex*>::iterator v_it = vertices.begin();
		v_it != vertices.end();
	){
		Vertex* vbegin = *v_it;
		Vertex* vend = vbegin->next->v2;

		int num_edges = vbegin->next->unterteilung;


		Vector richtung = (*vend - *vbegin) / num_edges;
		bool got_neumann = true;
		double neumann = vbegin->next->neumann;
		if (isnan(neumann)){
			got_neumann = false;
		}


		// v_it zeigt jetzt auf vend
		v_it++;

		Vertex* v1 = vbegin;
		for (int i = 1; i < num_edges; i++) {

			Vertex* v2 = new Vertex(*v1 + richtung);
			//Wenn Neumann Wert existiert Dirichlet nicht Interpolieren/mit Funktion errechnen
			if (got_neumann == false) {

				if(dirichletf == true){
					v2->dirichlet = get_dirichlet(v2->x, v2->y);
				} else {
					v2->dirichlet = vbegin->dirichlet + ((double(i)/(num_edges)) * (vend->dirichlet - vbegin->dirichlet)); //Interpolation
				}
			}
			else v2->dirichlet = numeric_limits<double>::quiet_NaN();

			vertices.insert(v_it, v2);

			// Hier keien Abfrage, denn: wenn Neuman nicht existent wird NAN übernommen
			Edge* edge = new Edge(v1, v2, neumann, 1);

			if(neumannf == true){
				edge->neumann = get_neumann(v1->x, v2->x, v1->y, v2->y);
			}

			v1->next = edge;
			v2->previous = edge;

			v1 = v2;
		}

		Edge* edge = new Edge(v1, vend, neumann, 1);
		if(neumannf == true){
			edge->neumann = get_neumann(v1->x, vend->x, v1->y, vend->y);
		}
		v1->next = edge;
		vend->previous = edge;

	}

}
