#include "atkmath/matrix3.h"
#include "atkmath/quaternion.h"

namespace atkmath
{
   Vector3 Matrix3::toEulerAnglesXYZ() const
   {
      float x = 0.0f; 
      float z = 0.0f;
      float y = 0.0f;
     
     // Middle angle is 90
      if(mM[0][2] == -1.0) {
         // set one angle to 0
         x = 0.0f;
         z = -atan2(mM[2][1], mM[1][1]);
         y = -(float)PI_2;
      }
      else if (mM[0][2] == 1.0)
      {
         x = 0.0f;
         z = atan2(mM[2][1], mM[1][1]);
         y = (float)PI_2;
      }
      // Normal conditions
      else {
         y = asin(mM[0][2]);
         x = -atan2(mM[1][2], mM[2][2]);
         z = -atan2(mM[0][1], mM[0][0]);
      }
      return Vector3(x,y,z);
   }

   Vector3 Matrix3::toEulerAnglesXZY() const
   {
      float x = 0.0f; 
      float y = 0.0f; 
      float z = 0.0f; 

      // if z = 90
      if (mM[0][1] == -1.0) {
         // set y = 0
         y = 0.0f; 
         x = atan2(mM[2][0], mM[1][0]);
         z = (float)PI_2;
      }
      // z = -90
      else if (mM[0][1] == 1.0) {
         y = 0.0f; 
         x = -atan2(mM[1][2], mM[2][2]);
         z = -(float)PI_2;
      }
      else {
         z = -asin(mM[0][1]);
         y = atan2(mM[0][2], mM[0][0]);
         x = atan2(mM[2][1], mM[1][1]);
      }
      return Vector3(x,y,z);
   }

   Vector3 Matrix3::toEulerAnglesYXZ() const
   {
      float x = 0.0f; 
      float y = 0.0f; 
      float z = 0.0f; 

      // x = 90
      if(mM[1][2] == -1.0) {
         x = (float)PI_2;
         // set z = 0
         z = 0.0f; 
         y = atan2(mM[0][1], mM[0][0]);
      }
      // x = -90
      else if (mM[1][2] == 1.0) {
         x = -(float)PI_2;
         z = 0.0f; 
         y = -atan2(mM[0][1], mM[0][0]);
      }
      else {
         x = -asin(mM[1][2]);
         y = atan2(mM[0][2], mM[2][2]);
         z = atan2(mM[1][0], mM[1][1]);
      }
      return Vector3(x,y,z);
   }

   Vector3 Matrix3::toEulerAnglesYZX() const
   {
      float x = 0.0f; 
      float y = 0.0f; 
      float z = 0.0f; 

      // z = 90
      if(mM[1][0] == 1.0) {
         y = 0.0f;
         x = atan2(mM[2][1], mM[2][2]);
         z = (float)PI_2;
      }
      else if (mM[1][0] == -1.0) {
         y = 0.0f;
         x = atan2(mM[2][1], mM[2][2]);
         z = -(float)PI_2;
      }
      else {
         z = asin(mM[1][0]);
         x = -atan2(mM[1][2], mM[1][1]);
         y = -atan2(mM[2][0], mM[0][0]);
      }
      return Vector3(x,y,z);
   }

   Vector3 Matrix3::toEulerAnglesZXY() const
   {
      float x = 0.0f; 
      float y = 0.0f; 
      float z = 0.0f; 

      // x = 90
      if (mM[2][1] == 1.0) {
         z = 0.0f;
         y = atan2(mM[1][0], mM[0][0]);
         x = (float)PI_2;
      }
      else if (mM[2][1] == -1.0) {
         z = 0.0f;
         y = -atan2(mM[1][0], mM[0][0]);
         x = -(float)PI_2;
      }
      else {
         x = asin(mM[2][1]);
         y = -atan2(mM[2][0], mM[2][2]);
         z = -atan2(mM[0][1], mM[1][1]);
      }
      return Vector3(x,y,z);
   }

   Vector3 Matrix3::toEulerAnglesZYX() const
   {
      float x = 0.0f; 
      float y = 0.0f; 
      float z = 0.0f; 

      // y = 90
      if (mM[2][0] == -1.0) {
         z = 0.0f;
         x = atan2(mM[0][1], mM[1][1]);
         y = (float)PI_2;
      }
      else if (mM[2][0] == 1.0) {
         z = 0.0f;
         x = -atan2(mM[0][1], mM[1][1]);
         y = -(float)PI_2;
      }
      else {
         x = atan2(mM[2][1], mM[2][2]);
         y = -asin(mM[2][0]);
         z = atan2(mM[1][0], mM[0][0]);
      }
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
      Quaternion quat;
      quat.fromMatrix(*this);
      quat.toAxisAngle(axis, angleRad);  
   }

   void Matrix3::fromAxisAngle(const Vector3 &axis, double angleRad)
   {
      *this = Identity;
      // double a = angleRad;
      // float x = axis[0]; 
      // float y = axis[1];
      // float z = axis[2];

      // m11 = cos(a) + (1 - cos(a)) * pow(x,2);
      // m12 = -sin(a) * z + (1- cos(a)) * x * y;
      // m13 = y * sin(a) + x * z * (1- cos(a));

      // m21 = -z * sin(a) + (1- cos(a)) * x * y; 
      // m22 = cos(a) + (1 - cos(a)) * pow(y,2);
      // m23 = -x * sin(a) + (1 - cos(a)) * y * z;

      // m31 = y * sin(a) + x * y * (1- cos(a));
      // m32 = -x * sin(a) + (1 - cos(a)) * y * z;
      // m33 = cos(a) + (1 - cos(a)) * pow(z,2);

      Quaternion quat;
      quat.fromAxisAngle(axis, angleRad);
      *this = quat.toMatrix();

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