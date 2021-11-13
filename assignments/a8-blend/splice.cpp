#include "atk/toolkit.h"
#include "atkui/framework.h"
#include "atkui/skeleton_drawer.h"
#include <algorithm>
#include <string>

using namespace atk;
using namespace atkui;
using namespace glm;

class ASplice : public atkui::Framework
{
public:
   ASplice() : atkui::Framework(atkui::Perspective) {}
   virtual ~ASplice() {}

   void setup()
   {
      _alpha = 0;

      BVHReader reader;
      reader.load("../motions/Beta/walking.bvh", _skeleton, _lower);
      reader.load("../motions/Beta/gangnam_style.bvh", _skeleton, _upper);
      _splice = spliceUpperBody(_lower, _upper, _alpha);
   }

   Motion spliceUpperBody(const Motion& lower, const Motion& upper, float alpha)
   {
      Motion result = lower;
      result.setFramerate(lower.getFramerate());
      // todo: your code here

      Joint* spine = _skeleton.getByName("Beta:Spine1");
      int spineID = spine->getID();

      
      for (int i = 0; i < lower.getNumKeys(); i++) {
         Pose lowerPose = lower.getKey(i);
         Pose upperPose = upper.getKey(i+120);
         Pose lowerCopy = lowerPose;

         for (int j = 0; j < lowerPose.jointRots.size(); j++) {
            
            Joint* joint = _skeleton.getByID(j);

            if (isUpperBody(joint)) {

               // Pose newUpper = Pose::Lerp(upperPose, lowerPose, alpha);
               // Pose newUpper = Pose(glm::slerp(upperPose.jointRots[j], lowerPose.jointRots[j], alpha));

               lowerCopy.jointRots[j] = glm::slerp(upperPose.jointRots[j], lowerPose.jointRots[j], alpha);

               result.appendKey(lowerCopy);
            }
            // else {
            //    result.appendKey(lowerPose.jointRots[j]);
            // }
         }
      }

   //   result.appendKey(lower.getKey(0));
      return result;
   }

   bool isUpperBody(Joint* joint) {
      // check if joint is the hips
      if (joint->getID() == 0) {
         return false;
      }
      else if (joint->getName() == "Beta:Spine1") {
         return true;
      }
      else {
         return isUpperBody(joint->getParent());
      }
   }

   void scene()
   {  
      _splice.update(_skeleton, elapsedTime() * 0.5);
      SkeletonDrawer drawer;
      drawer.draw(_skeleton, *this);
      drawText("alpha: "+std::to_string(_alpha), 10, 15);
   }

   void keyUp(int key, int mods) 
   {
      if (key == GLFW_KEY_UP)
      {
         _alpha = std::min(_alpha+0.05, 1.0);
         _splice = spliceUpperBody(_lower, _upper, _alpha);
      }
      else if (key == GLFW_KEY_DOWN)
      {
         _alpha = std::max(_alpha-0.05, 0.0);
         _splice = spliceUpperBody(_lower, _upper, _alpha);
      }
   }

   Skeleton _skeleton;
   Motion _upper;
   Motion _lower;
   Motion _splice;
   float _alpha;
};

int main(int argc, char** argv)
{
   ASplice viewer;
   viewer.run();
   return 0;
}

