#include <random>
#include <functional>
#include "atkui/framework.h"
#include "atk/toolkit.h"
#include "agl/renderer.h"
#include "devil.h"

using namespace atk;
using namespace glm;
using namespace std;

class Thriller : public atkui::Framework
{
public:
   Thriller() : atkui::Framework(atkui::Perspective) {}
   virtual ~Thriller() {}

   virtual void setup() {
      BVHReader reader;
      reader.load("../motions/Warrok/WarrokThriller.bvh", _skeleton, _motion);

      vector<vec3> positions; 

      int x = -200; 
      int y = 0; 
      int z = -450; 

      for (int i = 0; i < 3; i++) {
         z += 200; 
         x = 0;
         for (int j = 0; j < 4; j++) {
            x += 150; 
            positions.push_back(vec3(x, y, z));
         }
      }

      for (int i = 0; i < 12; i++) {
         vec3 color = agl::randomUnitVector()/5.0f;
         float size = random * (1.2f - 0.4f) + 0.4f;
         _devil = Devil(positions[i], color, size);
         devilList.push_back(_devil);
      }
   }

   virtual void scene() {
      if (!_paused) _motion.update(_skeleton, elapsedTime());
      
      for (int i = 0; i < devilList.size(); i++) {
         devilList[i].draw(_skeleton, *this);
      }
   }

   virtual void keyUp(int key, int mods) {
      if (key == 'P') _paused = !_paused;
   }

protected:
   Motion _motion;
   Skeleton _skeleton;
   bool _paused = false;
   Devil _devil;
   vector<Devil> devilList; 
};

int main(int argc, char** argv) {
   Thriller viewer;
   viewer.run();
}

