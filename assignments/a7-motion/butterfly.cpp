#include <iostream>
#include "atkui/framework.h"
#include "atk/toolkit.h"

using namespace glm;
using namespace atk;

class Butterfly : public atkui::Framework
{
public:
   Butterfly() : atkui::Framework(atkui::Perspective) {
   }

   void setup() {
      Joint* body = new Joint("Body");
      body->setLocalTranslation(vec3(1,2,1)*100.0f);
      body->setLocalRotation(glm::angleAxis(glm::radians<float>(45.0f), vec3(0,1,0)));
      skeleton.addJoint(body);

      Joint* lwing = new Joint("LWing");
      lwing->setLocalTranslation(vec3(0.1,0,0)*100.0f);
      // lwing->setLocalRotation(glm::angleAxis(glm::radians<float>(45.0f), vec3(0,1,0)));
      skeleton.addJoint(lwing, body);

      Joint* lowLWing = new Joint("lowLWing");
      lowLWing->setLocalTranslation(vec3(0.2,0,0)*100.0f);
      // lowLWing->setLocalRotation(glm::angleAxis(glm::radians<float>(45.0f), vec3(0,1,0)));
      skeleton.addJoint(lowLWing, body);

      Joint* rwing = new Joint("RWing");
      rwing->setLocalTranslation(vec3(-0.1,0,0)*100.0f);
      skeleton.addJoint(rwing, body);

      Joint* lowRWing = new Joint("lowRWing");
      lowRWing->setLocalTranslation(vec3(-0.2,0,0)*100.0f);
      skeleton.addJoint(lowRWing, body);

      skeleton.fk();
   }

   void scene() {
      Joint* body = skeleton.getByName("Body");
      // body->setLocalRotation(glm::angleAxis(sin(elapsedTime()/2), vec3(1,0,0)));

      Joint* lwing = skeleton.getByName("LWing");
      lwing->setLocalRotation(glm::angleAxis(sin(elapsedTime()*4), vec3(0,0,1)));
      
      Joint* lowLeftWing = skeleton.getByName("lowLWing");
      lowLeftWing->setLocalRotation(glm::angleAxis(sin(elapsedTime()*4), vec3(0,0,1)));

      Joint* rwing = skeleton.getByName("RWing");
      rwing->setLocalRotation(glm::angleAxis(-sin(elapsedTime()*4), vec3(0,0,1))); 

      Joint* lowRightWing = skeleton.getByName("lowRWing");
      lowRightWing->setLocalRotation(glm::angleAxis(-sin(elapsedTime()*4), vec3(0,0,1)));

      skeleton.fk();

      // attach geometry to skeleton 
      Transform B = body->getLocal2Global(); 
      Transform LT = lwing->getLocal2Global(); 
      Transform LLT = lowLeftWing->getLocal2Global(); 
      Transform RT = rwing->getLocal2Global();
      Transform LRT = lowRightWing->getLocal2Global(); 

      // draw body
      Transform bodyGeometry(
         glm::angleAxis(glm::pi<float>()*0.5f, vec3(1,0,0)), // rotation
         vec3(0), vec3(25, 200, 25)); // position, scale

      Transform lwingGeometry(
         eulerAngleRO(XYZ, vec3(0,-M_PI/4,0)),
         vec3(-70,0,40), 
         vec3(120,20,150));

      Transform lowLeftWingGeometry(
         eulerAngleRO(XYZ, vec3(0,-M_PI/4,0)),
         vec3(-70,0,-40), 
         vec3(120,20,80));

      Transform rwingGeometry(
         eulerAngleRO(XYZ, vec3(0,M_PI/4,0)),
         vec3(70,0,40), 
         vec3(120,20,150));
      
      Transform lowRightWingGeometry(
         eulerAngleRO(XYZ, vec3(0,M_PI/4,0)),
         vec3(70,0,-40), 
         vec3(120,20,80));

      // rotate(glm::pi<float>()*0.5f, vec3(M_PI/4,0,0));

      // display axes by pressing "d"
      if (showAxes){
         push();
            transform(B);

            setColor(vec3(1,0,0));
            drawEllipsoid(vec3(0,0,0),vec3(250,0,0),5);

            setColor(vec3(0,1,0));
            drawEllipsoid(vec3(0,0,0),vec3(0,250,0),5);
            
            setColor(vec3(0,0,1));
            drawEllipsoid(vec3(0,0,0),vec3(0,0,250),5);
         pop();
      }

      setColor(vec3(0.4, 0.4, 0.8));
      push();
      transform(B * bodyGeometry);
      drawSphere(vec3(0), 1);
      pop();

      setColor(vec3(0.0, 0.0, 0.7));
      push();
      // rotate(glm::pi<float>()*0.5f, vec3(M_PI/4,0,0));
      transform(LT * lwingGeometry);
      drawSphere(vec3(0), 1);
      pop();

      setColor(vec3(0.7, 0.7, 0.0));
      push();
      transform(LLT * lowLeftWingGeometry);
      drawSphere(vec3(0), 1);
      pop();

      setColor(vec3(0, 0.0, 0.7));
      push();
      transform(RT * rwingGeometry);
      drawSphere(vec3(0), 1);
      pop();

      setColor(vec3(0.7, 0.7, 0.0));
      push();
      transform(LRT * lowRightWingGeometry);
      drawSphere(vec3(0), 1);
      pop();
      
   }

   void keyUp(int key, int mods) {
      if (key == GLFW_KEY_D) {
         showAxes = !showAxes;
      }
   }

private:
   Skeleton skeleton;
   bool showAxes = false;
};


int main(int argc, char** argv) {
   Butterfly viewer;
   viewer.run();
}
