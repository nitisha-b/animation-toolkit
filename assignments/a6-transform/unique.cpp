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
        lookAt(vec3(300), vec3(0));

        // person 1 (blue)
        Joint *root1 = new Joint("root1");
        root1->setLocalTranslation(vec3(0, 120, 0));
        person1.addJoint(root1);

        Joint *leftT1 = new Joint("leftT1");
        leftT1->setLocalTranslation(vec3(-20, -50, 0));
        person1.addJoint(leftT1, root1);

        Joint *rightT1 = new Joint("rightT1");
        rightT1->setLocalTranslation(vec3(20, -50, 0));
        person1.addJoint(rightT1, root1);

        Joint *leftLeg1 = new Joint("leftLeg1");
        leftLeg1->setLocalTranslation(vec3(-5, -70, 0));
        person1.addJoint(leftLeg1, leftT1);

        Joint *rightLeg1 = new Joint("rightLeg1");
        rightLeg1->setLocalTranslation(vec3(5, -70, 0));
        person1.addJoint(rightLeg1, rightT1);

        Joint *abdomen1 = new Joint("abdomen1");
        abdomen1->setLocalTranslation(vec3(0, 50, 0));
        person1.addJoint(abdomen1, root1);

        Joint *chest1 = new Joint("chest1");
        chest1->setLocalTranslation(vec3(0, 30, 0));
        person1.addJoint(chest1, abdomen1);

        Joint *leftArm1 = new Joint("leftArm1");
        leftArm1->setLocalTranslation(vec3(-50, -10, 0));
        person1.addJoint(leftArm1, abdomen1);

        Joint *rightArm1 = new Joint("rightArm1");
        rightArm1->setLocalTranslation(vec3(50, -10, 0));
        person1.addJoint(rightArm1, abdomen1);

        Joint *leftHand1 = new Joint("leftHand1");
        leftHand1->setLocalTranslation(vec3(-50, -10, 0));
        person1.addJoint(leftHand1, leftArm1);

        Joint *rightHand1 = new Joint("rightHand1");
        rightHand1->setLocalTranslation(vec3(50, -10, 0));
        person1.addJoint(rightHand1, rightArm1);

        Joint *head1 = new Joint("head1");
        head1->setLocalTranslation(vec3(0, 0, 0));
        person1.addJoint(head1, chest1);

        person1.fk(); // compute local2global transforms

        // person 2 (red)
        Joint *root = new Joint("root");
        root->setLocalTranslation(vec3(0, 120, 0));
        person2.addJoint(root);

        Joint *leftT = new Joint("leftT");
        leftT->setLocalTranslation(vec3(-20, -50, 0));
        person2.addJoint(leftT, root);

        Joint *rightT = new Joint("rightT");
        rightT->setLocalTranslation(vec3(20, -50, 0));
        person2.addJoint(rightT, root);

        Joint *leftLeg = new Joint("leftLeg");
        leftLeg->setLocalTranslation(vec3(-5, -70, 0));
        person2.addJoint(leftLeg, leftT);

        Joint *rightLeg = new Joint("rightLeg");
        rightLeg->setLocalTranslation(vec3(5, -70, 0));
        person2.addJoint(rightLeg, rightT);

        Joint *abdomen = new Joint("abdomen");
        abdomen->setLocalTranslation(vec3(0, 50, 0));
        person2.addJoint(abdomen, root);

        Joint *chest = new Joint("chest");
        chest->setLocalTranslation(vec3(0, 30, 0));
        person2.addJoint(chest, abdomen);

        Joint *leftArm = new Joint("leftArm");
        leftArm->setLocalTranslation(vec3(-50, -10, 0));
        person2.addJoint(leftArm, abdomen);

        Joint *rightArm = new Joint("rightArm");
        rightArm->setLocalTranslation(vec3(50, -10, 0));
        person2.addJoint(rightArm, abdomen);

        Joint *leftHand = new Joint("leftHand");
        leftHand->setLocalTranslation(vec3(-50, -10, 0));
        person2.addJoint(leftHand, leftArm);

        Joint *rightHand = new Joint("rightHand");
        rightHand->setLocalTranslation(vec3(50, -10, 0));
        person2.addJoint(rightHand, rightArm);

        Joint *head = new Joint("head");
        head->setLocalTranslation(vec3(0, 0, 0));
        person2.addJoint(head, chest);

        person2.fk();
    }

    virtual void scene()
    {
        person1.fk(); // computes local2global transforms
        setColor(vec3(0, 0, 1));

        Joint *root1 = person1.getByID(0);
        vec3 globalPos = root1->getGlobalTranslation();
        drawSphere(globalPos, 15);

        for (int i = 1; i < person1.getNumJoints(); i++)
        {
            Joint *child = person1.getByID(i);
            if (child->getName() == "head1")
            {
                drawSphere(child->getGlobalTranslation(), 25);
                break;
            }
            Joint *parent = child->getParent();
            vec3 globalParentPos = parent->getGlobalTranslation();
            vec3 globalPos = child->getGlobalTranslation();
            // animate tentacle
            quat animate = glm::angleAxis(sin(elapsedTime() * i/2), vec3(0, 1, 0));
            child->setLocalRotation(animate);
            drawEllipsoid(globalParentPos, globalPos, 10);
        }

        // person 2
        person2.fk(); // computes local2global transforms
        setColor(vec3(1, 0, 0));

        vec3 distance = vec3(0,0,30);

        Joint *root2 = person2.getByID(0);
        vec3 globalPos2 = root2->getGlobalTranslation();
        drawSphere(globalPos2+ distance, 15);

        for (int i = 1; i < person2.getNumJoints(); i++)
        {
            Joint *child2 = person2.getByID(i);
            if (child2->getName() == "head")
            {
                drawSphere(child2->getGlobalTranslation()+ distance, 25);
                break;
            }
            Joint *parent2 = child2->getParent();
            vec3 globalParentPos2 = parent2->getGlobalTranslation();
            vec3 globalPos2 = child2->getGlobalTranslation();
            // animate tentacle
            quat animate2 = glm::angleAxis(sin(elapsedTime() * i/2), vec3(0, 1, 0));
            child2->setLocalRotation(animate2);
            drawEllipsoid(globalParentPos2 + distance, globalPos2 + distance, 10);
        }
    }

protected:
    Skeleton person1;
    Skeleton person2;
};

int main(int argc, char **argv)
{
    Unique viewer;
    viewer.run();
}
