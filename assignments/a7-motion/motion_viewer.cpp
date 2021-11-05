#include <iostream>
#include "atkui/framework.h"
#include "atk/toolkit.h"

using namespace glm;
using namespace atk;
using namespace std;

class MotionViewer : public atkui::Framework
{
public:
   MotionViewer() : atkui::Framework(atkui::Perspective) {
   }

   void setup() {
      rightBracket = false;
      leftBracket = false;
      periodPressed = false; 
      commaPressed = false;  
   }

   void setFilename(string filename) {
      BVHReader reader;
      if (filename.empty() || filename == "") {
         reader.load("../motions/Beta/jump.bvh", skeleton, motion);
         motion.update(skeleton, 0);
      }
      else {
         reader.load(filename, skeleton, motion);
         motion.update(skeleton, 0);
      }
   }

   void scene() {
      if (!paused) {
         if (rightBracket || leftBracket) {
            time += timeScale;
         }
         // else if (leftBracket) {
         //    time 
         // }
         else {
            time += dt();
         } 
         motion.update(skeleton, time);
      }

      setColor(vec3(0,0,0.8));
      for (int i = 0; i < skeleton.getNumJoints(); i++) {
         Joint* joint = skeleton.getByID(i);
         if (joint->getParent() == 0) continue;

         vec3 p1 = joint->getGlobalTranslation();
         vec3 p2 = joint->getParent()->getGlobalTranslation();
         drawEllipsoid(p1, p2, 5);
      }

      // if (currentFrame >= motion.getNumKeys()) {
      //    currentFrame = 0; 
      // }
      // else if (!periodPressed || !commaPressed){
      //    currentFrame++;
      // }

      drawText(paused? "Paused" : "Playing", 10, 15);
      drawText("Current frame: "+std::to_string(currentFrame), 10, 35);
      drawText("Time scale: "+std::to_string(timeScale), 10, 55);
   }

   virtual void keyUp(int key, int mods) {
      if (key == GLFW_KEY_P) {
         paused = !paused;
      }
      if (key == GLFW_KEY_0) {
         motion.update(skeleton, 0);
      }
      if (key == GLFW_KEY_PERIOD) {
         paused = true; 
         if (currentFrame >= motion.getNumKeys()) {
            currentFrame = 0;
            time = 0;
         }
         currentFrame++;
         time += dt();
         motion.update(skeleton, time);
      }
      if (key == GLFW_KEY_COMMA) {
         paused = true; 
         if (time <= 0 || currentFrame <= 0) {
            currentFrame = motion.getNumKeys()-1;
            time = motion.getNumKeys();
         }
         currentFrame--;
         time -= dt();
         motion.update(skeleton, time);
      }
      if (key == GLFW_KEY_RIGHT_BRACKET) {
         timeScale = 1.3f * dt();
         // motion.update(skeleton, timeScale);
         rightBracket = true;
      }
      if (key == GLFW_KEY_LEFT_BRACKET) {
         timeScale = 0.3f * dt();
         leftBracket = true;
      }
   }

private:
   Skeleton skeleton;
   Motion motion;

   float timeScale = 1.0f;
   int currentFrame = 0; 
   bool paused = false;
   float time = 0;
   bool rightBracket; 
   bool leftBracket;
   bool commaPressed; 
   bool periodPressed;
};


int main(int argc, char** argv) {
   MotionViewer viewer;
   if (argc == 1) {
      viewer.setFilename("");
   }
   else {
      viewer.setFilename(argv[1]);
   }
   viewer.run();
}
