#include "atkui/framework.h"
#include "atk/toolkit.h"
using namespace atk;
using glm::vec3;
using glm::quat;
// using namespace atkmath;

class Tentacle : public atkui::Framework {
public:
   Tentacle() : atkui::Framework(atkui::Perspective) {}
   virtual ~Tentacle() {}

   virtual void setup() {
      lookAt(vec3(200), vec3(0));

      Joint* root  = new Joint("root");
      root->setLocalTranslation(vec3(0,0,0));
      _tentacle.addJoint(root);

      Joint* joint1  = new Joint("joint1");
      joint1->setLocalTranslation(vec3(0,50,0));
      _tentacle.addJoint(joint1, root);

      // todo: add more joints
      Joint* joint2  = new Joint("joint2");
      joint2->setLocalTranslation(vec3(0,50,0));
      _tentacle.addJoint(joint2, joint1);

      Joint* joint3  = new Joint("joint3");
      joint3->setLocalTranslation(vec3(0,50,0));
      _tentacle.addJoint(joint3, joint2);

      Joint* joint4  = new Joint("joint4");
      joint4->setLocalTranslation(vec3(0,50,0));
      _tentacle.addJoint(joint4, joint3);

      _tentacle.fk(); // compute local2global transforms
   }

   virtual void scene()
   {
      // todo animate joints
      // hint: use glm::angleAxis(...) to compute quaternions for each joint
      _tentacle.fk(); // computes local2global transforms
      setColor(vec3(0,1,0));

      // todo: loop over all joints and draw
      // draw the root separately because it does not have a parent
      // Joint* root = _tentacle.getByID(0);
      // vec3 rootPos = root->getGlobalTranslation();
      // drawEllipsoid(vec3(0), rootPos, 7);

      for (int i = 1; i < _tentacle.getNumJoints(); i++) {
         Joint* child = _tentacle.getByID(i);
         Joint* parent = child->getParent();
         vec3 globalParentPos = parent->getGlobalTranslation();
         vec3 globalPos = child->getGlobalTranslation();
         quat animate = glm::angleAxis(sin(elapsedTime()+i), vec3(0,0,1));
         child->setLocalRotation(animate);
         drawEllipsoid(globalParentPos, globalPos, 7);
      }
   }

protected:
   Skeleton _tentacle;
};

int main(int argc, char** argv)
{
   Tentacle viewer;
   viewer.run();
} 

