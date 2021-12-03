#include "ik_controller.h"
#include <cmath>
#include <iostream>

using namespace atk;
using namespace glm;
using namespace std;

bool IKController::solveIKAnalytic(Skeleton& skeleton, 
    int jointid, const vec3& goalPos, float epsilon) {
  if (jointid == -1) return true;

  Joint* ankle = skeleton.getByID(jointid);
  if (!ankle->getParent()) {
    std::cout << "Warning: solveIKAnalytic() needs joint "
      "with parent and grandparent\n";
    return false;
  }

  Joint* knee = ankle->getParent();
  if (!knee->getParent()) {
    std::cout << "Warning: solveIKAnalytic() needs joint "
      "with parent and grandparent\n";
    return false;
  }

  Joint* hip = knee->getParent();

  // TODO: Your code here


  return true;
}

bool IKController::solveIKCCD(Skeleton& skeleton, int jointid, 
    const vec3& goalPos, const std::vector<Joint*>& chain, 
    float threshold, int maxIters, float nudgeFactor) {
  // There are no joints in the IK chain for manipulation
  if (chain.size() == 0) return true;

  // TODO: Your code here

    // solveIKCCD positions the joint given by jointid so its global position
    // is located at goalPos
    //
    // param skeleton: the character to modify
    // param jointid: the ID of the joint to pose
    // param goalPos: the target position for jointid (global pos)
    // param chain: the list of joints to "nudge" towards the goal
    // param threshold: when the given joint is within threshold of the goal, stop iterating
    // param maxIters: the max number of iterations to try to reach the goal
    //
    // return true/false based on whether we could reach the goal
    // side effect: skeleton should by posed such that jointid is located at goalPos (or in this direction of
    // goalPos if the target is out of reach)
    vec3 p = chain[0]->getGlobalTranslation();
    int count = 0; 

    while ((glm::length(goalPos-p) > threshold) && count < maxIters) {
      for (int i = 1; i < chain.size(); i++) {
        Joint* endEff = chain[0];
        Joint* currJoint = chain[i];

        // vec3 r = endEff->getGlobalTranslation() - currJoint->getGlobalTranslation(); 
        // vec3 e = goalPos - endEff->getGlobalTranslation(); 

        vec3 r = currJoint->getGlobalTranslation() - currJoint->getParent()->getGlobalTranslation();
        vec3 e = goalPos - currJoint->getGlobalTranslation(); 

        float phi = atan2(glm::length(glm::cross(r,e)), (glm::dot(r,e) + glm::dot(r,r))) * nudgeFactor;
        vec3 axis = glm::cross(r,e) / glm::length(glm::cross(r,e));

        currJoint->setLocalRotation(currJoint->getLocalRotation() * angleAxis(phi,axis));
        // currJoint->setLocalRotation(angleAxis(phi,axis));
      
        currJoint->fk();
        // skeleton.fk();
      }
      // skeleton.fk();
      p = skeleton.getByID(jointid)->getGlobalTranslation();
      count++;

    }


  return false;
}
