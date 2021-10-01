#ifndef _interpolator_linear_H_
#define _interpolator_linear_H_

#include <string>
#include <vector>
#include "interpolator.h"

//--------------------------------
// Linear 
//--------------------------------

class InterpolatorLinear : public Interpolator
{
public:
   InterpolatorLinear() : Interpolator("Linear") {}

   virtual glm::vec3 interpolate(int segment, double u) const {
      glm::vec3 b0 = mCtrlPoints[segment] * (float(1-u)) + mCtrlPoints[segment+ 1] * (float)u;
      return b0;
   }

   virtual void computeControlPoints(const std::vector<glm::vec3>& keys) {
      for (int i = 0; i < keys.size(); i++){
         mCtrlPoints.push_back(keys[i]);
      }
   }
};

#endif
