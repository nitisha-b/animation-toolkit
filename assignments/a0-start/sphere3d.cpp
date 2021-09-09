#include "atkui/framework.h"

using glm::vec3;

class Sphere3D : public atkui::Framework {
 public:
  Sphere3D() : atkui::Framework(atkui::Perspective) {
  }
  vec3 currentPos;
  vec3 velocity;

  virtual void setup(){
    currentPos = vec3(0,0,0);
  }

  virtual void scene() {
    // colors are RGB triplets in range [0,1]
    setColor(vec3(0,1,0));

    // draw a sphere at center of the world
    float radius = 70.0;
    drawSphere(currentPos, radius);
  }

  void keyUp(int key, int mods){
    // Reset to center
    if (key == GLFW_KEY_R) {
      currentPos = vec3(0,0,0);
    }

    // Move in a random direction
    if (key == GLFW_KEY_SPACE){
      velocity = 500.0f * agl::randomUnitVector();
      currentPos = currentPos + velocity * dt();
    }
  }
};

int main(int argc, char** argv)
{
  Sphere3D viewer;
  viewer.run();
  return 0;
}
