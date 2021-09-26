#include "atkui/framework.h"
using namespace glm;
using namespace std;

class Unique : public atkui::Framework {
 public:
  Unique() : atkui::Framework(atkui::Orthographic) {
  }

   virtual void setup() {
      c1.b0 = vec3(100,  50, 0);
      c1.b1 = vec3(200, 200, 0);
      c1.b2 = vec3(50, 300, 0);
      c1.b3 = vec3(100, 400, 0);
      c1.color = agl::randomUnitVector()/2.5f;

      c2.b0 = vec3(150,  50, 0);
      c2.b1 = vec3(250, 200, 0);
      c2.b2 = vec3(100, 300, 0);
      c2.b3 = vec3(150, 400, 0);
      c2.color = agl::randomUnitVector()/2.5f;

      c3.b0 = vec3(200,  50, 0);
      c3.b1 = vec3(300, 200, 0);
      c3.b2 = vec3(150, 300, 0);
      c3.b3 = vec3(200, 400, 0);
      c3.color = agl::randomUnitVector()/2.5f;

      c4.b0 = vec3(250,  50, 0);
      c4.b1 = vec3(350, 200, 0);
      c4.b2 = vec3(200, 300, 0);
      c4.b3 = vec3(250, 400, 0);
      c4.color = agl::randomUnitVector()/2.5f;

      curves.push_back(c1);
      curves.push_back(c2);
      curves.push_back(c3);
      curves.push_back(c4);

      t = 0.0;
      timer = 0.0;

      f1.b0 = vec3(100,  50, 0);
      f1.b1 = vec3(100, 200, 0);
      f1.b2 = vec3(150, 300, 0);
      f1.b3 = vec3(100, 400, 0);
      f1.color = agl::randomUnitVector()/2.5f;
   }

   virtual void scene() {
      for(Curve& c: curves) {
         if (t >= 0.5){
            t = 0.0;
            c.color = agl::randomUnitVector();
         }
         t += 0.005;

         for (float i = 0.0; i < 1.0; i += 0.002)
         {
            bernstein(c.b0, c.b1, c.b2, c.b3, i, c.color);
         }
      }

   // Curve current;
   //  current.b0 = interpolate(c1.b0, f1.b0, t);
   //  current.b1 = interpolate(c1.b1, f1.b1, t);
   //  current.b2 = interpolate(c1.b2, f1.b2, t);
   //  current.b3 = interpolate(c1.b3, f1.b3, t);
   //  current.color = agl::randomUnitVector()/2.5f;

   // if (timer > 1.0)
   //  {
   //    timer = 0.0;
   //    c1 = f1;
   //  }

   // else
   //  {
      
   //    timer += 0.1;
   //  }

   //  for (float i = 0.0; i < 1.0; i += 0.002)
   //    {
   //      bernstein(current.b0, current.b1, current.b2, current.b3, i, current.color);
   //    }

   }

   virtual void bernstein(vec3 b0, vec3 b1, vec3 b2, vec3 b3, float i, vec3 color) {
      float term1 = (std::pow((1-i),3) );
      float term2 = (3*i* std::pow((1-i),2) );
      float term3 = (3*std::pow(i,2)*(1-i) );
      float term4 = (std::pow(i,3) );
      p = term1 * b0 + term2 * b1 + term3 * b2 + term4 * b3;
      setColor(color);
      drawSphere(p, 3);
   }

   virtual vec3 interpolate(vec3 b0, vec3 b1, float t)
   {
    return b0 * (1 - t) + b1 * t;
   }

   virtual vec3 generateRandomVector()
   {
      // Using agl::random() was causing the program to be very slow
      return vec3((float)(rand() % (int)width()), (float)(rand() % (int)height()), 0);
   }

   struct Curve {
    vec3 b0;
    vec3 b1;
    vec3 b2;
    vec3 b3;
    vec3 color;
  };

   private:
      vec3 B0 = vec3(100,  50, 0);
      vec3 B1 = vec3(200, 200, 0);
      vec3 B2 = vec3(50, 300, 0);
      vec3 B3 = vec3(100, 400, 0);
      vec3 p;
      Curve c1;
      Curve c2;
      Curve c3;
      Curve c4;
      list<Curve> curves;
      float t;
      float timer;

      Curve f1;
};

int main(int argc, char** argv) {
   Unique viewer;
   viewer.run();
   return 0;
}

