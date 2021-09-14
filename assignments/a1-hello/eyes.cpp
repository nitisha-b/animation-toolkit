#include "atkui/framework.h"

using namespace glm;
class Eyes : public atkui::Framework
{
  public:
    Eyes() : atkui::Framework(atkui::Orthographic) {
    }

    virtual void setup() {
      theta = 0.0;
      thetaRate = 0.6;
    }

    virtual void scene() {
      // draw two spheres for the eyes
      setColor(vec3(1,1,1));
      double x1 = width() * 0.30;
      double y1 = height() * 0.5;
      double r1 = 150; 
      drawSphere(vec3(x1,y1,0), r1);
      
      double x2 = width() * 0.70;
      double y2 = height() * 0.5;
      double r2 = 150; 
      drawSphere(vec3(x2,y2,0), r2);

      // draw the pupils
      theta += thetaRate * dt();
      // float px1 = 90.0f * sin(theta) + 0.3 * width();
      float px1 = 55.0f * sin(elapsedTime()) + 0.3 * width();
      float py1 = 0.5 * width();
      setColor(vec3(0, 0, 0));
      drawSphere(vec3(px1, py1, 80), 35);

      // float px2 = 90.0f * sin(theta) + 0.7 * width();
      float px2 = 55.0f * sin(elapsedTime()) + 0.7 * width();
      float py2 = 0.5 * width();
      setColor(vec3(0, 0, 0));
      drawSphere(vec3(px2, py2, 80), 35);
    }
  
  private:
    float theta;
    float thetaRate;
};

int main(int argc, char** argv) {
  Eyes viewer;
  viewer.run();
  return 0;
}
