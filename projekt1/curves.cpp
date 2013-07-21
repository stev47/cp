#define _USE_MATH_DEFINES	// Nötig für die Konstante M_PI
#include <iostream>
#include <cmath>
#include "datastructures.h"
#include "curves.h"

namespace Curves {

	Vertex Curve::f (double t) {
		return Vertex(0,0,0);
	}

	/**
	 * Kurve zum Testen
	 */
	Vertex Test::f (double t) {
		/*double u = 4*cos(M_PI * 2 * t);
		double v = 4*sin(M_PI * 2 * t);

		return Vertex(
			u * cos(v),
			u * sin(v),
			3 * v,
			t
		);*/

		double r = 3;
		double R = 15;
		double n = 12;

		return Vertex(
			cos(2*M_PI*t) * (R + r * cos(n * 2*M_PI*t)),
			sin(2*M_PI*t) * (R + r * cos(n * 2*M_PI*t)),
			r * sin(n * 2*M_PI*t),
			t
		);
	}


	/**
	 * Kreisspirale
	 */
	Vertex Kreisspirale::f (double t) {
		double r = 3; 	//<! Radius der Spiralkreise
		double n = 12;	//<! Anzahl der Spiralkreise
		double R = 15;	//<! Radius des Gesamtkreises

		return Vertex(
			cos(2*M_PI*t) * (R + r * cos(n * 2*M_PI*t)),
			sin(2*M_PI*t) * (R + r * cos(n * 2*M_PI*t)),
			r * sin(n * 2*M_PI*t),
			t
		);
	}
	/**
	 * Kurve zum Testen
	 */
	Vertex Helix::f (double t) {
		double s;
		if (t < 0.5) {
			s = t * 2;
			if (s < 0.9) {
				s *= 10.0 / 9;
				return Vertex(
					cos(M_PI * 2 * s),
					sin(M_PI * 2 * s),
					6 * s,
					t
				);
			} else {
				s = (s - 0.9) * 10;
				return Vertex( 1 - (2*s), 0, 6, t);
			}
		} else {
			s = (t - 0.5) * 2;
			if (s < 0.9) {
				s *= 10.0 / 9;
				return Vertex(
					-cos(M_PI * 2 * -s),
					-sin(M_PI * 2 * -s),
					6 - (6 * s),
					t
				);
			} else {
				s = (s - 0.9) * 10;
				return Vertex( -1 + (2*s), 0, 0, t);
			}
		}
	}

	/**
	 * Eine sich selbst schneidende Kreiskurve, die mit unsrem Algorithmus funktioniert
	 */
	Vertex Schnitt::f (double t) {
		return Vertex (cos(M_PI * 4 * t), sin(M_PI * 4 * t), sin(M_PI * 6 * t) * 0.5, t);
	}

	/**
	 * Kreiskurve mit Radius 1
	 */
	Vertex Circle::f (double t) {
		Vertex v (cos(2 * M_PI * t), sin(2 * M_PI * t), 0, t);
		return v;
	}

	/**
	 * Welle mit variablem Abstand der Ränder
	 */
	Vertex Welle::f (double t) {
		double s;
		double l = 5;
		if (t < 0.5) {
			s = t * 2;
			if (s < 0.8) {
				s *= 10.0 / 8;
				return Vertex(
					l*s,
					0,
					sin(M_PI * 2 * s),
					t
				);
			} else {
				s = (s - 0.8) * 5;
				return Vertex(l, s * a, 0, t);
			}
		} else {
			s = (t - 0.5) * 2;
			if (s < 0.8) {
				s *= 10.0 / 8;
				return Vertex(
					l * (1 - s),
					a,
					-sin(M_PI * 2 * s),
					t
				);
			} else {
				s = (s - 0.8) * 5;
				return Vertex(0, a - (s * a), 0, t);
			}
		}
	}

	/**
	 * Viviani's Curve
	 * http://en.wikipedia.org/wiki/Viviani%27s_curve
	 */
	Vertex Viviani::f (double t) {
		Vertex v(
				a * (1 + cos(4 * M_PI * t)),	// x-Koordinate
				a * sin(4 * M_PI * t),			// y-Koordinate
				2 * a * sin(2 * M_PI * t),		// z-Koordinate
				t
				);
		return v;
	}

	/**
	 * Annähernd eine Tennisballkurve, zusammengesetzt aus vier
	 * Halbkreisen mit Radius 1.
	 */
	Vertex TennisBall::f (double t) {
		if(t>=0.0 && t<=1.0/4) {
			Vertex v(
					cos(M_PI * 4 * t),		// x-Koordinate
					sin(M_PI * 4 * t),		// y-Koordinate
					0,						// z-Koordinate
					t
					);
			return v;
		}
		if(t>=1.0/4 && t<=1.0/2){
			t -= 1.0/4;
			Vertex v(
					-1,						// x-Koordinate
					-sin(M_PI * 4 * t),		// y-Koordinate
					-cos(M_PI * 4 * t)+1,	// z-Koordinate
					t + 1.0/4
					);
			return v;
		}
		if(t>=1.0/2 && t<=3.0/4) {
			t -= 1.0/2;
			Vertex v(
					-cos(M_PI * 4 * t),			// x-Koordinate
					sin(M_PI * 4 * t),			// y-Koordinate
					2,							// z-Koordinate
					t + 1.0/2
					);
			return v;
		}
		if(t>=3.0/4 && t<1.0){
			t -= 3.0/4;
			Vertex v(
					1				,		// x-Koordinate
					-sin(M_PI * 4 * t),		// y-Koordinate
					cos(M_PI * 4 * t)+1,	// z-Koordinate
					t + 3.0/4
					);
			return v;
		}
	}

	/**
	 * Gebogene Tennisballkurve, auf der Einheitssphäre liegend
	 */
	Vertex TennisBallB::f (double t) {
		double u = cos(M_PI * 2 * t);
		double v = sin(M_PI * 2 * t);

		return Vertex(
			u - (u*u*u / 3) + (u*v*v),
			v - (v*v*v / 3) + (v*u*u),
			(u*u) - (v*v),
			t
		);
	}
	
	/**
	 * Spiralkurve mit Radius 1
	 */
	Vertex Spirale::f (double t) {
		double s;
		if (t < 0.5) {
			s = t * 2;
			if (s < 0.9) {
				s *= 10.0 / 9;
				return Vertex(
					cos(M_PI * 4 * s),
					sin(M_PI * 4 * s),
					4 * s,
					t
				);
			} else {
				s = (s - 0.9) * 10;
				return Vertex( 1 - s, 0, 4, t);
			}
		} else {
			s = (t - 0.5) * 2;
			if (s < 0.9) {
				s *= 10.0 / 9;
				return Vertex(
					0,
					0,
					4 - (4 * s),
					t
				);
			} else {
				s = (s - 0.9) * 10;
				return Vertex( s, 0, 0, t);
			}
		}

	}


}
