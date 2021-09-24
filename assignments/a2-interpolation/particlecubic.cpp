#include "atkui/framework.h"
using namespace glm;

class ParticleCubic : public atkui::Framework {
 public:
  ParticleCubic() : atkui::Framework(atkui::Orthographic) {
  }

  void setup() {
    sphPos = vec3(100,  50, 0);
  }

  void scene() {
    // draw the path
    setColor(vec3(1,1,0));
    for (float i = 0.0f; i <= 1.0f; i = i+0.005f){
      float term1 = (std::pow((1-i),3) );
      float term2 = (3*i* std::pow((1-i),2) );
      float term3 = (3*std::pow(i,2)*(1-i) );
      float term4 = (std::pow(i,3) );
      line = term1 * B0 + term2 * B1 + term3 * B2 + term4 * B3;
      drawSphere(line, 3);
    }
    
    // draw sphere
    setColor(vec3(1));
    float j = fmod(elapsedTime()/t,1);
    float term1 = std::pow((1-j),3);
    float term2 = 3*j* std::pow((1-j),2);
    float term3 = 3*std::pow(j,2)*(1-j);
    float term4 = std::pow(j,3);
    sphPos = term1 * B0 + term2 * B1 + term3 * B2 + term4 * B3;
    drawSphere(sphPos, 10);
  }

  vec3 B0 = vec3(100,  50, 0);
  vec3 B1 = vec3(150, 200, 0);
  vec3 B2 = vec3(250, 100, 0);
  vec3 B3 = vec3(300, 300, 0);  
  float t = 5.0f; // complete in 5 seconds
  vec3 line; 
  vec3 sphPos;
};

int main(int argc, char** argv) {
  ParticleCubic viewer;
  viewer.run();
}

