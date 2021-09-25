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
    for (float i = 0.0; i < 1.0; i += 0.002)
    {
      drawCurve(initPos[0], initPos[1], initPos[2], initPos[3], i, randColor1);
    }

    for (float i = 0.0; i < 1.0; i += 0.002)
    {
      drawCurve(finalPos[0], finalPos[1], finalPos[2], finalPos[3], i, randColor2);
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
      finalPos[0] = generateRandomVector();
      finalPos[1] = generateRandomVector();
      finalPos[2] = generateRandomVector();
      finalPos[3] = generateRandomVector();

      randColor1 = agl::randomUnitVector()/2.5f;
      randColor2 = agl::randomUnitVector()/2.5f;
      // randColor3 = agl::randomUnitVector();
    }

    else
    {
      t += 0.024;
    }

    // interpolate
    currentPos[0] = interpolate(initPos[0], finalPos[0], t);
    currentPos[1] = interpolate(initPos[1], finalPos[1], t);
    currentPos[2] = interpolate(initPos[2], finalPos[2], t);
    currentPos[3] = interpolate(initPos[3], finalPos[3], t);
    randColor3 = interpolate(randColor1, randColor2, t);

    for (float i = 0.0; i < 1.0; i += 0.002)
    {
      drawCurve(currentPos[0], currentPos[1], currentPos[2], currentPos[3], i, randColor3);
    }
  }

  virtual void drawCurve(vec3 B0, vec3 B1, vec3 B2, vec3 B3, float t, vec3 color)
  {
    float term1 = (std::pow((1 - t), 3));
    float term2 = (3 * t * std::pow((1 - t), 2));
    float term3 = (3 * std::pow(t, 2) * (1 - t));
    float term4 = (std::pow(t, 3));
    curve = term1 * B0 + term2 * B1 + term3 * B2 + term4 * B3;
    setColor(color);
    drawSphere(curve, 3);
  }

  virtual vec3 generateRandomVector()
  {
    // Using agl::random() was causing the program to be very slow
    return vec3((float)(rand() % (int)width()), (float)(rand() % (int)height()), 0);
  }

  virtual vec3 interpolate(vec3 f, vec3 l, float t)
  {
    return f * (1 - t) + l * t;
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
