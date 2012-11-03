#include <cmath>
#include "math.h"

using namespace std;

Vector Vector::operator+ (const Vector &v) {
	return Vector(this->x + v.x, this->y + v.y, this->z + v.z);
}

Vector Vector::operator- (const Vector &v) {
	return Vector(this->x - v.x, this->y - v.y, this->z - v.z);
}

Vector Vector::operator- () {
	return Vector(-this->x, -this->y, -this->z);
}

Vector Vector::operator^ (const Vector &v) {
	double x = (this->y * v.z) - (this->z * v.y);
	double y = (this->z * v.x) - (this->x * v.z);
	double z = (this->x * v.y) - (this->y * v.x);

	return Vector(x, y, z);
}

double Vector::norm () {
	return sqrt((this->x * this->x) + (this->y * this->y) + (this->z * this->z));
}
