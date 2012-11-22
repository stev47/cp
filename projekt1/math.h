#ifndef MATH_H
#define MATH_H

class Vector {
	private:

	public:
		double x, y, z;
	
		Vector (double x, double y, double z) : x(x), y(y), z(z) {}
		Vector (Vector* const vector);

		Vector operator+ (const Vector &v);
		Vector operator+= (const Vector &v);
		Vector operator- (const Vector &v);
		Vector operator-= (const Vector &v);
		Vector operator* (const double lambda);
		Vector operator*= (const double lambda);
		Vector operator/ (const double lambda);
		Vector operator/= (const double lambda);
		
		Vector operator- ();
		Vector operator^ (const Vector &v);			

		double norm ();
};


#endif
