#include "atk/toolkit.h"
#include "atkui/framework.h"
#include "atkui/skeleton_drawer.h"
#include <algorithm>
#include <string>

using namespace glm;
using namespace atk;
using namespace atkui;

class Unique : public atkui::Framework {
public:
   Unique() : atkui::Framework(atkui::Perspective) {}
   virtual ~Unique() {}

   void setup() {
      BVHReader reader;
      reader.load("../motions/Beta/walking.bvh", _skeleton, _original);

      _zombieFreeze = ComputeArmFreeze(_original);
      _zombieOffset = ComputeArmOffset(_original);
   }

   Motion ComputeArmOffset(const Motion& motion) {
      quat leftLocalRot = eulerAngleRO(XYZ, radians(vec3(-53, -88, -33)));
      quat rightLocalRot = eulerAngleRO(XYZ, radians(vec3(14, 88, -33)));
      quat elbowLocalRot = eulerAngleRO(XYZ, radians(vec3(0, 23, 0)));
      quat bodyLocalRot = eulerAngleRO(XYZ, radians(vec3(0, 0, 50)));

      Joint* leftArm = _skeleton.getByName("Beta:LeftArm");
      Joint* rightArm = _skeleton.getByName("Beta:RightArm");

      Joint* leftElbow = _skeleton.getByName("Beta:LeftForeArm");
      Joint* rightElbow = _skeleton.getByName("Beta:RightForeArm");

      Joint* spine = _skeleton.getByName("Beta:Spine");

      Motion result;
      result.setFramerate(motion.getFramerate());

      for (int i = 0; i < motion.getNumKeys(); i++) {
         Pose newPose = motion.getKey(i);
         newPose.jointRots[leftArm->getID()] *= leftLocalRot * inverse(leftArm->getLocalRotation());
         newPose.jointRots[rightArm->getID()] *= rightLocalRot * inverse(rightArm->getLocalRotation());
         newPose.jointRots[leftElbow->getID()] *= elbowLocalRot * inverse(leftElbow->getLocalRotation());
         newPose.jointRots[rightElbow->getID()] *= elbowLocalRot * inverse(rightElbow->getLocalRotation());

         newPose.jointRots[spine->getID()] *= bodyLocalRot * inverse(spine->getGlobalRotation());
         // spine->setLocalRotation(newPose.jointRots[spine->getID()] * bodyLocalRot * inverse(spine->getLocalRotation()));
         result.appendKey(newPose);
      }
     
      return result;
   }

   Motion ComputeArmFreeze(const Motion& motion) {
      quat leftRot = eulerAngleRO(XYZ, radians(vec3(-53, -88, -33)));
      quat rightRot = eulerAngleRO(XYZ, radians(vec3(14, 88, -33)));
      quat elbowRot = eulerAngleRO(XYZ, radians(vec3(0, 23, 0)));

      Joint* leftArm = _skeleton.getByName("Beta:LeftArm");
      Joint* rightArm = _skeleton.getByName("Beta:RightArm");

      Joint* leftElbow = _skeleton.getByName("Beta:LeftForeArm");
      Joint* rightElbow = _skeleton.getByName("Beta:RightForeArm");

      Motion result;
      result.setFramerate(motion.getFramerate());

      for (int i = 0; i < motion.getNumKeys(); i++) {
         Pose newPose = motion.getKey(i);
         newPose.jointRots[leftArm->getID()] = leftRot;
         newPose.jointRots[rightArm->getID()] = rightRot;
         newPose.jointRots[leftElbow->getID()] = elbowRot;
         newPose.jointRots[rightElbow->getID()] = elbowRot;
         result.appendKey(newPose);
      }
      return result;
   }

   

   void update() {
      double t =  elapsedTime() * 0.5;
         _zombieOffset.update(_skeleton, t);
         drawText("Joint edit type: offset", 10, 15);
   }

   void scene() {  
      update();
      _drawer.draw(_skeleton, *this);
   }

   void keyUp(int key, int mods) {
      if (key == '1') {
          _currentMotion = 1;
      } else if (key == '2') {
          _currentMotion = 2;
      } else if (key == '0') {
          _currentMotion = 0;
      }
   }

   SkeletonDrawer _drawer;
   Skeleton _skeleton;
   Motion _original;
   Motion _zombieFreeze;
   Motion _zombieOffset;
   int _currentMotion = 0;
};

int main(int argc, char** argv) {
   Unique viewer;
   viewer.run();
   return 0;
}

