class Domain {
	protected:
		void import(string file);

	public:
		list<Vertex*> vertices;
		bool dirichletf, neumannf;
		virtual double get_dirichlet(double x, double y);
		virtual double get_neumann(double x1, double x2, double y1, double y2);

		void write_to_obj(string file);

		void refine();

		vector<double> get_x_coordinates();

		vector<double> get_y_coordinates();

		// Kontruktor, der aus einer Datei den Polygonzug einliest
		Domain(string file);

		Domain() {};
};