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
      r = 45;
      t = 0.0f;
   }

   virtual void scene()
   {
      for (int i = 0; i < 7; i++)
      {
         theta += thetaRate * dt();
         idvTheta += thetaRate2 * dt();

         float t_x = i * px / width() / 10;
         t_x = glm::clamp(t_x, 0.0f, 1.0f);

         c_x0 = c_nw * (1 - theta) + c_ne * theta;
         c_x1 = c_sw * (1 - theta) + c_se * theta;
         vec3 c = c_x0 * (1 - theta) + c_x1 * theta;

         // change direction for alternating circles
         int direction = 1;
         if (i % 2 == 1)
         {
            direction = -1;
         }

         float outerRad = i * r;
         setColor(c);

         for (int j = 0; j < 36; j++)
         {
            // get interpolated color
            // vec3 c = interpolateColor();

            // float t_y = j * py / height() / 10;
            // t_y = glm::clamp(t_y, 0.0f, 1.0f);

            // vec3 c = c_x0 * (1 - theta) + c_x1 * theta;

            Matrix3 rot;
            Vector3 euler(30, 90, 0);

            float size = 18.0;
            px = outerRad * cos(direction * theta + j * (15 * M_PI / 180)) + 0.5 * width();
            py = outerRad * sin(direction * theta + j * (15 * M_PI / 180)) + 0.5 * height();

            Vector3 eulerRad = euler * Deg2Rad;
            
            push();
            translate(vec3(px, py, 0));
            rotate(eulerRad[0] + idvTheta, vec3(1, 0, 0));
            rotate(eulerRad[1] + idvTheta, vec3(0, 1, 0));
            rotate(eulerRad[2] + idvTheta, vec3(0, 0, 1));

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
   float t;
   float i = 0.0f;

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
           vec3(255, 162, 58) / 255.0f};

   vec3 c1 = vec3(0.15, 0.6, 0.19);
   vec3 c2 = vec3(0.24, 0.14, 0.75);
   vec3 c_nw = vec3(1, 1, 0);
   vec3 c_ne = vec3(0, 1, 1);
   vec3 c_sw = vec3(1, 0, 0);
   vec3 c_se = vec3(1, 0, 1);
   vec3 c_x0;
   vec3 c_x1;

};

int main(int argc, char **argv)
{
   Unique viewer;
   viewer.run();
   return 0;
}
