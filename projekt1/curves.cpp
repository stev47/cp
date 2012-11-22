#define _USE_MATH_DEFINES	// Nötig für die Konstante M_PI
#include <cmath>
#include "datastructures.h"
#include "curves.h"
#include <iostream>

namespace Curves {

	Vertex Curve::f (double t) {
		return Vertex(0,0,0);
	}

	/**
	 * Kurve zum Testen
	 */
	Vertex Test::f (double t) {
		double u = 9*cos(M_PI * 2 * t);
		double v = 9*sin(M_PI * 2 * t);

		return Vertex(
			u * cos(v),
			u * sin(v),
			3 * v,
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
		if(t>=0.0 && t<=1.0/16) {
			Vertex v(
					1-cos(M_PI * 16 * t),		// x-Koordinate
					sin(M_PI * 16 * t),		// y-Koordinate
					0,						// z-Koordinate
					t
					);
			return v;
		}
		if(t>=1.0/16 && t<=2.0/16) {
			t -= 1.0/16;
			Vertex v(
					1+cos(M_PI * 16 * t),		// x-Koordinate
					-sin(M_PI * 16 * t),		// y-Koordinate
					0,						// z-Koordinate
					t + 1.0/16
					);
			return v;
		}
		if(t>=2.0/16 && t<=3.0/16){
			t -= 2.0/16;
			Vertex v(
					1-cos(M_PI * 16 * t),		// x-Koordinate
					sin(M_PI * 16 * t),		// y-Koordinate
					sin(M_PI * 8 * t),						// z-Koordinate
					t + 2.0/16
					);
			return v;
		}
		if(t>=3.0/16 && t<=4.0/16) {
			t -= 3.0/16;
			Vertex v(
					1+cos(M_PI * 16 * t),		// x-Koordinate
					-sin(M_PI * 16 * t),		// y-Koordinate
					1-sin(M_PI * 8 * t),					// z-Koordinate
					t + 3.0/16
					);
			return v;
		}
		if(t>=4.0/16 && t<=5.0/16){
			t -= 4.0/16;
			Vertex v(
					0,							// x-Koordinate
					sin(M_PI * 16 * t),			// y-Koordinate
					1-cos(M_PI * 16 * t),		// z-Koordinate
					t + 4.0/16
					);
			return v;
		}
		if(t>=5.0/16 && t<=6.0/16) {
			t -= 5.0/16;
			Vertex v(
					0,		// x-Koordinate
					-sin(M_PI * 16 * t),		// y-Koordinate
					1+cos(M_PI * 16 * t),					// z-Koordinate
					t + 5.0/16
					);
			return v;
		}
		if(t>=6.0/16 && t<=7.0/16){
			t -= 6.0/16;
			Vertex v(
					-1+cos(M_PI * 16 * t),							// x-Koordinate
					sin(M_PI * 16 * t),			// y-Koordinate
					32*t,		// z-Koordinate
					t + 6.0/16
					);
			return v;
		}
		if(t>=7.0/16 && t<=8.0/16) {
			t -= 7.0/16;
			Vertex v(
					-1-cos(M_PI * 16 * t),		// x-Koordinate
					-sin(M_PI * 16 * t),		// y-Koordinate
					2-32*t,					// z-Koordinate
					t + 7.0/16
					);
			return v;
		}
		if(t>=8.0/16 && t<=9.0/16){
			t -= 8.0/16;
			Vertex v(
					-1+cos(M_PI * 16 * t),							// x-Koordinate
					sin(M_PI * 16 * t),			// y-Koordinate
					0,		// z-Koordinate
					t + 8.0/16
					);
			return v;
		}
		if(t>=9.0/16 && t<=10.0/16) {
			t -= 9.0/16;
			Vertex v(
					-1-cos(M_PI * 16 * t),		// x-Koordinate
					-sin(M_PI * 16 * t),		// y-Koordinate
					0,					// z-Koordinate
					t + 9.0/16
					);
			return v;
		}
		if(t>=10.0/16 && t<=11.0/16){
			t -= 10.0/16;
			Vertex v(
					-1+cos(M_PI * 16 * t),							// x-Koordinate
					sin(M_PI * 16 * t),			// y-Koordinate
					-32*t,		// z-Koordinate
					t + 10.0/16
					);
			return v;
		}
		if(t>=11.0/16 && t<=12.0/16) {
			t -= 11.0/16;
			Vertex v(
					-1-cos(M_PI * 16 * t),		// x-Koordinate
					-sin(M_PI * 16 * t),		// y-Koordinate
					-2+32*t,					// z-Koordinate
					t + 11.0/16
					);
			return v;
		}
		if(t>=12.0/16 && t<=13.0/16){
			t -= 12.0/16;
			Vertex v(
					0,							// x-Koordinate
					sin(M_PI * 16 * t),			// y-Koordinate
					-1+cos(M_PI * 16 * t),		// z-Koordinate
					t + 12.0/16
					);
			return v;
		}
		if(t>=13.0/16 && t<=14.0/16) {
			t -= 13.0/16;
			Vertex v(
					0,		// x-Koordinate
					-sin(M_PI * 16 * t),		// y-Koordinate
					-1-cos(M_PI * 16 * t),					// z-Koordinate
					t + 13.0/16
					);
			return v;
		}
		if(t>=14.0/16 && t<=15.0/16){
			t -= 14.0/16;
			Vertex v(
					1-cos(M_PI * 16 * t),							// x-Koordinate
					sin(M_PI * 16 * t),			// y-Koordinate
					-32*t,		// z-Koordinate
					t + 14.0/16
					);
			return v;
		}
		if(t>=15.0/16 && t<=16.0/16) {
			t -= 15.0/16;
			Vertex v(
					1+cos(M_PI * 16 * t),		// x-Koordinate
					-sin(M_PI * 16 * t),		// y-Koordinate
					-2+32*t,					// z-Koordinate
					t + 15.0/16
					);
			return v;
		}
	}


}
