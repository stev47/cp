#ifndef MATH_H
#define MATH_H

class Vector {
	private:

	public:
		double x, y;
	
		Vector (double x, double y) : x(x), y(y) {}
		Vector (Vector* const vector);

		Vector operator+ (const Vector &v);
		Vector operator+= (const Vector &v);
		Vector operator- (const Vector &v);
		Vector operator-= (const Vector &v);
		double operator* (const Vector &v);

		Vector operator* (const double lambda);
		Vector operator*= (const double lambda);
		Vector operator/ (const double lambda);
		Vector operator/= (const double lambda);
		
		Vector operator- ();
		// Kreuzprodukt
		Vector operator~ ();			

		double norm ();
};


#endif
