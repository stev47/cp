class Domain {
	protected:
		// Eine Zeile einlesen (Knoten und Neumanndaten der nächsten Kante)
		pair<Vertex, double> parse_line(string line);
		// Importiert einen Polygonzug
		void import(string file);

	public:
		// Knotenliste
		list<Vertex*> vertices;
		// Boolean Abfrage ob eine Dirichlet- bzw Neumannfunktion vorhanden ist
		bool dirichletf, neumannf;
		// Funktion für die Dirichletdaten
		virtual double get_dirichlet(double x, double y);
		// Funktion für die Nemanndaten
		virtual double get_neumann(double x1, double x2, double y1, double y2);

		// Exportiert einen Polygonzug in eine Datei
		void write_to_obj(string file);
		// Berechnet die Fläche
		double calculate_area();

		void refine();

		vector<double> get_x_coordinates();
		vector<double> get_y_coordinates();

		// Kontruktor, der aus einer Datei den Polygonzug einliest
		Domain(string file);

		Domain() {};
};