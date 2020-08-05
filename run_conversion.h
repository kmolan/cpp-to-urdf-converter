#pragma once

#include <fstream>
#include <string>
#include <unordered_set>
#include "helper_functions.h"

namespace global_list{
    std::unordered_set<std::string> list_of_links;
    std::unordered_set<std::string> list_of_joints;
    std::unordered_set<std::string> list_of_materials;
}

class Material {
public:
    Material(std::ofstream* file){
        filepointer = file;
    }

    void setMaterialName(std::string name){

        if(global_list::list_of_materials.count(name)){
            std::string error = "Redeclaration of material name " + name + " found. Please use a different name.";
            throw std::runtime_error(error);
        }

        global_list::list_of_joints.insert(name);
        material_name = name;
        *filepointer << "\t<material name = \"" + name + "\" > \n";

    }

    void setRGBA(float r, float g, float b, float a){
        *filepointer << "\t\t<color rgba =\"" << r << " "<< g << " " << b << " " << a << "\"/>\n";
        setColor = true;
    }

    void finalizeMaterial(){
        if(!setColor){
            std::string error = material_name + " must have a defined rgba value. Use .setRGBA() to set rgba values.";
            throw std::runtime_error(error);
        }
        *filepointer << "\t</material>\n\n";
    }

    std::string getName(){
        return material_name;
    }

private:
    std::ofstream* filepointer;
    bool setColor = false;
    std::string material_name;
};

class Link{
public:

    Link(std::ofstream* file){
        filepointer = file;
    }

    void setName(std::string name){
        checkIfFinalized();

        if(global_list::list_of_links.count(name)){
            std::string error = "Redeclaration of link name " + name + " found. Please use a different name.";
            throw std::runtime_error(error);
        }

        global_list::list_of_links.insert(name);
        linkname_ = name;
        setname = true;
        *filepointer << "\t<link name =\"" << name << "\"> \n";
    }

    void openVisual(){
        checkIfFinalized();
        *filepointer << "\t\t<visual>\n";
        visualtag = true;
    }

    void setVisualOrigin(float roll, float pitch, float yaw, float x, float y, float z){
        checkIfFinalized();
        checkifvisual();
        helper_functions::setOriginHelper(roll, pitch, yaw, x, y, z, filepointer);
    }

    void setVisualGeometry(std::string type, float l, float b, float h){ //TODO: THINK OF DIFF TYPES AND ARGUMENTS
        checkIfFinalized();
        checkifvisual();
        helper_functions::setGeometryHelper(type, l ,b , h, filepointer);
    }

    void setVisualMaterial(Material material){
        checkIfFinalized();
        checkifvisual();
        *filepointer << "\t\t\t<material name = \"" << material.getName() << "\"/>\n";
    }

    void finalizeVisual(){
        checkIfFinalized();
        *filepointer << "\t\t</visual>\n";
        visualtag = false;
    }

    void openCollision(){
        checkIfFinalized();
        *filepointer << "\t\t<collision>\n";
        collisiontag = true;
    }

    void setCollisionOrigin(float roll, float pitch, float yaw, float x, float y, float z){
        checkIfFinalized();
        checkifcollision();
        helper_functions::setOriginHelper(roll, pitch, yaw, x, y, z, filepointer);
    }

    void setCollisionGeometry(std::string type, float l, float b, float h){ //TODO: THINK OF DIFF TYPES AND ARGUMENTS
        checkIfFinalized();
        checkifcollision();
        helper_functions::setGeometryHelper(type, l ,b , h, filepointer);
    }

    void finalizeCollision(){
        checkIfFinalized();
        *filepointer << "\t\t</collision>\n";
        collisiontag = false;
    }

    void openInertial(){
        checkIfFinalized();
        *filepointer << "\t\t<inertial>\n";
        inertiatag = true;
    }

    void setInertialOrigin(float roll, float pitch, float yaw, float x, float y, float z){
        checkIfFinalized();
        checkifinertial();
        helper_functions::setOriginHelper(roll, pitch, yaw, x, y, z, filepointer);
    }

    void setInertialMass(float mass){
        checkIfFinalized();
        checkifinertial();
        *filepointer << "\t\t\t<mass value = \""<< mass << "\"/>\n";
    }

    void setInertialTensor(float ixx, float ixy, float ixz, float iyy, float iyz, float izz){
        checkIfFinalized();
        checkifinertial();
        if(!inertiatag) openInertial();
        *filepointer << "\t\t\t<inertia ixx = \""<<ixx << "\" ixy = \"" << ixy << "\" ixz = \"" << ixz << "\" iyy = \"" << iyy << "\" iyz = \"" << iyz << "\" izz = \"" << izz << "\"/>\n";
    }

    void finalizeInertial(){
        checkIfFinalized();
        *filepointer << "\t\t</inertial>\n";
        inertiatag = false;
    }

    void finalizeLink(){
        checkIfFinalized();
        if(visualtag){
            throw std::runtime_error("Visual tag must be closed before finalizing link. Use finalizeVisual() to close visual tag");
        }
        if(collisiontag){
            throw std::runtime_error("Collision tag must be closed before finalizing link. Use finalizeCollision() to close visual tag");
        }
        if(inertiatag){
            throw std::runtime_error("Inertial tag must be closed before finalizing link. Use finalizeInertial() to close visual tag");
        }
        *filepointer << "\t</link>\n\n";
        isLinkOpen = false;
    }

    std::string getName(){
        return linkname_;
    }

private:

    void checkIfFinalized(){
        if (!isLinkOpen){
            std::string error = "Changes cannot be made to the link " + linkname_ + " after it has been finalized";
            throw std::runtime_error(error);
        }
    }

    void checkifvisual(){
        if (!visualtag){
            std::string error = "Changes cannot be made to the visual tag of link " + linkname_ + " after it has been finalized";
            throw std::runtime_error(error);
        }
    }

    void checkifcollision(){
        if (!collisiontag){
            std::string error = "Changes cannot be made to the collision tag of link " + linkname_ + " after it has been finalized";
            throw std::runtime_error(error);
        }
    }

    void checkifinertial(){
        if (!inertiatag){
            std::string error = "Changes cannot be made to the inertial tag of link" + linkname_ + " after it has been finalized";
            throw std::runtime_error(error);
        }
    }

    std::ofstream* filepointer;
    std::string linkname_;
    bool setname = false;
    bool visualtag = false; /// < is the visual tag open
    bool collisiontag = false; ///< is the collision tag open
    bool inertiatag = false; ///< is the inertia tag open
    bool isLinkOpen = true; ///< is the link open
};

class Joint{
public:
    Joint(std::ofstream* file){
        filepointer = file;
    }

    void SetNameAndType(std::string name, std::string type = "fixed"){
        if(global_list::list_of_joints.count(name)){
            std::string error = "Redeclaration of joint name " + name + " found. Please use a different name.";
            throw std::runtime_error(error);
        }

        global_list::list_of_joints.insert(name);
        jointname_ = name;
        *filepointer << "\t<joint name = \"" << name <<"\" type = \""<< type << "\" > \n";
    }

    void setParentLink(Link parent){
        *filepointer << "\t\t<parent link = \"" << parent.getName() << "\" /> \n";
        setParent = true;
    }

    void setChildLink(Link child){
        *filepointer << "\t\t<child link = \"" << child.getName() << "\" /> \n";
        setChild = true;
    }

    void setAxis(int x = 0, int y = 0, int z = 0){
        *filepointer << "\t\t<axis xyz = \"" << x << " "<< y <<" "<< z << "\" /> \n";
    }

    void setOrigin(int roll, int pitch, int yaw, int x, int y, int z){
        helper_functions:: setOriginHelper(roll, pitch, yaw, x, y, z, filepointer);
    }

    void setLimits(float effort = 0.0, float upper = 10000.0, float lower = -10000.0, float velocity = 0.0){
        *filepointer << "\t\t<limit effort =\"" << effort << "\" lower = \"" << lower << "\" upper = \"" << upper << "\" velocity = \"" << velocity << "\" />\n";
    }

    void finalizeJoint(){

        if(!setParent || !setChild){
            std::string error = "Joint " + jointname_ + " must have a parent and child link declared.";
            throw std::runtime_error(error);
        }

        *filepointer << "\t</joint> \n\n";
    }

    std::string getName(){
        return  jointname_;
    }

private:
    std::ofstream* filepointer;
    std::string jointname_;
    bool setParent = false;
    bool setChild = false;
};

class Robot{
public:
    void beginURDF(std::string name, std::ofstream* file){
        filepointer = file;
        *filepointer << "<?xml version=\"1.0\" ?>\n\n";
        *filepointer << "<!-- | This document was custom generated using the cpp-to-urdf library. For more details visit https://github.com/kmolan/cpp-to-urdf-converter | -->\n";
        *filepointer << "<!-- | Do not edit this file by hand unless you know what you're doing                                                                          | -->\n\n\n";
    }

    void openRobotAndSetName(std::string name){
        robot_name = name;
        *filepointer << "<robot name=\""<< robot_name <<"\" xmlns:xacro=\"http://ros.org/wiki/xacro\">\n";
    }

    void finalizeRobot(){
        *filepointer << "</robot>\n";
    }

private:
    std::string robot_name;
    std::ofstream* filepointer;
};