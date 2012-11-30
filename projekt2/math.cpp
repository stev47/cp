#include <cmath>
#include "math.h"

using namespace std;

Vector Vector::operator+ (const Vector &v) {
	Vector out(*this);
	out += v;
	return out; 
}

Vector Vector::operator+= (const Vector &v) {
	this->x += v.x;
	this->y += v.y;
	return *this;
}

Vector Vector::operator- (const Vector &v) {
	return Vector(this->x - v.x, this->y - v.y);
}

Vector Vector::operator-= (const Vector &v) {
	this->x -= v.x;
	this->y -= v.y;
	return *this;
}

double Vector::operator* (const Vector &v) {
	return (this->x * v.x) + (this->y * v.y);
}

Vector Vector::operator* (const double lambda) {
	return Vector(this->x * lambda, this->y * lambda);
}

Vector Vector::operator*= (const double lambda) {
	this->x *= lambda;
	this->y *= lambda;
	return *this;
}

Vector Vector::operator/ (const double lambda) {
	return Vector(this->x / lambda, this->y / lambda);
}
Vector Vector::operator/= (const double lambda) {
	this->x /= lambda;
	this->y /= lambda;
	return *this;
}

Vector Vector::operator- () {
	return Vector(-this->x, -this->y);
}

Vector Vector::operator~ () {
	double x = this->y;
	double y = -this->x;

	return Vector(x, y);
}

double Vector::norm () {
	return sqrt((this->x * this->x) + (this->y * this->y));
}

