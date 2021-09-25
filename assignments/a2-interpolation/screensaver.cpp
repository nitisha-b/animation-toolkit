#include "atkui/framework.h"
using namespace glm;
using namespace std;

class Screensaver : public atkui::Framework
{
public:
  Screensaver() : atkui::Framework(atkui::Orthographic)
  {
  }

  void setup()
  {
    // get initiral random control points
    initPos.push_back(generateRandomVector());
    initPos.push_back(generateRandomVector());
    initPos.push_back(generateRandomVector());
    initPos.push_back(generateRandomVector());

    // get random final control points
    finalPos.push_back(generateRandomVector());
    finalPos.push_back(generateRandomVector());
    finalPos.push_back(generateRandomVector());
    finalPos.push_back(generateRandomVector());

    randColor1 = agl::randomUnitVector();
    randColor2 = agl::randomUnitVector();
    randColor3 = agl::randomUnitVector();

    currentPos = vector<vec3>(4);

    t = 0.0;
  }

  void scene()
  {
    // draw initial and final curves
    for (float i = 0.0; i < 1.0; i += 0.1)
    {
      setColor(randColor1);
      drawCurve(initPos[0], initPos[1], initPos[2], initPos[3], i);
    }

    for (float i = 0.0; i < 1.0; i += 0.1)
    {
      setColor(randColor2);
      drawCurve(finalPos[0], finalPos[1], finalPos[2], finalPos[3], i);
    }

    if (t > 1.0)
    {
      t = 0.0;
      // set initial to current
      initPos[0] = currentPos[0];
      initPos[1] = currentPos[1];
      initPos[2] = currentPos[2];
      initPos[3] = currentPos[3];

      // set final to new curve
      finalPos.push_back(generateRandomVector());
      finalPos.push_back(generateRandomVector());
      finalPos.push_back(generateRandomVector());
      finalPos.push_back(generateRandomVector());

      randColor1 = agl::randomUnitVector()/2.0f;
      randColor2 = agl::randomUnitVector()/2.0f;
      randColor3 = agl::randomUnitVector()/2.0f;
    }

    else
    {
      t += 0.05;
    }

    // interpolate
    currentPos[0] = interpolate(initPos[0], finalPos[0], t);
    currentPos[1] = interpolate(initPos[1], finalPos[1], t);
    currentPos[2] = interpolate(initPos[2], finalPos[2], t);
    currentPos[3] = interpolate(initPos[3], finalPos[3], t);

    for (float i = 0.0; i < 1.0; i += 0.1)
    {
      setColor(randColor3);
      drawCurve(currentPos[0], currentPos[1], currentPos[2], currentPos[3], i);
    }
  }

  virtual void drawCurve(vec3 B0, vec3 B1, vec3 B2, vec3 B3, float t)
  {
    float term1 = (std::pow((1 - t), 3));
    float term2 = (3 * t * std::pow((1 - t), 2));
    float term3 = (3 * std::pow(t, 2) * (1 - t));
    float term4 = (std::pow(t, 3));
    curve = term1 * B0 + term2 * B1 + term3 * B2 + term4 * B3;
    drawSphere(curve, 4);
  }

  // virtual vector<vec3> generateRandomControlPoints()
  // {
  //   vector<vec3> temp = {
  //       vec3(agl::random(0, width()), agl::random(0, height()), 0),
  //       vec3(agl::random(0, width()), agl::random(0, height()), 0),
  //       vec3(agl::random(0, width()), agl::random(0, height()), 0),
  //       vec3(agl::random(0, width()), agl::random(0, height()), 0),
  //   };
  //   return temp;
  // }

  virtual vec3 generateRandomVector()
  {
    return vec3(agl::random(0, width()), agl::random(0, height()), 0);
  }

  virtual vec3 interpolate(vec3 f, vec3 l, float t)
  {
    return f * (1.0f - t) + l * t;
  }

private:
  vec3 curve;
  float t;
  vector<vec3> initPos;    
  vector<vec3> finalPos;   
  vector<vec3> currentPos; 
  vec3 randColor1;
  vec3 randColor2;
  vec3 randColor3;
};

int main(int argc, char **argv)
{
  Screensaver viewer;
  viewer.run();
}
