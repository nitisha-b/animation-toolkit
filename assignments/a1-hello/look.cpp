#include "atkui/framework.h"

using namespace glm;

class Look : public atkui::Framework {
 public:
  Look() : atkui::Framework(atkui::Orthographic) {
  }

  virtual void setup() {
    _mouseX = width() * 0.5;
    _mouseY = height() * 0.5;
    thetaLeft = 0.0;
    thetaRight = 0.0;
    thetaRate = 0.6;
    mousePos = vec3(_mouseX, _mouseY, 0);
  }

  virtual void scene() {
    mousePos = vec3(mousePosition().x, mousePosition().y, 0);
    mouseMotion(mousePosition().x, mousePosition().y, mousePosition().x - _mouseX, mousePosition().y - _mouseY);
    mouseMove(mousePosition().x, mousePosition().y);
    vec3 target = vec3(_mouseX, _mouseY, 0);
    setColor(vec3(1,0,0));
    drawSphere(target, 15);

  // draw two spheres for the eyes
    setColor(vec3(1,1,1));
    float x1 = width() * 0.30;
    float y1 = height() * 0.5;
    float r1 = 150; 
    vec3 centerL = vec3(x1,y1,0);
    drawSphere(vec3(x1,y1,0), r1);
    
    float x2 = width() * 0.70;
    float y2 = height() * 0.5;
    float r2 = 150; 
    vec3 centerR = vec3(x2,y2,0);
    drawSphere(vec3(x2,y2,0), r2);

    // left pupil
    float r = 30;
    vec3 diffL = mousePos - centerL;
    thetaLeft = atan2(diffL.y, diffL.x);
    float px1 = r * cos(thetaLeft) + 0.3 * width();
    float py1 = r * sin(-thetaLeft) + 0.5 * height();
    setColor(vec3(0, 0, 0));
    drawSphere(vec3(px1, py1, 80), 35);
    
    // right pupil 
    vec3 diffR = mousePos - centerR;
    thetaRight = atan2(diffR.y, diffR.x);
    float px2 = r * cos(thetaRight) + 0.7 * width();
    float py2 = r * sin(-thetaRight) + 0.5 * height();
    setColor(vec3(0, 0, 0));
    drawSphere(vec3(px2, py2, 80), 35);
  }

  void mouseMove(int x, int y) {
    _mouseX = x;
    _mouseY = height() - y;
  }

 private:
  int _mouseX;
  int _mouseY;
  float thetaLeft;
  float thetaRight;
  float thetaRate;
  vec3 mousePos;
};

int main(int argc, char** argv) {
  Look viewer;
  viewer.run();
  return 0;
}
