#include <cmath>
#include "math.h"

using namespace std;

Vector Vector::operator- () {
	return Vector(-this->x, -this->y, -this->z);
}

Vector Vector::operator+ (const Vector &v) const {
	Vector out(*this);
	out += v;
	return out;
}

Vector& Vector::operator+= (const Vector &v) {
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
	return *this;
}

Vector Vector::operator- (const Vector &v) const {
	return Vector(this->x - v.x, this->y - v.y, this->z - v.z);
}

Vector& Vector::operator-= (const Vector &v) {
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
	return *this;
}

Vector Vector::operator* (const double lambda) const {
	return Vector(this->x * lambda, this->y * lambda, this->z * lambda);
}

Vector Vector::operator*= (const double lambda) {
	this->x *= lambda;
	this->y *= lambda;
	this->z *= lambda;
	return *this;
}

Vector Vector::operator/ (const double lambda) const {
	return Vector(this->x / lambda, this->y / lambda, this->z / lambda);
}

Vector Vector::operator/= (const double lambda) {
	this->x /= lambda;
	this->y /= lambda;
	this->z /= lambda;
	return *this;
}

double Vector::operator* (const Vector &v) const {
	return (this->x * v.x) + (this->y * v.y) + (this->z * v.z);
}

Vector Vector::operator^ (const Vector &v) const {
	double x = (this->y * v.z) - (this->z * v.y);
	double y = (this->z * v.x) - (this->x * v.z);
	double z = (this->x * v.y) - (this->y * v.x);

	return Vector(x, y, z);
}

double Vector::norm () const {
	return sqrt((this->x * this->x) + (this->y * this->y) + (this->z * this->z));
}

