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
      reader.load("../motions/Beta/samba_dancing.bvh", skeleton, motion);
      motion.update(skeleton, 0);

      BVHReader reader2;
      reader2.load("../motions/Beta/gangnam_style.bvh", skeleton2, motion2);
      motion2.update(skeleton2, 0);

      BVHReader reader3;
      reader3.load("../motions/Beta/back_flip_to_uppercut.bvh", skeleton3, motion3);
      motion3.update(skeleton3, 0);
   }

   virtual void scene()
   {
      time += dt();
      motion.update(skeleton, time);
      motion2.update(skeleton2, time);
      motion3.update(skeleton3, time);

      for (int i = 0; i < skeleton.getNumJoints(); i++) {
         Joint* joint = skeleton.getByID(i);
         if (joint->getParent() == 0) continue;

         // samba 1
         vec3 p1 = joint->getGlobalTranslation();
         vec3 p2 = joint->getParent()->getGlobalTranslation();
         setColor(vec3(0,0.4,0.8));
         drawEllipsoid(p1, p2, 12);

         // samba 2
         vec3 distance = vec3(0,0,-120);
         vec3 p3 = joint->getGlobalTranslation() + distance;
         vec3 p4 = joint->getParent()->getGlobalTranslation() + distance;
         
         push();
         setColor(vec3(0.3,0,0.8));
         rotate(M_PI, vec3(0,1,0));
         drawEllipsoid(p3, p4, 7);
         pop();

         // samba second pair 
         vec3 pos1 = vec3(150, 0, 300);
         push();
         setColor(vec3(0.7,0,0.2));
         rotate(M_PI, vec3(0,1,0));
         drawEllipsoid(p1+pos1, p2+pos1, 9);
         pop();

         vec3 pos2 = vec3(-150, 0, -450);
         push();
         setColor(vec3(0.3,0.7,0.4));
         // rotate(M_PI, vec3(0,1,0));
         drawEllipsoid(p1+pos2, p2+pos2, 11);
         pop();


         // gangnam style
         Joint* joint2 = skeleton2.getByID(i);
         if (joint2->getParent() == 0) continue;

         vec3 g1 = joint2->getGlobalTranslation();
         vec3 g2 = joint2->getParent()->getGlobalTranslation();

         vec3 pos3 = vec3(200, 0, -450);
         push();
         setColor(vec3(0.1,0,0.9));
         // rotate(M_PI, vec3(0,1,0));
         drawSphere(g1+pos3, 45);
         pop();

         vec3 pos4 = vec3(200, 0, -300);
         push();
         setColor(vec3(0.8,0,0.8));
         rotate(M_PI, vec3(0,1,0));
         drawEllipsoid(g1+pos4, g2+pos4, 15);
         pop();

         Joint* joint3 = skeleton3.getByID(i);
         if (joint3->getParent() == 0) continue;

         vec3 b1 = joint3->getGlobalTranslation();
         vec3 b2 = joint3->getParent()->getGlobalTranslation();
         
         vec3 pos5 = vec3(300, 0, 300);
         push();
         setColor(vec3(0,0.8,0.8));
         // rotate(M_PI, vec3(0,1,0));
         drawEllipsoid(b1+pos5, b2+pos5, 10);
         pop();

      }
   }

   private:
      Skeleton skeleton;
      Motion motion;

      Skeleton skeleton2;
      Motion motion2;

      Skeleton skeleton3;
      Motion motion3;

      // float timeScale = 1.0f;
      float time = 0;
      
};

int main(int argc, char **argv)
{
   Unique viewer;
   viewer.run();
}
