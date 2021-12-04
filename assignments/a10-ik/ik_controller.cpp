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
  
  Joint* current = skeleton.getByID(jointid);
  Joint* parent = current->getParent();
  Joint* grandParent = parent->getParent();

  // vec3 rVec = goalPos - grandParent->getGlobalTranslation();
  // float r = length(rVec);
  float r = length(goalPos - grandParent->getGlobalTranslation());
  vec3 eVec = goalPos - current->getGlobalTranslation();
  float e = length(eVec);

  float l1 = length(parent->getGlobalTranslation() - grandParent->getGlobalTranslation());
  float l2 = length(current->getGlobalTranslation() - parent->getGlobalTranslation());
  float cosPhi = (pow(r,2) - pow(l1,2) - pow(l2,2)) / (-2 * l1 * l2);  
  float theta2z = acos(cosPhi) - M_PI;
  float theta1z = asin((-l2 * sin(theta2z))/r);
  float gamma = asin(goalPos[1]/r);
  float beta = atan2(goalPos[2], goalPos[0]);

  // Use the angle/axis CCD computation to solve for the grandparent joint rotation.
  vec3 rVec = current->getGlobalTranslation() - grandParent->getGlobalTranslation();
  vec3 rXe = cross(rVec, eVec);
  float phi = atan2(length(rXe), (dot(rVec,eVec) + dot(rVec,rVec)));
  vec3 gpAxis = rXe / length(rXe);

  if (length(rXe) < epsilon) {
    gpAxis = vec3(0,0,1);
  }
  
  quat gpRot = angleAxis(phi, inverse(grandParent->getParent()->getGlobalRotation()) * gpAxis);
  grandParent->setLocalRotation(gpRot * grandParent->getLocalRotation());
  // grandParent->fk();
  skeleton.fk();

  // Use the law of cosines to solve for the parent joint rotation.
  vec3 limbDir = normalize(parent->getLocalTranslation());
  vec3 axis = cross(limbDir, vec3(0,0,-1));
  if (limbDir[1] < 0) axis = cross(limbDir, vec3(0,0,1));
  quat pRot = angleAxis(theta2z, axis);
  parent->setLocalRotation(pRot);

  // grandParent->fk();
  // parent->fk();
  // current->fk();
  skeleton.fk();

  return true;
}

bool IKController::solveIKCCD(Skeleton& skeleton, int jointid, 
    const vec3& goalPos, const std::vector<Joint*>& chain, 
    float threshold, int maxIters, float nudgeFactor) {
  // There are no joints in the IK chain for manipulation
  if (chain.size() == 0) return true;

    vec3 p = chain[0]->getGlobalTranslation();
    int count = 0; 

    while ((glm::length(goalPos-p) > threshold) && count < maxIters) {
      for (int i = 1; i < chain.size(); i++) {
        Joint* endEff = chain[0];
        Joint* currJoint = chain[i];

        vec3 r = endEff->getGlobalTranslation() - currJoint->getGlobalTranslation(); 
        vec3 e = goalPos - endEff->getGlobalTranslation(); 

        // vec3 r = currJoint->getGlobalTranslation() - currJoint->getParent()->getGlobalTranslation();
        // vec3 e = goalPos - currJoint->getGlobalTranslation(); 

        if (length(e) < 0.0001) {
          continue;
        }

        if (length(glm::cross(r,e)) < 0.0001) {
          continue;
        }

        float phi = atan2(glm::length(glm::cross(r,e)), (glm::dot(r,e) + glm::dot(r,r))) * nudgeFactor;
        vec3 axis = glm::cross(r,e) / glm::length(glm::cross(r,e));

        quat rot = angleAxis(phi, inverse(currJoint->getParent()->getGlobalRotation()) * axis);
        currJoint->setLocalRotation(rot * currJoint->getLocalRotation());
        
        currJoint->fk();
        // skeleton.fk();
      }
      p = skeleton.getByID(jointid)->getGlobalTranslation();
      count++;

    }


  return false;
}
