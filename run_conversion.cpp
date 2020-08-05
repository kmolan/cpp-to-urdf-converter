#include <iostream>
#include <fstream>
#include "run_conversion.h"

#define filename "test.urdf"

int main () {

    std::ofstream target_file (filename);

    Robot robot;

    Link foreaft_constraint_element(&target_file);
    Link pitch_constraint_element(&target_file);

    Material grey_material(&target_file);

    Joint foreaft_joint(&target_file);

    try {

        robot.beginURDF(filename, &target_file);
        robot.openRobotAndSetName("pendulum");

        grey_material.setMaterialName("Grey");
        grey_material.setRGBA(0.4,0.4,0.4,1);

        foreaft_constraint_element.setName("foreaft_constraint_element");
        foreaft_constraint_element.openVisual();
        foreaft_constraint_element.setVisualOrigin(0,0,0,0,0,0);
        foreaft_constraint_element.setVisualGeometry("box", 0.5, 0.5, 0.5);
        foreaft_constraint_element.finalizeVisual();
        foreaft_constraint_element.openCollision();
        foreaft_constraint_element.setCollisionOrigin(0,0,0,0,0,0);
        foreaft_constraint_element.setCollisionGeometry("box",0.5,0.5,0.5);
        foreaft_constraint_element.finalizeCollision();
        foreaft_constraint_element.openInertial();
        foreaft_constraint_element.setInertialMass(1.0);
        foreaft_constraint_element.setInertialTensor(0.1,0.1,0,0,0.1,0.1);
        foreaft_constraint_element.finalizeInertial();
        foreaft_constraint_element.finalizeLink();

        pitch_constraint_element.setName("pitch_constraint_element");
        pitch_constraint_element.finalizeLink();

        foreaft_joint.SetNameAndType("foreaft");
        foreaft_joint.setOrigin(0,0,0,0,0,0);
        foreaft_joint.setAxis(1,0,0);
        foreaft_joint.setChildLink(foreaft_constraint_element);
        foreaft_joint.setParentLink(pitch_constraint_element);
        foreaft_joint.setLimits();
        foreaft_joint.finalizeJoint();

        robot.finalizeRobot();
    }
    catch(const char* msg){
        std::cerr << msg << std::endl;
    }

    target_file.close();

    return 0;
}