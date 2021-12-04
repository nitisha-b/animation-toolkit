#include "atk/toolkit.h"
#include "atkui/framework.h"
#include "cyclops.h"
#include "ik_controller.h"
#include <algorithm>
#include <string>

using namespace atk;
using namespace glm;
using namespace std;

class ADancer : public atkui::Framework
{
public:
   ADancer() : atkui::Framework(atkui::Perspective) {}
   virtual ~ADancer() {}

   void setup()
   {
      BVHReader reader;
      reader.load("../motions/Beta/idle.bvh", _skeleton, _motion);
      _drawer.color = vec3(1,0,0);
      thetaRate = 3.0f;
      theta = 0.0;
   }

   void update()
   {
      _motion.update(_skeleton, elapsedTime());

      IKController ik;
      // TODO: Your code here
      int lhID = _skeleton.getByName("Beta:LeftHand")->getID();
      int rhID = _skeleton.getByName("Beta:RightHand")->getID();

      vector<Joint*> chain1; 
      chain1.push_back(_skeleton.getByName("Beta:LeftHand"));
      chain1.push_back(_skeleton.getByName("Beta:LeftArm"));
      chain1.push_back(_skeleton.getByName("Beta:LeftForeArm"));
      chain1.push_back(_skeleton.getByName("Beta:LeftShoulder"));

      vector<Joint*> chain2; 
      chain2.push_back(_skeleton.getByName("Beta:RightHand"));
      chain2.push_back(_skeleton.getByName("Beta:RightArm"));
      chain2.push_back(_skeleton.getByName("Beta:RightForeArm"));
      chain2.push_back(_skeleton.getByName("Beta:RightShoulder"));

      ik.solveIKCCD(_skeleton, lhID, _lhandTarget, chain1, 0.0001, 8, 0.1);
      ik.solveIKCCD(_skeleton, rhID, _rhandTarget, chain2, 0.0001, 8, 0.1);

      _skeleton.fk();
   }

   void scene()
   {  
      update();
      _drawer.draw(_skeleton, *this);
      theta += thetaRate * dt();
      float r = 35.0f;

      _lhandTarget.x = 50.0;
      _lhandTarget.y = r * sin(theta) + 110.0;
      _lhandTarget.z = 25.0;

      _rhandTarget.x = -50.0;
      _rhandTarget.y = r * -sin(theta) + 110.0;
      _rhandTarget.z = 25.0;


      setColor(vec3(0,0,1));
      drawSphere(_lhandTarget, 10);
      drawSphere(_rhandTarget, 10);
   }

protected:
   Cyclops _drawer;
   Skeleton _skeleton;
   Motion _motion;

   // Hand target positions
   vec3 _lhandTarget;
   vec3 _rhandTarget;

   float thetaRate; 
   float theta;
};

int main(int argc, char** argv)
{
   ADancer viewer;
   viewer.run();
   return 0;
}

