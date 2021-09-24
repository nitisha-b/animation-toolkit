#include <iostream>
#include "atkui/framework.h"
using namespace glm;

class DrawCubic : public atkui::Framework
{
 public:
  DrawCubic() : atkui::Framework(atkui::Orthographic, 400, 400) {
  }

  virtual void scene()
  {
    setColor(vec3(0,0,1));
    drawSphere(B0, 10);
    drawSphere(B3, 10);

    setColor(vec3(1,1,0));
    drawSphere(B1, 10);
    drawSphere(B2, 10);

    // draw bernstein
    if (keyPressed1){
      setColor(vec3(0,0,1));
      for (float i = 0.0f; i <= 1.0f; i = i+0.005f){
        float term1 = (std::pow((1-i),3) );
        float term2 = (3*i* std::pow((1-i),2) );
        float term3 = (3*std::pow(i,2)*(1-i) );
        float term4 = (std::pow(i,3) );
        p = term1 * B0 + term2 * B1 + term3 * B2 + term4 * B3;
        // p = term1 + term2 + term3 + term4;
        drawSphere(p, 4);
      }
    }
    
    // draw Casteljau
    if(keyPressed2){
      setColor(vec3(1,1,0));
      for (float i = 0.0f; i <= 1.0f; i = i+0.005f) {
        // level 1
        vec3 x_0 = B0 * (1-i) + B1 * i;
        vec3 x_1 = B1 * (1-i) + B2 * i;
        vec3 x_2 = B2 * (1-i) + B3 * i;

        // level 2
        vec3 y_1 = x_0 * (1-i) + x_1 * i;
        vec3 y_2 = x_1 * (1-i) + x_2 * i;

        // level 3
        vec3 z_1 = y_1 * (1-i) + y_2 * i;
        drawSphere(z_1, 4);
      }
    }
  }

  void keyUp(int key, int mod) {
    if (key == GLFW_KEY_1) {
      // draw Bernstein
      keyPressed2 = false;
      keyPressed1 = true;
    }
    else if (key == GLFW_KEY_2) {
      // draw Casteljau
      keyPressed1 = false;
      keyPressed2 = true;
    }
  }

 private:
  vec3 B0 = vec3(100,  50, 0);
  vec3 B1 = vec3(150, 200, 0);
  vec3 B2 = vec3(250, 100, 0);
  vec3 B3 = vec3(300, 300, 0);
  vec3 p;
  bool keyPressed1;
  bool keyPressed2;
};

int main(int argc, char **argv) {
  DrawCubic viewer;
  viewer.run();
}
