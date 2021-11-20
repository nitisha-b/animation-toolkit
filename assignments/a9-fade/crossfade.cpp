#include "atk/toolkit.h"
#include "atkui/framework.h"
#include "atkui/skeleton_drawer.h"
#include <stdio.h>
#include <string.h>

using namespace atk;
using namespace atkui;
using namespace glm;

class ACrossfadeViewer : public atkui::Framework
{
public:
  ACrossfadeViewer() : atkui::Framework(atkui::Perspective) {}
  virtual ~ACrossfadeViewer() {}

  void loadMotion1(const std::string &filename)
  {
    BVHReader reader;
    reader.load(filename, skeleton_, motion1_);
  }

  void loadMotion2(const std::string &filename)
  {
    BVHReader reader;
    reader.load(filename, skeleton_, motion2_);
  }

  void crossfade(int numBlendFrames)
  {
    assert(motion1_.getNumKeys() > 0);
    assert(motion2_.getNumKeys() > 0);
    assert(numBlendFrames > 0);
    assert(numBlendFrames <= motion1_.getNumKeys());
    assert(numBlendFrames <= motion2_.getNumKeys());

    int start1 = motion1_.getNumKeys() - numBlendFrames - 1;
    int start2 = 0;

    // TODO: Your code here
  
    blend_.setFramerate(motion1_.getFramerate());
    // float alpha = (float)1/numBlendFrames;

    for (int i = 0; i < motion1_.getNumKeys(); i++){
      blend_.appendKey(motion1_.getKey(i));
    }

    for (float a = 0.0f; a <= 1.0f; a+=0.15) {
      Pose blended = Pose::Lerp(motion1_.getKey(start1), motion2_.getKey(start2), a);
      blend_.appendKey(blended);
    }

    Joint* hip = skeleton_.getByName("Beta:Hips");
    Pose pose1 = motion1_.getKey(motion1_.getNumKeys()-1);
    Pose pose2 = motion2_.getKey(0);
    vec3 root1 = pose1.rootPos;
    quat rotation1 = pose1.jointRots[hip->getID()];
    Transform t1 = Transform(root1, rotation1);

    vec3 root2 = pose2.rootPos;
    quat rotation2 = pose2.jointRots[hip->getID()];
    Transform t2 = Transform(root2, rotation2);


    for (int i = 0; i < motion2_.getNumKeys(); i++){
      // Pose pose1 = motion1_.getKey(motion1_.getNumKeys()-1);
      Pose pose = motion2_.getKey(i);
      // vec3 rootMotion1 = motion1_.getKey(motion1_.getNumKeys()-1).rootPos;
      // pose.rootPos = rootMotion1;
      // pose.jointRots[hip->getID()] = eulerAngleRO(XYZ, vec3(hipQuat.x, hipQuat.y, hipQuat.z));

      
      pose.rootPos = pose.rootPos * eulerAngleRO(XYZ, vec3(hipQuat.x, hipQuat.y, hipQuat.z));
      // pose.rootPos = eulerAngleRO(XYZ, pose1.jointRots[hip->getID()]) * rootMotion1;  
      motion2_.editKey(i, pose);

      // blend_.appendKey(motion2_.getKey(i));

      // Pose last = motion1_.getKey(motion1_.getNumKeys()-1);
      // Pose first = motion2_.getKey(0);
      // vec3 offset = last.rootPos - first.rootPos; 
      // Transform transform = Transform();
      // transform.setT(offset);
      // pose.rootPos *= offset; 

      blend_.appendKey(motion2_.getKey(i));
    }



  }

  void save(const std::string &filename)
  {
    BVHWriter writer;
    writer.save(filename, skeleton_, blend_);
  }

  void scene()
  {
    blend_.update(skeleton_, elapsedTime());
    drawer_.draw(skeleton_, *this);
  }

private:
  Skeleton skeleton_;
  SkeletonDrawer drawer_;
  Motion motion1_;
  Motion motion2_;
  Motion blend_;
};

std::string PruneName(const std::string &name)
{
  int idx1 = name.find_last_of("/");
  int idx2 = name.find_last_of(".");
  return name.substr(idx1 + 1, idx2 - idx1 - 1);
}

int main(int argc, char **argv)
{
  std::string motion1 = "../motions/Beta/left_turn_90.bvh";
  std::string motion2 = "../motions/Beta/walking.bvh";
  int numFrames = 10;

  try
  {
    for (int i = 0; i < argc; i++)
    {
      if (strncmp(argv[i], "-m1", 3) == 0)
        motion1 = argv[i + 1];
      else if (strncmp(argv[i], "-m2", 3) == 0)
        motion2 = argv[i + 1];
      else if (strncmp(argv[i], "-nframes", 7) == 0)
        numFrames = std::stoi(argv[i + 1]);
    }
  }
  catch (const std::exception &e)
  {
    std::cout << "usage: crossfade -m1 <path> -m2 <path> -nframes <num frames>\n";
  }

  ACrossfadeViewer viewer;
  viewer.loadMotion1(motion1);
  viewer.loadMotion2(motion2);
  viewer.crossfade(numFrames);

  std::string saveName = "blend-" + PruneName(motion1) + PruneName(motion2);
  saveName += "-" + std::to_string(numFrames) + ".bvh";
  viewer.save(saveName);

  viewer.run();
  return 0;
}
