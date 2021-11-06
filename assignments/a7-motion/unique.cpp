#include <iostream>
#include "atkui/framework.h"
#include "atk/toolkit.h"

using namespace glm;
using namespace atk;
using namespace std;

class Unique : public atkui::Framework
{
public:
   Unique() : atkui::Framework(atkui::Perspective) {}
   virtual ~Unique() {}

   virtual void setup()
   {
      BVHReader reader;
      reader.load("../motions/Beta/jump.bvh", skeleton, motion);
      motion.update(skeleton, 0);
   }

   virtual void scene()
   {
      time += dt();
      motion.update(skeleton, time);

      setColor(vec3(0,0,0.8));
      for (int i = 0; i < skeleton.getNumJoints(); i++) {
         Joint* joint = skeleton.getByID(i);
         if (joint->getParent() == 0) continue;

         vec3 p1 = joint->getGlobalTranslation();
         vec3 p2 = joint->getParent()->getGlobalTranslation();
         drawEllipsoid(p1, p2, 5);
      }
   }

   private:
      Skeleton skeleton;
      Motion motion;

      // float timeScale = 1.0f;
      float time = 0;
};

int main(int argc, char **argv)
{
   Unique viewer;
   viewer.run();
}
