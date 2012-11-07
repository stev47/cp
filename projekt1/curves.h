#ifndef CURVES_H
#define CURVES_H

#include <cmath>
#include "datastructures.h"


namespace Curves {
	/**
	 * Abstrakte Kurvenklasse
	 */
	class Curve {
		public:
			virtual Vertex f (double f) =0;
	};

	class Test : public Curve {
		virtual Vertex f (double t);
	};

	class Circle : public Curve {
		virtual Vertex f (double t);
	};

	class Viviani : public Curve {
		double a;
		public:
				Viviani (double a = 5) : a(a) {}
				virtual Vertex f (double t);
	};

	class TennisBall : public Curve {
		virtual Vertex f (double t);
	};

	class TennisBallB : public Curve {
		virtual Vertex f (double t);
	};

}

#endif
