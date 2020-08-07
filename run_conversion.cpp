#include "include/cpp-to-urdf.h"

#define filename "urdf/pendulum.urdf"

//TODO: colours not visible
int main () {

    std::ofstream target_file (filename);
    Robot robot;
    Link world(&target_file), base_part2(&target_file), arm(&target_file), arm_com(&target_file); //TODO: using target_file each time is getting annoying
    Joint base_weld(&target_file), theta(&target_file), arm_weld(&target_file);
    Transmission elbow_trans(&target_file);

    robot.beginURDF(&target_file);
    robot.openRobotAndSetName("pendulum");

    Material blue_material = predefined_materials::blue(&target_file);
    Material red_material = predefined_materials::red(&target_file);
    Material green_material = predefined_materials::green(&target_file);

    std::vector<float> listOfOrigins = {0, 0, 0, 0, 0, 0};
    world.setName("world");
    world.openInertial();
    world.setInertialOrigin(listOfOrigins);
    world.setInertialMass(0.01);
    world.setInertialTensor(0.01,0,0,0,0,0);
    world.finalizeInertial();
    world.finalizeLink();

    listOfOrigins = {0, 0, 0, 0, 0, 0.015};
    base_part2.setName("base_part2");
    base_part2.openInertial();
    base_part2.setInertialOrigin(listOfOrigins);
    base_part2.setInertialMass(1.0);
    base_part2.setInertialTensor(0,0,0,0,0,0);
    base_part2.finalizeInertial();
    base_part2.openVisual();
    base_part2.setVisualOrigin(listOfOrigins);
    base_part2.setVisualGeometrySphere(0.015);
    base_part2.setVisualMaterial(green_material);
    base_part2.finalizeVisual();
    base_part2.finalizeLink();

    base_weld.setNameAndType("base_weld", "fixed");
    base_weld.setParentLink(world);
    base_weld.setChildLink(base_part2);
    base_weld.setOrigin(0,0,0,0,0,1); //TODO FIX
    base_weld.finalizeJoint();

    listOfOrigins = {0,0,0,0,0,-0.5};
    arm.setName("arm");
    arm.openInertial();
    arm.setInertialOrigin(listOfOrigins);
    arm.setInertialMass(0.5);
    arm.setInertialTensor(0,0,0,0,0,0);
    arm.finalizeInertial();
    arm.openVisual();
    listOfOrigins = {0,0,0,0,0, -0.375};
    arm.setVisualOrigin(listOfOrigins); //TODO ADD OTHER METHODS OF IMPLEMENTATION
    arm.setVisualGeometryCylinder(0.75, 0.01);
    arm.setVisualMaterial(red_material);
    arm.finalizeVisual();
    arm.openCollision();
    arm.setCollisionOrigin(listOfOrigins);
    arm.setCollisionGeometryCylinder(0.75,0.01);
    arm.finalizeCollision();
    arm.finalizeLink();

    theta.setNameAndType("theta", "continuous"); //TODO: every class should have a begin and finalize???
    theta.setParentLink(base_part2);
    theta.setChildLink(arm);
    theta.setAxis(0,1,0);
    theta.setDynamics(0.5, 20);
    theta.finalizeJoint();

    listOfOrigins = {0,0,0,0,0, -0.5};
    arm_com.setName("arm_com");
    arm_com.openInertial();
    arm_com.setInertialOrigin(listOfOrigins);
    arm_com.setInertialMass(0.5);
    arm_com.setInertialTensor(0,0,0,0,0,0);
    arm_com.finalizeInertial();
    arm_com.openVisual();
    arm_com.setVisualOrigin(listOfOrigins);
    arm_com.setVisualGeometrySphere(0.025);
    arm_com.setVisualMaterial(blue_material);
    arm_com.finalizeVisual();
    arm_com.openCollision();
    arm_com.setCollisionOrigin(listOfOrigins);
    arm_com.setCollisionGeometrySphere(0.025);
    arm_com.finalizeCollision();
    arm_com.finalizeLink();

    arm_weld.setNameAndType("arm_weld", "fixed");
    arm_weld.setParentLink(arm);
    arm_weld.setChildLink(arm_com);
    arm_weld.finalizeJoint();

    elbow_trans.setNameAndType("elbow_trans", "SimpleTransmission");
    elbow_trans.setActuatorName("tau");
    elbow_trans.setJointName(theta);
    elbow_trans.setMechanicalReduction(1);
    elbow_trans.finalizeTransmission();

    setGazeboMaterial(&target_file, "Gazebo/Green", base_part2);
    setGazeboMaterial(&target_file, "Gazebo/Red", arm);
    setGazeboMaterial(&target_file, "Gazebo/Blue", arm_com);

    robot.finalizeRobot();

    target_file.close();

    return 0;
}