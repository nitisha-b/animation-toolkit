#ifndef _interpolator_catmullrom_
#define _interpolator_catmullrom_

#include <string>
#include <vector>
#include "interpolator.h"

//--------------------------------
// Catmull-Rom 
//--------------------------------

class InterpolatorCatmullRom : public Interpolator
{
public:
   InterpolatorCatmullRom() : Interpolator("Catmull-Rom") {}

   virtual glm::vec3 interpolate(int segment, double u) const {
      
      int n = 0;
      if (segment == 0) {
         n = 4*segment; // index
      }
      else {
         n = 4*segment-1; // index
      }

      glm::vec3 b0 = mCtrlPoints[n];
      glm::vec3 b1 = mCtrlPoints[n+1];
      glm::vec3 b2 = mCtrlPoints[n+2];
      glm::vec3 b3 = mCtrlPoints[n+3];

      float term1 = std::pow((1-u),3);
      float term2 = 3 * u * std::pow((1-u),2);
      float term3 = 3 * std::pow(u,2)*(1-u);
      float term4 = std::pow(u,3);
      glm::vec3 p = term1 * b0 + term2 * b1 + term3 * b2 + term4 * b3;
      return p;
   }

   virtual void computeControlPoints(const std::vector<glm::vec3>& keys) {
      // First segment
      mCtrlPoints.push_back(keys[0]);
      glm::vec3 f_b1 = keys[0] + (1.0f/6) * (keys[1] - keys[0]);
      mCtrlPoints.push_back(f_b1);

      for (int i = 1; i < keys.size()-1; i++) {
         if (i == keys.size()-2) {
            glm::vec3 b2 = keys[i] - (1.0f/6) * (keys[i+1] - keys[i-1]);
            mCtrlPoints.push_back(b2);
         }
         else {
            glm::vec3 b2 = keys[i+1] - (1.0f/6) * (keys[i+2] - keys[i]);
            mCtrlPoints.push_back(b2);
         }
         mCtrlPoints.push_back(keys[i]);
         glm::vec3 b1 = keys[i] + (1.0f/6) * (keys[i+1] - keys[i-1]); 
         mCtrlPoints.push_back(b1);
      }
      
      // Last segment
      glm::vec3 l_b2 = keys[keys.size()-1] - (1.0f/6) * (keys[keys.size()-1] - keys[keys.size()-2]);
      mCtrlPoints.push_back(l_b2);
      mCtrlPoints.push_back(keys[keys.size()-1]);
   }
};

#endif
