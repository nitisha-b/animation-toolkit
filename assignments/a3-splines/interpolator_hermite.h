#ifndef _interpolator_hermite_
#define _interpolator_hermite_

#include <string>
#include <vector>
#include <Eigen/Dense>
#include "interpolator.h"

//--------------------------------
// Hermite 
//--------------------------------

class InterpolatorHermite : public Interpolator
{
public:
    InterpolatorHermite() : Interpolator("Hermite"), mClampDir(glm::vec3(1,0,0)) {}

    virtual glm::vec3 interpolate(int segment, double u) const {

        // use the hermite interpolation formula, where segment*i is p0 and segment*i+2 is p1
        float t1 = 2 * pow(u,3) - 3 * pow(u,2) + 1; 
        float t2 = u * pow((1-u), 2); 
        float t3 =  -pow(u,2) +  pow(u,3);
        float t4 = 3 * pow(u,2) - 2 * pow(u,3); 
        glm::vec3 p = t1 * mCtrlPoints[segment*2] + t2 * mCtrlPoints[segment*2+1] + t3 * mCtrlPoints[segment*2+3] + t4 * mCtrlPoints[segment*2+2];
       return p;
    }

    virtual void computeControlPoints(const std::vector<glm::vec3>& keys) {
        Eigen::MatrixXd A(5,5);
        Eigen::MatrixXd p(5,3);
        Eigen::MatrixXd pPrime(5,3); // slopes for each control point

        // natural endpoints
        A(0,0) =  2; A(0,1) = 1; A(0,2) = 0; A(0,3) = 0; A(0,4) = 0;
        A(1,0) =  1; A(1,1) = 4; A(1,2) = 1; A(1,3) = 0; A(1,4) = 0;
        A(2,0) =  0; A(2,1) = 1; A(2,2) = 4; A(2,3) = 1; A(2,4) = 0;
        A(3,0) =  0; A(3,1) = 0; A(3,2) = 1; A(3,3) = 4; A(3,4) = 1;
        A(4,0) =  0; A(4,1) = 0; A(4,2) = 0; A(4,3) = 1; A(4,4) = 2;

        // use 5 points at a time 
        for (int k = 0; k < keys.size()-4; k += 4) {
            glm::vec3 v0 = 3.0f *(keys[k+1] - keys[k]);
            glm::vec3 v1 = 3.0f *(keys[k+2] - keys[k]);
            glm::vec3 v2 = 3.0f *(keys[k+3] - keys[k+1]);
            glm::vec3 v3 = 3.0f *(keys[k+4] - keys[k+2]);
            glm::vec3 v4 = 3.0f *(keys[k+4] - keys[k+3]);

            // populate p 
            p(0,0) = v0[0]; p(0,1) = v0[1]; p(0,2) = v0[2];
            p(1,0) = v1[0]; p(1,1) = v1[1]; p(1,2) = v0[2];
            p(2,0) = v2[0]; p(2,1) = v2[1]; p(2,2) = v0[2];
            p(3,0) = v3[0]; p(3,1) = v3[1]; p(3,2) = v0[2];
            p(4,0) = v4[0]; p(4,1) = v4[1]; p(4,2) = v0[2];

            pPrime = A.inverse() * p;

            for (int j = 0; j <= k+4; j++) {
                glm::vec3 a = glm::vec3(pPrime(j,0), pPrime(j,1), 0);
                // push in the order p0p'0 p1p'1
                mCtrlPoints.push_back(keys[j]);
                mCtrlPoints.push_back(a);
            }
        }
    }

    void setClamped(bool c) { mIsClamped = c; }
    bool isClamped() const { return mIsClamped; }

    void setClampedDirection(const glm::vec3& v) { mClampDir = v; }
    glm::vec3 getClampDirection() const { return mClampDir; }

private:
    bool mIsClamped = true;
    glm::vec3 mClampDir;
};

#endif
