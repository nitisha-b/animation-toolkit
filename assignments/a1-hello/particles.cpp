#include "atkui/framework.h"

using namespace glm;
using namespace std;

class Particles : public atkui::Framework
{
 public:
  Particles() : atkui::Framework(atkui::Orthographic) {
  }

  virtual void setup() {
    for(int i = 0; i<150; i++){
      speed = 12.0f * agl::random (0.0, 10.0);
      vel = speed * vec3(2,2,0);
      
      // randomize color
      c = agl::randomUnitVector();

      pos = width() * agl::randomUnitVector();

      // take the absolute value of positions and set z to be 0 always
      if (pos.x < 0) { 
        pos.x = pos.x * -1;
      }
      if (pos.y < 0) {
        pos.y = pos.y * -1;
      }
      pos.z = 0;

      Particle p;
      p.velocity = vel; 
      p.color = c;
      p.position = pos;
      particles.push_back(p);
    }  
  }

  virtual void scene() {
    double radius = 10; 

    // draw all particles
    for(int i = 0; i<particles.size(); i++){
      Particle& p = particles[i];
      setColor(p.color);
      p.position = p.position + p.velocity * dt();

      // wrap positions of x and y
      if (p.position.x >= width()) {
        p.position.x = 0; 
      } 
      if (p.position.y >= height()){
        p.position.y = 0;
      }

      drawSphere(p.position, radius);
    }
  }

  // Particle object to store information about one particle
  struct Particle {
    vec3 position;
    vec3 color; 
    vec3 velocity; 
  };
  
  vec3 vel;
  float x0; 
  float y0;
  float speed;
  vec3 direction;
  vec3 c;
  vec3 pos;
  vector<Particle> particles; 
};

int main(int argc, char** argv) {
  Particles viewer;
  viewer.run();
  return 0;
}
