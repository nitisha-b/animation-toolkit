#include "atkmath/matrix3.h"
#include "atkmath/quaternion.h"

namespace atkmath
{

   Vector3 Matrix3::toEulerAnglesXYZ() const
   {
      float y = asin(mM[0][2]);
      float x = -atan2(mM[1][2], mM[2][2]);
      float z = -atan2(mM[0][1], mM[0][0]);
      return Vector3(x,y,z);
   }

   Vector3 Matrix3::toEulerAnglesXZY() const
   {
      float z = -asin(mM[0][1]);
      float y = atan2(mM[0][2], mM[0][0]);
      float x = atan2(mM[2][1], mM[1][1]);
      return Vector3(x,y,z);
   }

   Vector3 Matrix3::toEulerAnglesYXZ() const
   {
      float x = -asin(mM[1][2]);
      float y = atan2(mM[0][2], mM[2][2]);
      float z = atan2(mM[1][0], mM[1][1]);
      return Vector3(x,y,z);
   }

   Vector3 Matrix3::toEulerAnglesYZX() const
   {
      float z = asin(mM[1][0]);
      float x = -atan2(mM[1][2], mM[1][1]);
      float y = -atan2(mM[2][0], mM[0][0]);
      return Vector3(x,y,z);
   }

   Vector3 Matrix3::toEulerAnglesZXY() const
   {
      float x = asin(mM[2][1]);
      float y = -atan2(mM[2][0], mM[2][2]);
      float z = -atan2(mM[0][1], mM[1][1]);
      return Vector3(x,y,z);
   }

   Vector3 Matrix3::toEulerAnglesZYX() const
   {
      float x = atan2(mM[2][1], mM[2][2]);
      float y = -asin(mM[2][0]);
      float z = atan2(mM[1][0], mM[0][0]);
      return Vector3(x,y,z);
   }

   void Matrix3::fromEulerAnglesXYZ(const Vector3 &angleRad)
   {
      *this = Identity;
      *this = computeRx(angleRad[0]) * computeRy(angleRad[1]) * computeRz(angleRad[2]);
   }

   void Matrix3::fromEulerAnglesXZY(const Vector3 &angleRad)
   {
      *this = Identity;
      *this = computeRx(angleRad[0]) * computeRz(angleRad[2]) * computeRy(angleRad[1]);
   }

   void Matrix3::fromEulerAnglesYXZ(const Vector3 &angleRad)
   {
      *this = Identity;
      *this = computeRy(angleRad[1]) * computeRx(angleRad[0]) * computeRz(angleRad[2]);
   }

   void Matrix3::fromEulerAnglesYZX(const Vector3 &angleRad)
   {
      *this = Identity;
      *this = computeRy(angleRad[1]) * computeRz(angleRad[2]) * computeRx(angleRad[0]);
   }

   void Matrix3::fromEulerAnglesZXY(const Vector3 &angleRad)
   {
      *this = Identity;
      *this = computeRz(angleRad[2]) * computeRx(angleRad[0]) * computeRy(angleRad[1]);
   }

   void Matrix3::fromEulerAnglesZYX(const Vector3 &angleRad)
   {
      *this = Identity;
      *this = computeRz(angleRad[2]) * computeRy(angleRad[1]) * computeRx(angleRad[0]);

   }

   void Matrix3::toAxisAngle(Vector3 &axis, double &angleRad) const
   {
      // TODO
   }

   void Matrix3::fromAxisAngle(const Vector3 &axis, double angleRad)
   {
      // TODO
      *this = Identity;

   }

   Matrix3 Matrix3::computeRx(float x) {
      Matrix3 m = Matrix3();
      m[0][0] = 1; 
      m[0][1] = 0; 
      m[0][2] = 0; 
      m[1][0] = 0;
      m[2][0] = 0; 
      m[1][1] = cos(x); 
      m[1][2] = -sin(x);
      m[2][1] = sin(x);
      m[2][2] = cos(x);
      return m;
   }

   Matrix3 Matrix3::computeRy(float y) {
      Matrix3 m = Matrix3();
      m[0][0] = cos(y); 
      m[0][1] = 0; 
      m[0][2] = sin(y); 
      m[1][0] = 0;
      m[2][0] = -sin(y); 
      m[1][1] = 1; 
      m[1][2] = 0;
      m[2][1] = 0;
      m[2][2] = cos(y);
      return m;
   }

   Matrix3 Matrix3::computeRz(float z) {
      Matrix3 m = Matrix3();
      m[0][0] = cos(z); 
      m[0][1] = -sin(z); 
      m[0][2] = 0; 
      m[1][0] = sin(z);
      m[2][0] = 0; 
      m[1][1] = cos(z); 
      m[1][2] = 0;
      m[2][1] = 0;
      m[2][2] = 1;
      return m; 
   }

}