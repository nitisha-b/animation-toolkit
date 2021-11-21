#include "atkui/framework.h"
#include "atkui/skeleton_drawer.h"
#include "atk/toolkit.h"
#include <iostream>
#include <cmath>

using namespace glm;
using namespace std;
using namespace atk;

class WASDSimple : public atkui::Framework
{
public:
  WASDSimple() : atkui::Framework(atkui::Perspective) {}

  virtual void setup()
  {
    BVHReader reader;
    reader.load("../motions/Beta/walking.bvh", _skeleton, _walk);
    _drawer.showAxes = true;
  }

  virtual void scene()
  {
    update();
    _drawer.draw(_skeleton, *this);

    // draw heading
    vec3 p = _skeleton.getRoot()->getGlobalTranslation();
    p[1] = 10; // set height close above the floor

    setColor(vec3(0, 1, 1));
    push();
    translate(p);
    rotate(_heading, vec3(0, 1, 0));
    translate(vec3(0,0,25));
    scale(vec3(10, 10, 50));
    drawCylinder(vec3(0), 1.0f);
    pop();
  }

  virtual void update()
  {
    _walk.update(_skeleton, elapsedTime());
    vec3 velocity = vec3(0,0,_heading) * 50.0f;
    Joint* hip = _skeleton.getByName("Beta:Hips");
    Joint* head = _skeleton.getByName("Beta:Head");
    vec3 headPos = head->getGlobalTranslation();

    // TODO: Your code here
    for (int i = 0; i < _walk.getNumKeys(); i++) {
      Pose pose = _walk.getKey(i); 
      
      // pose.rootPos = vec3(0, 100, 0);
      
      // vec3 headT = head->getLocal2Global().transformVector(vec3(0,0,-400));

      pose.rootPos = headPos + velocity * dt();
      // pose.jointRots[hip->getID()] = eulerAngleRO(XYZ, vec3(0, _heading, 0));
      _walk.editKey(i, pose);
    
      

    // TODO: Override the default camera to follow the character

      vec3 headT = head->getLocal2Global().transformVector(vec3(0,0,-400));
      vec3 headPos1 = head->getGlobalTranslation();
      globalPos = headPos1+headT;
      // globalPos = head->getGlobalTranslation();
      globalLookPos = headPos1;
      // globalLookPos = headPos - vec3(0,0,-400);
      lookAt(globalPos, globalLookPos, vec3(0,1,0));   
    }

    // update heading when key is down
    if (keyIsDown('D')) {
      _heading -= 0.05;

      for (int i = 0; i < _walk.getNumKeys(); i++) {
        Pose pose = _walk.getKey(i);
        pose.jointRots[hip->getID()] = angleAxis(_heading, vec3(0,1,0));
        _walk.editKey(i, pose); 
      }
    }
    if (keyIsDown('A')) {
      _heading += 0.05;

      for (int i = 0; i < _walk.getNumKeys(); i++) {
        Pose pose = _walk.getKey(i);
        pose.jointRots[hip->getID()] = angleAxis(_heading, vec3(0,1,0));
        _walk.editKey(i, pose); 
      }
    }
  }

protected:
  float _heading;

  Motion _walk;
  Skeleton _skeleton;
  atkui::SkeletonDrawer _drawer;
  vec3 globalPos;
  vec3 globalLookPos;
};

int main(int argc, char **argv)
{
  WASDSimple viewer;
  viewer.run();
}
