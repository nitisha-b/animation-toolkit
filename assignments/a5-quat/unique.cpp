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
      c_nw = vec3(1, 1, 0);
      c_ne = vec3(0, 1, 1);
      c_sw = vec3(1, 0, 0);
      c_se = vec3(1, 0, 1);
      t = 0;
      x = 0;
      y = 0;
      t_x = 0;
      t_y = 0;
      _mouseX = width() * 0.5;
      _mouseY = height() * 0.5;
      theta = 0.0;
      thetaRate = 0.6;
      mousePos = vec3(_mouseX, _mouseY, 0);
   }

   virtual void scene()
   {
      float size = height() / 20;

      mousePos = vec3(mousePosition().x, mousePosition().y, 0);
      mouseMotion(mousePosition().x, mousePosition().y, mousePosition().x - _mouseX, mousePosition().y - _mouseY);
      mouseMove(mousePosition().x, mousePosition().y);
      vec3 target = vec3(_mouseX, _mouseY, 0);
      setColor(vec3(1, 0, 0));
      drawSphere(target, 15);

      for (float i = 0; i < 20; i++)
      {
         // time for interpolation
         t_x = i * x / width() / 10;
         t_x = glm::clamp(t_x, 0.0f, 1.0f);

         // interpolate colors
         vec3 c_x0 = c_nw * (1 - t_x) + c_ne * t_x;
         vec3 c_x1 = c_sw * (1 - t_x) + c_se * t_x;

         for (float j = 0; j < 20; j++)
         {
            // time for interpolation
            t_y = j * y / height() / 10;
            t_y = glm::clamp(t_y, 0.0f, 1.0f);

            // level 2 LERP
            vec3 c = c_x0 * (1 - t_y) + c_x1 * t_y;

            // position of the cuboids
            x = i * width() / 20 + size / 2;
            y = j * height() / 20 + size / 2;
            vec3 pos = vec3(x, y, 0);
            setColor(c);

            vec3 diff = target - pos;
            theta = atan2(diff.y, diff.x);

            push();
            translate(vec3(x, y, 0));
            rotate(theta, vec3(0, 0, 1));
            drawCube(vec3(0), vec3(size, 1, 0));
            pop();
         }
      }
   }
      void mouseMove(int x, int y)
      {
         _mouseX = x;
         _mouseY = height() - y;
      }

   private:
      vec3 c_nw;
      vec3 c_ne;
      vec3 c_sw;
      vec3 c_se;
      float x;
      float y;
      float t;
      float t_x;
      float t_y;
      int _mouseX;
      int _mouseY;
      float theta;
      float thetaRate;
      vec3 mousePos;

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
              vec3(196, 215, 113) / 255.0f,
              vec3(41, 237, 216) / 255.0f};
   };

   int main(int argc, char **argv)
   {
      Unique viewer;
      viewer.run();
      return 0;
   }
