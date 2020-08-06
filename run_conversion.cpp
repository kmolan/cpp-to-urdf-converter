#include <iostream>
#include "run_conversion.h"

#define filename "test.urdf"

int main () {
    std::ofstream target_file (filename);
    Robot robot;
    Link base_link(&target_file), pendulum_link_1(&target_file);
    Joint pendulum_joint_1(&target_file);
    Material blue_material(&target_file), red_material(&target_file), green_material(&target_file), yellow_material(&target_file), grey_material(&target_file);

    try {
        robot.beginURDF(&target_file);
        robot.openRobotAndSetName("omnipointer");

        blue_material.setMaterialName("Blue");
        blue_material.setRGBA(0.0,0.0,0.8,1);
        blue_material.finalizeMaterial();

        red_material.setMaterialName("Red");
        red_material.setRGBA(1.0,0.0,0.0,1);
        red_material.finalizeMaterial();

        base_link.setName("base_link");
        base_link.openVisual();
        base_link.setVisualOrigin(0,0,0,0,0,0.05715);
        base_link.setVisualGeometry("box",0.1143,0.0545,0.1143);
        base_link.setVisualMaterial(red_material);
        base_link.finalizeVisual();
        base_link.openCollision();
        base_link.setCollisionOrigin(0,0,0,0,0,0.05715);
        base_link.setCollisionGeometry("box", 0.1143, 0.0545, 0.1143);
        base_link.finalizeCollision();
        base_link.openInertial();
        base_link.setInertialOrigin(0,0,0,0,0,0.05715);
        base_link.setInertialMass(0.2);
        base_link.setInertialTensor(0.000267245666667, 0, 0, 0.000435483, 0, 0.000267245666667);
        base_link.finalizeInertial();
        base_link.finalizeLink();

        pendulum_link_1.setName("pendulum_link_1");
        pendulum_link_1.openVisual();
        pendulum_link_1.setVisualOrigin(0,0,0,0,0,0.5);
        pendulum_link_1.setVisualGeometry("box", 0.0402, 0.05, 1);
        pendulum_link_1.setVisualMaterial(blue_material);
        pendulum_link_1.finalizeVisual();
        pendulum_link_1.openCollision();
        pendulum_link_1.setCollisionOrigin(0,0,0,0,0,0.5);
        pendulum_link_1.setCollisionGeometry("box", 0.0402, 0.05, 1);
        pendulum_link_1.finalizeCollision();
        pendulum_link_1.openInertial();
        pendulum_link_1.setInertialOrigin(0,0,0,0,0,0.5);
        pendulum_link_1.setInertialMass(1.0);
        pendulum_link_1.setInertialTensor(0.0835416666667, 0, 0, 0.0835416666667, 0, 0.000343003333333);
        pendulum_link_1.finalizeInertial();
        pendulum_link_1.finalizeLink();

        pendulum_joint_1.SetNameAndType("pendulum_joint_1", "continuous");
        pendulum_joint_1.setParentLink(base_link);
        pendulum_joint_1.setChildLink(pendulum_link_1);
        pendulum_joint_1.setLimits(2.5, 10000, -10000,10.0);
        pendulum_joint_1.setOrigin(0,0,0,0,0.05225,0.05715);
        pendulum_joint_1.setAxis(0,1,0);
        pendulum_joint_1.finalizeJoint();

        robot.finalizeRobot();
    }
    catch(const char* msg){
        std::cerr << msg << std::endl;
    }
    target_file.close();
    return 0;
}