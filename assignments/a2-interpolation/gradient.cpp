#include <iostream>
#include "atkui/framework.h"
using namespace glm;

class Gradient : public atkui::Framework {
 public:
  Gradient() : atkui::Framework(atkui::Orthographic) {
  }

  // setWindowSize(400,400);

  virtual void setup() {
    c_nw = vec3(1,1,0);
    c_ne = vec3(0,1,1);
    c_sw = vec3(1,0,0);
    c_se = vec3(1,0,1);
    t = 0;
    x = 0; 
    y = 0;
    t_x = 0; 
    t_y = 0;
  }

  virtual void scene() {
    float size = height()/10;

    for (float i = 0; i < 10; i++) {
      t_x = i * x/width()/10;
      t_x = glm::clamp(t_x, 0.0f, 1.0f);

      vec3 c_x0 = c_nw * (1-t_x) + c_ne * t_x;
      vec3 c_x1 = c_sw * (1-t_x) + c_se * t_x;

      for (float j = 0; j < 10; j++) {
        t_y = j * y/height()/10;
        t_y = glm::clamp(t_y, 0.0f, 1.0f);

        vec3 c = c_x0 * (1-t_y) + c_x1 * t_y;

        x = i * width()/10 + size/2;
        y = j * height()/10 + size/2; 
        setColor(c);
        drawCube(vec3(x, y, 0), vec3(size, size, 0));
      }
    }
  }

  vec3 c_nw; 
  vec3 c_ne;
  vec3 c_sw;
  vec3 c_se;
  float x; 
  float y;
  float t;
  float t_x;
  float t_y;
};

int main(int argc, char **argv) {
  Gradient viewer;
  viewer.run();
}
