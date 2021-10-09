#include "atkui/framework.h"
#include "atkmath/matrix3.h"

using namespace glm;
using atkmath::Deg2Rad;
using glm::vec3;
// using atkmath::Rad2Deg;
using atkmath::Matrix3;
using atkmath::Vector3;

class Unique : public atkui::Framework
{
public:
   Unique() : atkui::Framework(atkui::Orthographic)
   {
   }

   virtual void setup()
   {
      theta = 0;
      thetaRate = 0.02f;
      idvTheta = 0.0;
      thetaRate2 = 0.05f;
      r = 40;
   }

   virtual void scene()
   {
      for (int i = 0; i < 8; i++)
      {
         theta += thetaRate * dt();
         idvTheta += thetaRate2 * dt();

         float t_x = i * x / width() / 10;
         t_x = glm::clamp(t_x, 0.0f, 1.0f);

         x0 = pallet[i+1] * (1 - t_x) + pallet[i+4] * t_x;
         x1 = pallet[i] * (1 - t_x) + pallet[i+2] * t_x;

         x2 = pallet[i] * (1 - t_x) + pallet[i+1] * t_x;
         x3 = pallet[i+2] * (1 - t_x) + pallet[i+3] * t_x;

         // change direction for alternating circles
         int direction = 1;
         if (i % 2 == 1)
         {
            direction = -1;
         }

         float outerRad = i * r;

         for (int j = 0; j < 36; j++)
         {
            // interpolate color
            float t_y = j * y / height() / 10;
            t_y = glm::clamp(t_y, 0.0f, 1.0f);

            vec3 c1 = x0 * (1 - t_y) + x1 * t_y;
            vec3 c2 = x2 * (1 - t_y) + x3 * t_y;

            x = i * width()/10 + height()/20;
            y = j * height()/10 + height()/20; 

            if (direction == 1){
               setColor(c1);
            }
            else {
               setColor(c2);
            }

            Matrix3 rot;
            Vector3 euler(90, 45, 13);

            float size = 18.0;
            px = outerRad * cos(direction * theta + j * (18 * M_PI / 180)) + 0.5 * width();
            py = outerRad * sin(direction * theta + j * (18 * M_PI / 180)) + 0.5 * height();

            Vector3 eulerRad = euler * Deg2Rad;
            
            push();
            translate(vec3(px, py, 0));
            rotate(direction * eulerRad[0] + idvTheta, vec3(1, 0, 0));
            rotate(direction * eulerRad[1] + idvTheta, vec3(0, 1, 0));
            rotate(direction * eulerRad[2] + idvTheta, vec3(0, 0, 1));
            drawCone(vec3(0), size);
            pop();
         }
      }
   }

   float theta;
   float thetaRate;
   float r;
   float px;
   float py;
   float idvTheta;
   float thetaRate2;
   float x = 0; 
   float y = 0;
   vec3 x0, x1, x2, x3 = vec3(0);

   std::vector<vec3> pallet =
       {
           vec3(0, 165, 227) / 255.0f,
           vec3(141, 215, 191) / 255.0f,
           vec3(255, 150, 197) / 255.0f,
           vec3(255, 87, 104) / 255.0f,
           vec3(255, 162, 58) / 255.0f,
           vec3(0, 165, 227) / 255.0f,
           vec3(141, 215, 191) / 255.0f,
           vec3(255, 150, 197) / 255.0f,
           vec3(255, 87, 104) / 255.0f,
           vec3(255, 162, 58) / 255.0f,
           vec3(196, 215, 113)/ 255.0f,
           vec3(41, 237, 216) / 255.0f };

};

int main(int argc, char **argv)
{
   Unique viewer;
   viewer.run();
   return 0;
}
