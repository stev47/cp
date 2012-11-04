#ifndef CURVES_H
#define CURVES_H

#include <cmath>
#include "net.h"
/**
 * Kreiskurve mit Radius 1
 */
class CircleNet : public Net {
	virtual Vertex f (double t) {
		Vertex v (cos(M_PI * t), sin(M_PI * t), 0, t);
		return v;
	}
};

/**
 * Viviani's Curve
 * http://en.wikipedia.org/wiki/Viviani%27s_curve
 */
class VivianiCurveNet : public Net {
	double a;
	public:
	VivianiCurveNet (double a = 5) : a(a) {}
	virtual Vertex f (double t) {
		Vertex v (a * (1 + cos(4 * M_PI * t)), a * sin(4 * M_PI * t), 2 * a * sin(2 * M_PI * t), t);
		return v;
	}
};

/**
 * Annähernd eine Tennisballkurve, zusammengesetzt aus vier
 * Halbkreisen mit Radius 1.
 */
class TennisBallCurveNet : public Net {
	public:
		virtual Vertex f (double t) {
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
						-cos(M_PI * 4 * t)+1,		// z-Koordinate
						t + 1.0/4
						);
				return v;
			}
			if(t>=1.0/2 && t<=3.0/4) {
				t -= 1.0/2;
				Vertex v(
						-cos(M_PI * 4 * t),		// x-Koordinate
						sin(M_PI * 4 * t),		// y-Koordinate
						2,						// z-Koordinate
						t + 1.0/2
						);
				return v;
			}
			if(t>=3.0/4 && t<1.0){
				t -= 3.0/4;
				Vertex v(
						1,						// x-Koordinate
						-sin(M_PI * 4 * t),		// y-Koordinate
						cos(M_PI * 4 * t)+1,		// z-Koordinate
						t + 3.0/4
						);
				return v;
			}
		}
};

#endif
