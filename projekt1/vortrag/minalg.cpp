do {
	// Minimize mesh
	for ( list<Vertex*>::iterator v_it = this->vertices.begin(); v_it != this->vertices.end(); v_it++) { 
		// For each Vertex
		move_to_optimum(*v_it);
	}
	// Calculate improvement
	improvement = 1 - (area_new / area_before);

} while (improvement > IMPROVEMENT_THRESHOLD);


