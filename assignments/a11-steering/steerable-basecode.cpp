#include "steerable.h"
#include "behaviors.h"

using namespace glm;
using namespace atk;

float ASteerable::kVelKv = 2.0; 
float ASteerable::kOriKv = 16.0;  
float ASteerable::kOriKp = 64.0;

// Given a desired velocity, veld, and dt, compute a transform holding 
// the new orientation and change in position
//
// rotation control: tau = I * (-Kv1 * thetaDot + Kp1 * (thetaD - theta))
// translation control: f = m * Kv0 * (vd - v)
void ASteerable::senseControlAct(const vec3& veld, float dt)
{
   // Compute _vd and _thetad
   _vd = length(veld);
   _thetad = atan2(veld.x, veld.z);
   
   // compute _force and _torque
   _force = _mass * kVelKv * _vd;
   float a = _thetad - _state[1];
   
   if (a > M_PI) a -= 2 * M_PI;
   else if (a < -M_PI) a += 2*M_PI;
   _torque = _inertia * (-kOriKv * _state[3]) + kOriKp * a;

   // find derivative
   _derivative[0] = _state[2];
   _derivative[1] = _state[3];
   _derivative[2] = (float)_force/_mass;
   _derivative[3] = (float)_torque/_mass;
   
   // update state
   _state[0] += dt * _derivative[0];
   _state[1] += dt * _derivative[1];
   _state[2] += dt * _derivative[2];
   _state[3] += dt * _derivative[3];

   // compute global position and orientation and update _characterRoot
   quat rot = glm::angleAxis(_state[ORI], vec3(0,1,0));
   vec3 localPos(0,0,_state[POS]);

   _characterRoot.setT(rot * localPos + _characterRoot.t());
   _characterRoot.setR(rot); 
}

// randomize the colors, characters, and animation times here
void ASteerable::randomizeAppearance()
{
   // to randomize the walking animations, compute different initial values 
   // for _time

   // to randomize color, call _drawer.setColor

   // to randomize shape, compute random values for _drawer.setJointRadius
   // or randomly assign different drawers to have a mix of characters
}

