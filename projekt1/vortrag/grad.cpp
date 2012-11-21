Vector Vertex::get_gradient (Triangle* t) {
	pair<Vertex*, Vertex*> p = t->get_remote_points(this);
	Vertex p1 = *p.first;
	Vertex p2 = *p.second;
	
	return ((*this - p1) ^ (*this - p2)) ^ (p1 - p2);
}
