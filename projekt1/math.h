#ifndef MATH_H
#define MATH_H

class Vector {
	private:

	public:
		double x, y, z;
	
		Vector (double x, double y, double z) : x(x), y(y), z(z) {}
		Vector (Vector* const vector);

		/* Additives Inverse */
		Vector operator- ();

		/* Addition */
		Vector operator+ (const Vector &v) const;
		Vector& operator+= (const Vector &v);
		Vector operator- (const Vector &v) const;
		Vector& operator-= (const Vector &v);

		/* Skalarmultiplikation */
		Vector operator* (const double lambda) const;
		Vector operator*= (const double lambda);
		Vector operator/ (const double lambda) const;
		Vector operator/= (const double lambda);
		
		/* Skalarprodukt */
		double operator* (const Vector &v) const;

		/* Kreuzprodukt */
		Vector operator^ (const Vector &v) const;

		/* Euklidische Vektornorm */
		double norm () const;
};


#endif
