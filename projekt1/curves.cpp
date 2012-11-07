#define _USE_MATH_DEFINES	// Nötig für die Konstante M_PI
#include <cmath>
#include "datastructures.h"
#include "curves.h"

namespace Curves {

	/**
	 * Kurve zum Testen
	 */
	Vertex Test::f (double t) {
		return Vertex (cos(M_PI * 2 * t), sin(M_PI * 2 * t), 0.5 * sin(M_PI * 8 * t), t);
	}

	/**
	 * Kreiskurve mit Radius 1
	 */
	Vertex Circle::f (double t) {
		Vertex v (cos(2 * M_PI * t), sin(2 * M_PI * t), 0, t);
		return v;
	}

	/**
	 * Viviani's Curve
	 * http://en.wikipedia.org/wiki/Viviani%27s_curve
	 */
	Vertex Viviani::f (double t) {
		Vertex v (a * (1 + cos(4 * M_PI * t)), a * sin(4 * M_PI * t), 2 * a * sin(2 * M_PI * t), t);
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
	 * Gebogene Tennisballkurve, mit Überschneidung von Flächen.
	 */
	Vertex TennisBallB::f (double t) {
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
					-1,								// x-Koordinate
					0.5*(-sin(M_PI * 6 * t)),		// y-Koordinate
					0.5*(-cos(M_PI * 6 * t))+0.5,	// z-Koordinate
					t + 1.0/4
					);
			return v;
		}
		if(t>=1.0/2 && t<=3.0/4) {
			t -= 1.0/2;
			Vertex v(
					-cos(M_PI * 4 * t),			// x-Koordinate
					0.5,						// y-Koordinate
					0.5-1.5*sin(M_PI * 4 * t),	// z-Koordinate
					t + 1.0/2
					);
			return v;
		}
		if(t>=3.0/4 && t<1.0){
			t -= 3.0/4;
			Vertex v(
					1				,		// x-Koordinate
					0.5*(-sin(M_PI * 6 * (t-3.0/4))),		// y-Koordinate
					0.5*(cos(M_PI * 6 * (t-3.0/4)))+0.5,	// z-Koordinate
					t + 3.0/4
					);
			return v;
		}
	}


}
