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
    init.b0 = (generateRandomVector());
    init.b1 = (generateRandomVector());
    init.b2 = (generateRandomVector());
    init.b3 = (generateRandomVector());
    // randColor1 = agl::randomUnitVector()/2.5f;
    init.color = agl::randomUnitVector()/2.5f;

    // get random final control points
    fin.b0 = (generateRandomVector());
    fin.b1 = (generateRandomVector());
    fin.b2 = (generateRandomVector());
    fin.b3 = (generateRandomVector());
    fin.color = agl::randomUnitVector()/2.5f;

    curves = list<Curve>(max);

    t = 0.0;
    timer = 0.0; 
  }

  void scene()
  {
    // draw initial and final curves
    for (float i = 0.0; i < 1.0; i += 0.002)
    {
      drawCurve(init.b0, init.b1, init.b2, init.b3, i, init.color);
    }

    Curve current;
    current.b0 = interpolate(init.b0, fin.b0, t);
    current.b1 = interpolate(init.b1, fin.b1, t);
    current.b2 = interpolate(init.b2, fin.b2, t);
    current.b3 = interpolate(init.b3, fin.b3, t);
    current.color = interpolate(init.color, fin.color, t);

    if (t > 1.0)
    {
      t = 0.0;
      // set initial to current
      init.b0 = current.b0;
      init.b1 = current.b1;
      init.b2 = current.b2;
      init.b3 = current.b3;
      // init = current;

      // set final to new curve
      fin.b0 = (generateRandomVector());
      fin.b1 = (generateRandomVector());
      fin.b2 = (generateRandomVector());
      fin.b3 = (generateRandomVector());

      // randColor1 = agl::randomUnitVector()/2.5f;
      fin.color = agl::randomUnitVector()/2.5f;
    }

    else
    {
      t += 0.08;
      timer += t;
      if (timer > 0.2){
        curves.push_back(current);
        
        if (curves.size() >= max){
          curves.pop_front();
        }
        timer = 0.0;
      }
    }

    for(Curve& curr: curves) {
      for (float i = 0.0; i < 1.0; i += 0.002)
      {
        drawCurve(curr.b0, curr.b1, curr.b2, curr.b3, i, curr.color);
      }
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
    drawSphere(curve, 1.5);
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

  struct Curve {
    vec3 b0;
    vec3 b1;
    vec3 b2;
    vec3 b3;
    vec3 color;
  };

private:
  vec3 curve;
  float t;
  int max = 40;
  list<Curve> curves;

  float timer;
  Curve init; 
  Curve fin;

};

int main(int argc, char **argv)
{
  Screensaver viewer;
  viewer.run();
}
