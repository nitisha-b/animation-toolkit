#include "atkui/framework.h"

using namespace glm;
class Circles : public atkui::Framework
{
public:
   Circles() : atkui::Framework(atkui::Orthographic) {
   }

   virtual void setup() {
      theta = 0; 
      thetaRate = 0.02f;
      r = 35; 
   }

   virtual void scene() {
      for(int i = 0; i < 10; i++) {
         theta += thetaRate * dt();
         if(i % 2 > 0) {
            theta *= -1;
         }

         setColor(pallet[i]);
         float outerRad = i * r;
         
         for(int j = 0; j < 36; j++){
            theta += thetaRate * dt();
            float innerRadius = 12.0;
            px = outerRad * cos(theta + j*(10*3.14/180)) + 0.5 * width();
            py = outerRad * sin(theta + j*(10*3.14/180)) + 0.5 * height();
            drawSphere(vec3(px, py, 0), innerRadius);
         }
      }
   }

   float theta; 
   float thetaRate;
   float r; 
   float px;
   float py;

   std::vector<vec3> pallet =
      {
         vec3(0,165,227)/255.0f,
         vec3(141,215,191)/255.0f,
         vec3(255,150,197)/255.0f,
         vec3(255,87,104)/255.0f,
         vec3(255,162,58)/255.0f,
         vec3(0,165,227)/255.0f,
         vec3(141,215,191)/255.0f,
         vec3(255,150,197)/255.0f,
         vec3(255,87,104)/255.0f,
         vec3(255,162,58)/255.0f
      };

};

int main(int argc, char** argv)
{
   Circles viewer;
   viewer.run();
   return 0;
}
