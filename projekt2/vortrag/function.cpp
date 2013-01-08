	while (true) {
		
		...

		if(dirichletf == true){
			dirichlet = get_dirichlet(x, y);
		}
		current_vertex = new Vertex(x, y, dirichlet);
		vertices.push_back(current_vertex);

		if(neumannf == true){
			previous_neumann = get_neumann(previous_vertex->x, current_vertex->x, previous_vertex->y, current_vertex->y);
		}
		Edge* last_edge = new Edge(previous_vertex, current_vertex, previous_neumann, prev_unterteilung);
		previous_vertex = current_vertex;
	}
	...

}