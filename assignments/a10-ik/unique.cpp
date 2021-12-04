#include "atk/toolkit.h"
#include "atkui/framework.h"
#include "cyclops.h"
#include "ik_controller.h"
#include <algorithm>
#include <string>

using namespace atk;
using namespace glm;
using namespace std;

class Unique : public atkui::Framework
{
public:
   Unique() : atkui::Framework(atkui::Perspective) {}
   virtual ~Unique() {}

   void setup()
   {
      BVHReader reader;
      reader.load("../motions/Beta/idle.bvh", _skeleton, _motion);
      _drawer.color = vec3(1,0,0);
      thetaRate = 2.0f;
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

      vec3 adj1 = vec3(_lhandTarget.x - 5, _lhandTarget.y, _lhandTarget.z);
      vec3 adj2 = vec3(_rhandTarget.x - 10, _rhandTarget.y, _rhandTarget.z);
      ik.solveIKCCD(_skeleton, lhID, adj1, chain1, 0.0001, 8, 0.1);
      ik.solveIKCCD(_skeleton, rhID, adj2, chain2, 0.0001, 8, 0.1);

      _skeleton.fk();
   }

   void scene()
   {  
      update();
      _drawer.draw(_skeleton, *this);
      theta += thetaRate * dt();
      float r = 30.0f;

      _lhandTarget.x = 40.0;
      _lhandTarget.y = r * sin(theta) + 120.0;
      _lhandTarget.z = 25.0;

      _rhandTarget.x = -5.0;
      _rhandTarget.y = r * sin(theta) + 120.0;
      _rhandTarget.z = 25.0;


      setColor(vec3(0.7,0,1));
      // drawLine(_lhandTarget, _rhandTarget);
   
      push();
      rotate(1.57, vec3(0,1,0));
      translate(vec3(-80, 0, 30));
      drawCylinder(_lhandTarget, 20);
      pop();
      
      push();
      rotate(1.57, vec3(0,1,0));
      translate(vec3(-35, 0, -60));
      // scale(vec3(10, 5, 2));
      drawCylinder(_rhandTarget, 20);
      pop();
      
      for (float p = _rhandTarget.x; p <= _lhandTarget.x+30; p += 1.0) {
         
         push();
         // rotate(1.57, vec3(0,1,0));
         translate(vec3(-75, 0, 0));
         // scale(vec3(40, 0, 0));
         // drawCylinder(_lhandTarget, 6);
         drawSphere(vec3(p+50, _lhandTarget.y, _lhandTarget.z+15), 5);
         pop();
      }
      
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
   Unique viewer;
   viewer.run();
   return 0;
}

