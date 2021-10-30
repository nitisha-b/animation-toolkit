#include "atkui/framework.h"
#include "atk/toolkit.h"
using namespace atk;
using glm::quat;
using glm::vec3;
// using namespace atkmath;

class Unique : public atkui::Framework
{
public:
    Unique() : atkui::Framework(atkui::Perspective) {}
    virtual ~Unique() {}

    virtual void setup()
    {
        lookAt(vec3(200), vec3(0));

        Joint *root = new Joint("root");
        root->setLocalTranslation(vec3(0, 120, 0));
        _tentacle.addJoint(root);

        Joint *leftT = new Joint("leftT");
        leftT->setLocalTranslation(vec3(-20, -50, 0));
        _tentacle.addJoint(leftT, root);

        Joint *rightT = new Joint("rightT");
        rightT->setLocalTranslation(vec3(20, -50, 0));
        _tentacle.addJoint(rightT, root);

        Joint *leftLeg = new Joint("leftLeg");
        leftLeg->setLocalTranslation(vec3(-5, -70, 0));
        _tentacle.addJoint(leftLeg, leftT);

        Joint *rightLeg = new Joint("rightLeg");
        rightLeg->setLocalTranslation(vec3(5, -70, 0));
        _tentacle.addJoint(rightLeg, rightT);

        Joint *abdomen = new Joint("abdomen");
        abdomen->setLocalTranslation(vec3(0, 50, 0));
        _tentacle.addJoint(abdomen, root);

        Joint *chest = new Joint("chest");
        chest->setLocalTranslation(vec3(0, 30, 0));
        _tentacle.addJoint(chest, abdomen);

        Joint *leftArm = new Joint("leftArm");
        leftArm->setLocalTranslation(vec3(-50, -10, 0));
        _tentacle.addJoint(leftArm, abdomen);

        Joint *rightArm = new Joint("rightArm");
        rightArm->setLocalTranslation(vec3(50, -10, 0));
        _tentacle.addJoint(rightArm, abdomen);

        Joint *leftHand = new Joint("leftHand");
        leftHand->setLocalTranslation(vec3(-50, -10, 0));
        _tentacle.addJoint(leftHand, leftArm);

        Joint *rightHand = new Joint("rightHand");
        rightHand->setLocalTranslation(vec3(50, -10, 0));
        _tentacle.addJoint(rightHand, rightArm);

        Joint *head = new Joint("head");
        head->setLocalTranslation(vec3(0, 0, 0));
        _tentacle.addJoint(head, chest);

        _tentacle.fk(); // compute local2global transforms
    }

    virtual void scene()
    {
        _tentacle.fk(); // computes local2global transforms
        setColor(vec3(0, 0, 1));

        Joint *root = _tentacle.getByID(0);
        vec3 globalPos = root->getGlobalTranslation();
        drawSphere(globalPos, 15);

        for (int i = 1; i < _tentacle.getNumJoints(); i++)
        {
            Joint *child = _tentacle.getByID(i);
            if (child->getName() == "head") {
                drawSphere(child->getGlobalTranslation(), 25);
                break;
            }
            Joint *parent = child->getParent();
            vec3 globalParentPos = parent->getGlobalTranslation();
            vec3 globalPos = child->getGlobalTranslation();
            // animate tentacle
            quat animate = glm::angleAxis(sin(elapsedTime() * i), vec3(0, 1, 0));
            child->setLocalRotation(animate);
            drawEllipsoid(globalParentPos, globalPos, 10);
        }
    }

protected:
    Skeleton _tentacle;
};

int main(int argc, char **argv)
{
    Unique viewer;
    viewer.run();
}
