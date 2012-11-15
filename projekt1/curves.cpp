#define _USE_MATH_DEFINES	// Nötig für die Konstante M_PI
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
		return Vertex ((sin(M_PI * 8 * t)+2.0) * cos(M_PI * 2 * t), (sin(M_PI * 8 * t)+2.0) * sin(M_PI * 2 * t), cos(M_PI * 4 * t)  , t);
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
		if(t>=0.0 && t<=1.0/8) {
			Vertex v(
					cos(M_PI * 8 * t),		// x-Koordinate
					sin(M_PI * 8 * t),		// y-Koordinate
					0,						// z-Koordinate
					t
					);
			return v;
		}
		if(t>=1.0/8 && t<=1.0/4){
			t -= 1.0/8;
			Vertex v(
					-2+cos(M_PI * 8 * t),	// x-Koordinate
					-sin(M_PI * 8 * t),		// y-Koordinate
					0,						// z-Koordinate
					t + 1.0/8
					);
			return v;
		}
		if(t>=1.0/4 && t<=3.0/8) {
			t -= 1.0/4;
			Vertex v(
					-3,							// x-Koordinate
					a*sin(M_PI * 8 * t),			// y-Koordinate
					a*(-cos(M_PI * 8 * t)+1),		// z-Koordinate
					t + 1.0/4
					);
			return v;
		}
		if(t>=3.0/8 && t<1.0/2){
			t -= 3.0/8;
			Vertex v(
					-2-cos(M_PI * 8 * t),	// x-Koordinate
					-sin(M_PI * 8 * t),		// y-Koordinate
					2*a,						// z-Koordinate
					t + 3.0/8
					);
			return v;
		}
		if(t>=1.0/2 && t<5.0/8){
			t -= 1.0/2;
			Vertex v(
					-cos(M_PI * 8 * t),		// x-Koordinate
					sin(M_PI * 8 * t),		// y-Koordinate
					2*a,						// z-Koordinate
					t + 1.0/2
					);
			return v;
		}
		if(t>=5.0/8 && t<3.0/4){
			t -= 5.0/8;
			Vertex v(
					2-cos(M_PI * 8 * t),	// x-Koordinate
					-sin(M_PI * 8 * t),		// y-Koordinate
					2*a,						// z-Koordinate
					t + 5.0/8
					);
			return v;
		}
		if(t>=3.0/4 && t<7.0/8){
			t -= 3.0/4;
			Vertex v(
					3,						// x-Koordinate
					a*sin(M_PI * 8 * t),		// y-Koordinate
					a*(1+cos(M_PI * 8 * t)),	// z-Koordinate
					t + 3.0/4
					);
			return v;
		}
		if(t>=7.0/8 && t<1.0){
			t -= 7.0/8;
			Vertex v(
					2+cos(M_PI * 8 * t),	// x-Koordinate
					-sin(M_PI * 8 * t),		// y-Koordinate
					0,						// z-Koordinate
					t + 7.0/8
					);
			return v;
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
					1,										// x-Koordinate
					0.5*(-sin(M_PI * 6 * (t-3.0/4))),		// y-Koordinate
					0.5*(cos(M_PI * 6 * (t-3.0/4)))+0.5,	// z-Koordinate
					t + 3.0/4
					);
			return v;
		}
	}
	
	/**
	 * Spiralkurve mit Radius 1
	 */
	Vertex Spirale::f (double t) {
  if(t>=0.0 && t<=1.0/8) {
			Vertex v(
					1-cos(M_PI * 16 * t),		// x-Koordinate
					sin(M_PI * 16 * t),		// y-Koordinate
					0,						// z-Koordinate
					t
					);
			return v;
		}
		if(t>=1.0/8 && t<=1.0/4){
			t -= 1.0/8;
			Vertex v(
					1-cos(M_PI * 16 * t),		// x-Koordinate
					sin(M_PI * 16 * t),		// y-Koordinate
					8*t,						// z-Koordinate
					t + 1.0/8
					);
			return v;
		}
		if(t>=1.0/4 && t<=3.0/8) {
			t -= 1.0/4;
			Vertex v(
					1-cos(M_PI * 16 * t),		// x-Koordinate
					sin(M_PI * 16 * t),		// y-Koordinate
					2*sin(M_PI * 8 * t),		// z-Koordinate
					t + 1.0/4
					);
			return v;
		}
		if(t>=3.0/8 && t<1.0/2){
			t -= 3.0/8;
			Vertex v(
					1-cos(M_PI * 16 * t),		// x-Koordinate
					sin(M_PI * 16 * t),		// y-Koordinate
					3*sin(M_PI * 8 * t),		// z-Koordinate
					t + 3.0/8
					);
			return v;
		}
		if(t>=1.0/2 && t<5.0/8){
			t -= 1.0/2;
			Vertex v(
					1-cos(M_PI * 16 * t),		// x-Koordinate
					sin(M_PI * 16 * t),		// y-Koordinate
					4*sin(M_PI * 8 * t),		// z-Koordinate
					t + 1.0/2
					);
			return v;
		}
		if(t>=5.0/8 && t<3.0/4){
			t -= 5.0/8;
			Vertex v(
					1-cos(M_PI * 16 * t),		// x-Koordinate
					sin(M_PI * 16 * t),		// y-Koordinate
					5*sin(M_PI * 8 * t),		// z-Koordinate
					t + 5.0/8
					);
			return v;
		}
		if(t>=3.0/4 && t<7.0/8){
			t -= 3.0/4;
			Vertex v(
					1-cos(M_PI * 16 * t),		// x-Koordinate
					sin(M_PI * 16 * t),		// y-Koordinate
					6*sin(M_PI * 8 * t),		// z-Koordinate
					t + 3.0/4
					);
			return v;
		}
		if(t>=7.0/8 && t<1.0){
			t -= 7.0/8;
			Vertex v(
					1-cos(M_PI * 16 * t),		// x-Koordinate
					sin(M_PI * 16 * t),		// y-Koordinate
					7*sin(M_PI * 8 * t),		// z-Koordinate
					t + 7.0/8
					);
			return v;
		}
	}


}
