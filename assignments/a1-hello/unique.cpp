#include "atkui/framework.h"

using namespace glm;

class Unique : public atkui::Framework {
 public:
  Unique() : atkui::Framework(atkui::Orthographic) {
  }

   virtual void setup() {
      thetaP = 0.0;
      thetaRate = 1.8;
      thetaBody = 0.0;
      thetaBodyRate = 1.0;
   }

   virtual void scene() {    
      createFirstObject();
      createThirdObject();

      // drawSphere(vec3(0.5 * width(), height(), 0), 300);
      // drawSphere(vec3(0, 0.5 * height(), 0), 300);
   }

   virtual void createFirstObject() {
      setColor(vec3(0, 1, 1));

      // bottom object 
      thetaBody += thetaBodyRate * dt();
      float ax = 0.5 * width();
      float ay = 60.0f * sin(thetaBody);
      drawSphere(vec3(ax, ay, 0), 300);

      // draw two spheres for the eyes
      setColor(vec3(1,1,1));
      double x1 = width() * 0.40;
      double y1 = 60.0f * sin(thetaBody) + 30;
      double r1 = 100; 
      drawSphere(vec3(x1,y1,150), r1);
      
      double x2 = width() * 0.60;
      double y2 = 60.0f * sin(thetaBody) + 30;
      double r2 = 100; 
      drawSphere(vec3(x2,y2,150), r2);

      // draw the pupils
      thetaP += thetaRate * dt();
      float px1 = 20.0f * sin(thetaP) + 0.4 * width();
      float py1 = 60.0f * sin(thetaBody) + 30;
      setColor(vec3(0, 0, 0));
      drawSphere(vec3(px1, py1, 200), 50);

      float px2 = 20.0f * sin(thetaP) + 0.6 * width();
      float py2 = 60.0f * sin(thetaBody) + 30;
      setColor(vec3(0, 0, 0));
      drawSphere(vec3(px2, py2, 200), 50);
   }     

   virtual void createThirdObject() {
      setColor(vec3(255,150,197)/255.0f);

      // top object 
      thetaBody += thetaBodyRate * dt();
      float ax = 0.5 * width();
      float ay = 60.0f * sin(thetaBody) + height();
      drawSphere(vec3(ax, ay, 0), 300);

      // draw two spheres for the eyes
      setColor(vec3(1,1,1));
      double x1 = width() * 0.40;
      double y1 = 60.0f * sin(thetaBody) + height() - 30;
      double r1 = 100; 
      drawSphere(vec3(x1,y1,150), r1);
      
      double x2 = width() * 0.60;
      double y2 = 60.0f * sin(thetaBody) + height() - 30;
      double r2 = 100; 
      drawSphere(vec3(x2,y2,150), r2);

      // draw the pupils
      thetaP += thetaRate * dt();
      float px1 = 20.0f * sin(-thetaP) + 0.4 * width();
      float py1 = 60.0f * sin(thetaBody) + height() - 30;
      setColor(vec3(0, 0, 0));
      drawSphere(vec3(px1, py1, 200), 50);

      float px2 = 20.0f * sin(-thetaP) + 0.6 * width();
      float py2 = 60.0f * sin(thetaBody) + height() - 30;
      setColor(vec3(0, 0, 0));
      drawSphere(vec3(px2, py2, 200), 50);
   }

   private:
      float thetaP;
      float thetaRate;
      float thetaBody; 
      float thetaBodyRate;
};

int main(int argc, char** argv) {
  Unique viewer;
  viewer.run();
  return 0;
}

