#include "atkmath/quaternion.h"
#include "atkmath/matrix3.h"
#include "atkmath/vector3.h"

namespace atkmath {

Quaternion Quaternion::Slerp(const Quaternion& q0, const Quaternion& q1, double t)
{
	// TODO
	return Quaternion(1,0,0,0);
}

void Quaternion::toAxisAngle (Vector3& axis, double& angleRad) const
{
	angleRad = 2 * acos(this->mW);

	// check if angleRad is close to 0 	
	// If 0 - there is no rotation, hardcode an axis w/ unit length
	if (std::abs(angleRad) < 0.000001) {
		Vector3 *a = new Vector3(0, 0, 1);
		axis = *a;
		// axis[0] = 0; 
		// axis[1] = 0; 
		// axis[2] = 1;
		std::cout << "hi" << std::endl;
	}
	else {
		float sinVal = sin(angleRad/2);
		float vX = this->mX/sinVal;
		float vY = this->mY/sinVal; 
		float vZ = this->mZ/sinVal; 
		Vector3 *a = new Vector3(vX, vY, vZ);
		axis = *a;
		// std::cout << axis << std::endl;
	} 
}

void Quaternion::fromAxisAngle (const Vector3& axis, double angleRad)
{
	float vx = sin(angleRad/2) * axis[0];
	float vy = sin(angleRad/2) * axis[1];
	float vz = sin(angleRad/2) * axis[2];
	float vw = cos(angleRad/2);
	*this = Quaternion(vx, vy, vz, vw);
}

Matrix3 Quaternion::toMatrix () const
{
	Matrix3 m = Matrix3(); 

	float x = this->mX; 
	float y = this->mY; 
	float z = this->mZ;
	float w = this->mW;

	m[0][0] = 1 - 2 * (pow(y,2) + pow(z,2));
	m[0][1] = 2 * (x * y - w * z);
	m[0][2] = 2 * (x * z + w * y);

	m[1][0] = 2 * (x * y + w * z);
	m[1][1] = 1 - 2 * (pow(x,2) + pow(z,2));
	m[1][2] = 2 * (y * z - w * x);

	m[2][0] = 2 * (x * z - w * y);
	m[2][1] = 2 * (y * z + w * x);
	m[2][2] = 1 - 2 * (pow(y,2) + pow(x,2));

	return m;
}

void Quaternion::fromMatrix(const Matrix3& rot)
{
	float w2 = (1/4) * (1 + rot[0][0] + rot[1][1] + rot[2][2]);
	float x2 = (1/4) * (1 + rot[0][0] - rot[1][1] - rot[2][2]);
	float y2 = (1/4) * (1 - rot[0][0] + rot[1][1] - rot[2][2]);
	float z2 = (1/4) * (1 - rot[0][0] - rot[1][1] + rot[2][2]);

	if (w2 > x2 && w2 > y2 && w2 > z2) {
		this->mW = sqrt(w2);
		this->mX = (1/(4*this->mW)) * (rot[2][1] - rot[1][2]);
		this->mY = (1/(4*this->mW)) * (rot[0][2] - rot[2][0]);
		this->mZ = (1/(4*this->mW)) * (rot[1][0] - rot[0][1]);
	}
	else if (x2 > w2 && x2 > y2 && x2 > z2) {
		this->mX = sqrt(x2);
		this->mW = (1/(4 * this->mX)) * (rot[2][1] - rot[1][2]);
		this->mY = (1/(4 * this->mX)) * (rot[1][0] + rot[0][1]);
		this->mZ = (1/(4 * this->mX)) * (rot[0][2] + rot[2][0]);
	}
	else if (y2 > w2 && y2 > x2 && y2 > z2) {
		this->mY = sqrt(y2);
		this->mW = (1/(4 * this->mY)) * (rot[0][2] - rot[2][0]);
		this->mX = (1/(4 * this->mY)) * (rot[1][0] + rot[0][1]);
		this->mZ = (1/(4 * this->mY)) * (rot[1][2] + rot[2][1]);
	}
	else {	// max == z2
		this->mZ = sqrt(z2);
		this->mW = (1/(4 * this->mZ)) * (rot[1][0] - rot[0][1]);
		this->mX = (1/(4 * this->mZ)) * (rot[0][2] + rot[2][0]);
		this->mY = (1/(4 * this->mZ)) * (rot[1][2] + rot[2][1]);
	}
}

}