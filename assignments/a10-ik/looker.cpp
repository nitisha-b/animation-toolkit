#include "atk/toolkit.h"
#include "atkui/framework.h"
#include "cyclops.h"
#include <algorithm>
#include <string>

using namespace atk;
using namespace glm;
using namespace std;

class ALooker : public atkui::Framework {
public:
   ALooker() : atkui::Framework(atkui::Perspective) {}
   virtual ~ALooker() {}

   void setup() {
      Motion motion;
      BVHReader reader;
      reader.load("../motions/Beta/idle.bvh", _skeleton, motion);
      motion.update(_skeleton, 0);

      _drawer.color = vec3(1,0,0);
      _head = _skeleton.getByName("Beta:Head");
   }

   void reset(Joint* head) {
      head->setLocalRotation(IdentityQ);
      head->fk();
   }

   void lookAtTarget(Joint* head, const vec3& target) {
      // vec3 r = vec3(0,0,1) * 300.0f;
      // vec3 e = target - (head->getGlobalTranslation() + r);
      // float phi = atan2(glm::length(glm::cross(r,e)), (glm::dot(r,e) + glm::dot(r,r)));
      // std::cout << "phi " << phi << std::endl;
      // vec3 axis = glm::cross(r,e) / glm::length(glm::cross(r,e));
      // head->setLocalRotation(angleAxis(phi,axis));

      //quat rot = angleAxis(phi, axis);
      // head->setLocalRotation(rot * head->getLocalRotation());

      vec3 z = target - head->getGlobalTranslation();
      vec3 x = glm::cross(vec3(0,1,0), z);
      vec3 y = glm::cross(z,x);
      glm::mat3 R_LtoG = glm::mat3(normalize(x), normalize(y), normalize(z));
      quat rot = quat(R_LtoG);
      head->setLocalRotation(inverse(head->getParent()->getGlobalRotation()) * rot * head->getLocalRotation());
      head->fk();
   }

   void scene() {  
      float r = 100;
      float angle = elapsedTime();
      _target = vec3(r * cos(angle), r * sin(angle) + r, 150);

      reset(_head);
      lookAtTarget(_head, _target);
      _drawer.draw(_skeleton, *this);

      vec3 globalHeadPos = _head->getGlobalTranslation();
      vec3 globalForward = _head->getGlobalRotation() * vec3(0,0,1);

      setColor(vec3(0,0,1));
      drawLine(globalHeadPos, globalHeadPos + 200.0f*globalForward);
      drawSphere(_target, 5);
   }

   Cyclops _drawer;
   Skeleton _skeleton;
   Joint* _head;
   vec3 _target;
};

int main(int argc, char** argv) {
   ALooker viewer;
   viewer.run();
   return 0;
}

