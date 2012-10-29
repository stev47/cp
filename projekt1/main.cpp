#define _USE_MATH_DEFINES	// Nötig für die Konstante M_PI
#include <iostream>
#include <cmath>
#include <list>
#include <set>


using namespace std;


struct Triangle;

/**
 * Knotenpunkt
 */
struct Vertex {
	unsigned int id;	//<! Index, nur für die Ausgabefunktion nötig
	double x, y, z;		//<! Koordinaten (public für die Ausgabe)
	double t;			//<! Stelle auf der parametrisierten Kurve
	std::list<Triangle*> triangles;	//<! Liste von zugehörigen Dreiecken

	Vertex (double x, double y, double z) : x(x), y(y), z(z), t(-1) {
	}
	Vertex (double x, double y, double z, double t) : x(x), y(y), z(z), t(t) {
	}
	bool is_margin () {
		return (this->t >= 0);
	}
	void add_triangle (Triangle* t) {
		this->triangles.push_back(t);		
	}
};

/**
 * Kante
 */
struct Edge {
	Vertex *v1, *v2;		//<! Eckpunkte
	bool margin;			//<! Randkante?

	// Für das Verfeinern nötig:
	Vertex* m;				//<! Neuer Mittelpunkt bei Halbierung
	Edge *s1, *s2;			//<! Neue Kanten bei Halbierung

	Edge (Vertex* v1, Vertex* v2) : v1(v1), v2(v2), margin(false), m(NULL) {
	}
	Edge (Vertex* v1, Vertex* v2, bool margin) : v1(v1), v2(v2), margin(margin), m(NULL) {
	}

	bool is_halved () {
		return (this->m != NULL);
	}
	bool is_margin () {
		return margin;
	}
	/**
	 * Gibt halbierte Kante an einem Punkt zurück
	 */
	Edge* subedge (Vertex* v) {
		if (v == this->v1) {
			return this->s1;
		} else {
			return this->s2;
		}		
	}
};

/**
 * Dreieck
 */
struct Triangle {
	Vertex *v1, *v2, *v3;		//<! Eckpunkte
	Edge *e1, *e2, *e3;			//<! Kanten
	Triangle *t1, *t2, *t3;		//<! Angrenzende Dreiecke

	Triangle (Vertex* v1, Vertex* v2, Vertex* v3, Edge* e1, Edge* e2, Edge* e3) 
		: v1(v1), v2(v2), v3(v3), e1(e1), e2(e2), e3(e3) {
	}
};


class Net {
	protected:
	std::list<Vertex*> vertices;		//!< Knotenliste
	std::list<Triangle*> triangles;	//!< Dreiecksliste
	std::list<Edge*> edges;			//!< Kantenliste
	
	public:
	/**
	 * Berechne einen Randpunkt auf der Kurve an der Stelle t.
	 * Es muss stets 0 <= t <= 1 gelten.
	 * Wird von einer anderen Klasse implementiert
	 * Mathematisch betrachtet, ist das hier unsere parametrisierte Kurvenfunktion
	 */
	virtual Vertex f (double t) = 0;

	Vertex* new_vertex (double x, double y, double z) {
		this->vertices.push_back(new Vertex(x,y,z));
		return this->vertices.back();
	}
	Vertex* new_vertex (double t) {
		this->vertices.push_back(new Vertex(this->f(t)));
		return this->vertices.back();
	}
	Edge* new_edge (Vertex* v1, Vertex* v2, bool margin = false) {
		this->edges.push_back(new Edge(v1, v2, margin));
		return this->edges.back();
	}
	Triangle* new_triangle (Vertex* v1, Vertex* v2, Vertex* v3, Edge* e1, Edge* e2, Edge* e3) {
		this->triangles.push_front(new Triangle(v1, v2, v3, e1, e2, e3));
		return this->triangles.front();
	}

	/**
	 * Beginne mit einem Dreieck
	 */
	virtual void init () {
		Vertex* v1 = this->new_vertex(0.0);
		Vertex* v2 = this->new_vertex(1.0/3);
		Vertex* v3 = this->new_vertex(2.0/3);

		Edge* e1 = this->new_edge(v2, v3, true);
		Edge* e2 = this->new_edge(v1, v3, true);
		Edge* e3 = this->new_edge(v1, v2, true);

		Triangle* t = this->new_triangle(v1, v2, v3, e1, e2, e3);
		
		v1->add_triangle(t);
		v2->add_triangle(t);
		v3->add_triangle(t);
	}

	void print () {
		unsigned int i = 1;
		std::cout.setf(std::ios::fixed, std::ios::floatfield);
		std::cout.precision(3);
		for (std::list<Vertex*>::iterator it = this->vertices.begin(); it != this->vertices.end(); it++) {
			std::cout << "v " << (*it)->x << " " << (*it)->y << " " << (*it)->z << std::endl;
			(*it)->id = i++;
		}
		int curve_begin = i;
		for (float t = 0; t < 1; t += 0.01) {
			Vertex v = this->f(t);
			std::cout << "v " << v.x << " " << v.y << " " << v.z << std::endl;
			i++;
		}
		int curve_end = i - 1;
		std::cout << "l";
		for (int i = curve_begin; i <= curve_end; i++) {
			std::cout << " " << i;
		}
		//std::cout << " " << curve_begin; // Zurück zum Anfangspunkt der Kurve verbinden
		std::cout << std::endl;

		
		for (std::list<Triangle*>::iterator it = this->triangles.begin(); it != this->triangles.end(); it++) {
			std::cout << "f " << (*it)->v1->id << " " << (*it)->v2->id << " " << (*it)->v3->id << std::endl;
		}
		for (std::list<Vertex*>::iterator it = this->vertices.begin(); it != this->vertices.end(); it++) {
			std::cout << "p " << (*it)->id << std::endl;
		}
	}

	void refine_mesh () {
		for (
			std::list<Triangle*>::iterator it = this->triangles.begin();
		   	it != this->triangles.end(); 
		)	{
			Triangle* t = (*it);	// Aktuelles Dreieck

			// Kanten halbieren (dabei werden die Teilkanten erstellt)
			bool e1_halved = this->halve_edge(t->e1);
			bool e2_halved = this->halve_edge(t->e2);
			bool e3_halved = this->halve_edge(t->e3);
			// Neue innere Kanten erzeugen
			Edge* ei1 = this->new_edge(t->e2->m, t->e3->m);
			Edge* ei2 = this->new_edge(t->e1->m, t->e3->m);
			Edge* ei3 = this->new_edge(t->e1->m, t->e2->m);
			// Neue Dreiecke erzeugen
			this->new_triangle(		// Linkes Dreieck
					t->v1, t->e3->m, t->e2->m,
					ei1, t->e2->subedge(t->v1), t->e3->subedge(t->v1)
				);
			this->new_triangle(		// Rechtes Dreieck
					t->v2, t->e1->m, t->e3->m,
					ei2, t->e3->subedge(t->v2), t->e1->subedge(t->v2)
				);
			this->new_triangle(		// Oberes Dreieck
					t->v3, t->e2->m, t->e1->m,
					ei3, t->e1->subedge(t->v3), t->e2->subedge(t->v3)
				);
			this->new_triangle(		// Inneres Dreieck
					t->e1->m, t->e2->m, t->e3->m,
					ei1, ei2, ei3
				);

			// Aufräumen
			this->triangles.erase(it++);
			delete t;
			
			if (!e1_halved) {
				this->edges.remove(t->e1);
				delete t->e1;
			}
			if (!e2_halved) {
				this->edges.remove(t->e2);
				delete t->e2;
			}
			if (!e3_halved) {
				this->edges.remove(t->e3);
				delete t->e3;
			}
		}
	}

	/**
	 * Halbiert eine Kante
	 *
	 * Erstellt Mittelpunkt und Teilkanten. Gibt true zurück, falls halbiert wurde
	 * und false, falls die Kante bereits halbiert war.
	 */
	bool halve_edge (Edge* e) {
		if (e->is_halved())
			return false;

		Vertex* m;

		if (e->is_margin()) {
			// Neuen Punkt auf der Kurve berechnen
			double t1 = e->v1->t;
			double t2 = e->v2->t;

			double t = (t1 + t2) / 2;
			if (fabs(t1 - t2) > 0.5) 
				t += 0.5;
			if (t > 1)
				t -= 1;

			m = this->new_vertex(t);
		} else {
			// Mittelpunkt
			m = this->new_vertex(
				(e->v1->x + e->v2->x) / 2,
				(e->v1->y + e->v2->y) / 2,
				(e->v1->z + e->v2->z) / 2
			);
		}
		// Der Kante den Mittelpunkt zuweisen
		e->m = m;

		// Neue Kanten erzeugen
		// Die Teilkanten sind genau dann Randkanten, wenn die
		// aktuelle Kante eine Randkante ist
		e->s1 = this->new_edge(e->v1, e->m, e->is_margin());
		e->s2 = this->new_edge(e->m, e->v2, e->is_margin());

		return true;
	}

	Vertex cross_product(Vertex v1, Vertex v2) {
	  //Kreuzprodukt
	    Vertex v((v1.y*v2.z)-(v1.z*v2.y),(v1.z*v2.x)-(v1.x*v2.z), (v1.x*v2.y)-(v1.y*v2.x)) ;
	  
	    return v;
	    
	}
  
};

/**
 * Kreiskurve mit Radius 1
 */
class CircleNet : public Net {
	public:
	virtual Vertex f (double t) {
		Vertex v(
			std::cos(2 * M_PI * t),		// x-Koordinate
			std::sin(2 * M_PI * t),		// y-Koordinate
			t,							// z-Koordinate
			t
		);
		return v;
	}
};

void m(const char* x) {
}

int main () {
	CircleNet my_circle;
	
	my_circle.init();

	my_circle.refine_mesh();
	my_circle.refine_mesh();
	my_circle.refine_mesh();
	my_circle.print();

	return 0;
}
