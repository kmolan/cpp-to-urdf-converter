#pragma once

#include <fstream>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>
#include "helper_functions.h"


/*!
 * namespace to store current list of links, joints and materials to prevent redeclaration of names
 */
namespace global_list{
    std::unordered_set<std::string> list_of_links; ///< Stores the name of all the declared links
    std::unordered_set<std::string> list_of_joints; ///< Stores the name of all the declared joints
    std::unordered_set<std::string> list_of_materials; ///< Stores the name of all the declared materials
}

/*!
 * Material object to define new materials
 */
class Material {
public:
    /*!
     * @brief default constructor for material class
     * @param file address of the std::ofstream object that is writing on the current urdf file
     */
    explicit Material(std::ofstream* file){
        filepointer = file;
    }

    /*!
     * @brief opens the material tag, specifies the material name and cross-checks if name already exists
     * @param name the name of the desired material
     */
    void setMaterialNameAndRGBA(const std::string& name, float r, float g, float b, float a){

        if(global_list::list_of_materials.count(name)){
            std::string error = "Redeclaration of material name " + name + " found. Please use a different name.";
            throw std::runtime_error(error);
        }

        global_list::list_of_joints.insert(name);
        material_name = name;
        *filepointer << "\t<material name = \"" + name + "\" > \n";
        *filepointer << "\t\t<color rgba =\"" << r << " "<< g << " " << b << " " << a << "\"/>\n";
        *filepointer << "\t</material>\n\n";
    }

    /*!
     * @brief returns the name of the material instance
     * @return name of the material instance
     */
    std::string getName(){
        return material_name;
    }

private:
    std::ofstream* filepointer; ///<Member variable to store file pointer of the urdf file
    std::string material_name; ///<Member variable to store the instance's name
};

/*!
 * Link object to define new links
 */
class Link{
public:

    /*!
     * @brief default constructor for the link object
     * @param file pointer to the current urdf file
     */
    explicit Link(std::ofstream* file){
        filepointer = file;
    }

    /*!
     * @brief begins the link tag and specifies link name, cross-checks to prevent redeclaration of link names
     * @param name desired link name
     */
    void setName(const std::string& name){
        checkIfFinalized(); //prevent using the function if link has been finalized
        if(global_list::list_of_links.count(name)){
            std::string error = "Redeclaration of link name " + name + " found. Please use a different name.";
            throw std::runtime_error(error);
        }

        global_list::list_of_links.insert(name);
        linkname_ = name;
        *filepointer << "\t<link name =\"" << name << "\"> \n";
    }

    /*!
     * @brief begins the visual tag
     */
    void openVisual(){
        checkIfFinalized(); //prevent using the function if link has been finalized
        *filepointer << "\t\t<visual>\n";
        visualtag = true;
    }

    /*!
     * @brief set origin for the visual tag
     * @param listOfOrigins std::vector containing the roll, pitch, yaw, x, y, z of the origin
     */
    void setVisualOrigin(const std::vector<float> listOfOrigins){
        checkIfFinalized(); //prevent using the function if link has been finalized
        checkifvisual(); //prevent using the function if visual tag has been finalized
        helper_functions::setOriginHelper(listOfOrigins[0], listOfOrigins[1], listOfOrigins[2], listOfOrigins[3], listOfOrigins[4], listOfOrigins[5], filepointer);
    }

    /*!
     * @brief set origin for the visual tag
     * @param listOfOrigins std::vector containing the roll, pitch, yaw, x, y, z of the origin
     */
    void setVisualOrigin(const std::vector<double> listOfOrigins){
        checkIfFinalized(); //prevent using the function if link has been finalized
        checkifvisual(); //prevent using the function if visual tag has been finalized
        helper_functions::setOriginHelper(listOfOrigins[0], listOfOrigins[1], listOfOrigins[2], listOfOrigins[3], listOfOrigins[4], listOfOrigins[5], filepointer);
    }

    /*!
     * @brief set a box geometry in the visual tag
     * @param length
     * @param breadth
     * @param height
     */
    const void setVisualGeometryBox(float length, float breadth, float height){
        checkIfFinalized(); //prevent using the function if link has been finalized
        checkifvisual(); //prevent using the function if visual tag has been finalized
        helper_functions::setGeometryHelperBox(length, breadth, height, filepointer);
    }

    /*!
     * @brief set a cylinder geometry in the visual tag
     * @param length
     * @param radius
     */
    const void setVisualGeometryCylinder(float length, float radius){
        checkIfFinalized(); //prevent using the function if link has been finalized
        checkifvisual(); //prevent using the function if visual tag has been finalized
        helper_functions::setGeometryHelperCylinder(length, radius, filepointer);
    }

    /*!
     * @brief set a sphere geometry in the visual tag
     * @param radius
     */
    const void setVisualGeometrySphere(float radius){
        checkIfFinalized(); //prevent using the function if link has been finalized
        checkifvisual(); //prevent using the function if visual tag has been finalized
        helper_functions::setGeometryHelperSphere(radius, filepointer);
    }

    /*!
     * @brief set geometry in visual tag using predefined meshes
     * @param meshfilename filename of the mesh
     */
    const void setVisualGeometryMesh(const std::string& meshfilename){
        checkIfFinalized(); //prevent using the function if link has been finalized
        checkifvisual(); //prevent using the function if visual tag has been finalized
        helper_functions::setGeometryHelperMesh(meshfilename, filepointer);
    }

    /*!
     * @brief add material in the visual tag
     * @param material instance of the Material object
     */
    void setVisualMaterial(Material material){
        checkIfFinalized(); //prevent using the function if link has been finalized
        checkifvisual(); //prevent using the function if visual tag has been finalized
        *filepointer << "\t\t\t<material name = \"" << material.getName() << "\"/>\n";
    }

    /*!
     * @brief close visual tag and prevent from making any further changes to tag
     */
    void finalizeVisual(){
        checkIfFinalized(); //prevent using the function if link has been finalized
        *filepointer << "\t\t</visual>\n";
        visualtag = false;
    }

    /*!
     * begin collision tag
     */
    void openCollision(){
        checkIfFinalized(); //prevent using the function if link has been finalized
        *filepointer << "\t\t<collision>\n";
        collisiontag = true;
    }

    /*!
     * @brief set origin for collision tag
     * @param listOfOrigins std::vector<> containing the roll, pitch, yaw, x, y, z of the origin
     */
    void setCollisionOrigin(const std::vector<float> listOfOrigins){
        checkIfFinalized(); //prevent using the function if link has been finalized
        checkifcollision(); //prevent using the function if collision tag has been finalized
        helper_functions::setOriginHelper(listOfOrigins[0], listOfOrigins[1], listOfOrigins[2], listOfOrigins[3], listOfOrigins[4], listOfOrigins[5], filepointer);
    }

    /*!
     * @brief set origin for collision tag
     * @param listOfOrigins std::vector<> containing the roll, pitch, yaw, x, y, z of the origin
     */
    void setCollisionOrigin(const std::vector<double> listOfOrigins){
        checkIfFinalized(); //prevent using the function if link has been finalized
        checkifcollision(); //prevent using the function if collision tag has been finalized
        helper_functions::setOriginHelper(listOfOrigins[0], listOfOrigins[1], listOfOrigins[2], listOfOrigins[3], listOfOrigins[4], listOfOrigins[5], filepointer);
    }

    /*!
     * @brief set a box geometry in the collision tag
     * @param length
     * @param breadth
     * @param height
     */
    const void setCollisionGeometryBox(float length, float breadth, float height){
        checkIfFinalized(); //prevent using the function if link has been finalized
        checkifcollision(); //prevent using the function if collision tag has been finalized
        helper_functions::setGeometryHelperBox(length , breadth , height, filepointer);
    }

    /*!
     * @brief set a cylinder geometry in the collision tag
     * @param length
     * @param radius
     */
    const void setCollisionGeometryCylinder(float length, float radius){
        checkIfFinalized(); //prevent using the function if link has been finalized
        checkifcollision(); //prevent using the function if collision tag has been finalized
        helper_functions::setGeometryHelperCylinder(length, radius, filepointer);
    }

    /*!
     * @brief set a sphere geometry in the collision tag
     * @param radius
     */
    const void setCollisionGeometrySphere(float radius){
        checkIfFinalized(); //prevent using the function if link has been finalized
        checkifcollision(); //prevent using the function if collision tag has been finalized
        helper_functions::setGeometryHelperSphere(radius, filepointer);
    }

    /*!
     * @brief set a mesh geometry in the collision tag
     * @param meshfilename
     */
    void setCollisionGeometryMesh(const std::string& meshfilename){
        checkIfFinalized(); //prevent using the function if link has been finalized
        checkifcollision(); //prevent using the function if collision tag has been finalized
        helper_functions::setGeometryHelperMesh(meshfilename, filepointer);
    }

    /*!
     * @brief close collision tag and prevent any further changes to the tag
     */
    void finalizeCollision(){
        checkIfFinalized(); //prevent using the function if link has been finalized
        *filepointer << "\t\t</collision>\n";
        collisiontag = false;
    }

    /*!
     * @brief begin inertial tag
     */
    void openInertial(){
        checkIfFinalized(); //prevent using the function if link has been finalized
        *filepointer << "\t\t<inertial>\n";
        inertiatag = true;
    }

    /*!
     * @brief set origin for inertial tag
     * @param listOfOrigins std::vector<> containing the roll, pitch, yaw, x, y, z of the origin
     */
    void setInertialOrigin(const std::vector<float> listOfOrigins){
        checkIfFinalized(); //prevent using the function if link has been finalized
        checkifinertial(); //prevent using the function if collision tag has been finalized
        helper_functions::setOriginHelper(listOfOrigins[0], listOfOrigins[1], listOfOrigins[2], listOfOrigins[3], listOfOrigins[4], listOfOrigins[5], filepointer);
    }

    /*!
     * @brief set origin for inertial tag
     * @param listOfOrigins std::vector<> containing the roll, pitch, yaw, x, y, z of the origin
     */
    void setInertialOrigin(const std::vector<double> listOfOrigins){
        checkIfFinalized(); //prevent using the function if link has been finalized
        checkifinertial(); //prevent using the function if collision tag has been finalized
        helper_functions::setOriginHelper(listOfOrigins[0], listOfOrigins[1], listOfOrigins[2], listOfOrigins[3], listOfOrigins[4], listOfOrigins[5], filepointer);
    }

    /*!
     * @brief set mass for the inertial tag
     * @param mass desired mass
     */
    void setInertialMass(const float mass){
        checkIfFinalized(); //prevent using the function if link has been finalized
        checkifinertial(); //prevent using the function if collision tag has been finalized
        *filepointer << "\t\t\t<mass value = \""<< mass << "\"/>\n";
    }

    /*!
     * @brief set the inertial tensor in the inertial tag
     * @param ixx
     * @param ixy
     * @param ixz
     * @param iyy
     * @param iyz
     * @param izz
     */
    const void setInertialTensor(float ixx, float ixy, float ixz, float iyy, float iyz, float izz){
        checkIfFinalized(); //prevent using the function if link has been finalized
        checkifinertial(); //prevent using the function if collision tag has been finalized
        if(!inertiatag) openInertial();
        *filepointer << "\t\t\t<inertia ixx = \""<<ixx << "\" ixy = \"" << ixy << "\" ixz = \"" << ixz << "\" iyy = \"" << iyy << "\" iyz = \"" << iyz << "\" izz = \"" << izz << "\"/>\n";
    }

    /*!
     * @brief close the inertial tag
     */
    void finalizeInertial(){
        checkIfFinalized(); //prevent using the function if link has been finalized
        *filepointer << "\t\t</inertial>\n";
        inertiatag = false;
    }

    /*!
     * @brief close the link and do error handling to ensure all other tags are closed
     */
    void finalizeLink(){
        checkIfFinalized(); //prevent using the function if link has been finalized

        //other checks
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

    /*!
     * @brief returns name of the object instance
     * @return name of the object instance
     */
    std::string getName(){
        return linkname_;
    }

private:

    /*!
     * @brief checks if the object link has been finalized
     */
    void checkIfFinalized(){
        if (!isLinkOpen){
            std::string error = "Changes cannot be made to the link " + linkname_ + " after it has been finalized";
            throw std::runtime_error(error);
        }
    }

    /*!
     * @brief checks if the visual tag has been finalized
     */
    void checkifvisual(){
        if (!visualtag){
            std::string error = "Changes cannot be made to the visual tag of link " + linkname_ + " after it has been finalized";
            throw std::runtime_error(error);
        }
    }

    /*!
     * @brief checks if the collision tag has been finalized
     */
    void checkifcollision(){
        if (!collisiontag){
            std::string error = "Changes cannot be made to the collision tag of link " + linkname_ + " after it has been finalized";
            throw std::runtime_error(error);
        }
    }

    /*!
     * checks if the inertial tag has been finalized
     */
    void checkifinertial(){
        if (!inertiatag){
            std::string error = "Changes cannot be made to the inertial tag of link" + linkname_ + " after it has been finalized";
            throw std::runtime_error(error);
        }
    }

    std::ofstream* filepointer; ///< Pointer to the urdf file writer
    std::string linkname_; ///< Name of the link instance
    bool visualtag = false; /// < is the visual tag open
    bool collisiontag = false; ///< is the collision tag open
    bool inertiatag = false; ///< is the inertia tag open
    bool isLinkOpen = true; ///< is the link open
};

/*!
 * @brief Joint object to define new joints
 */
class Joint{ //TODO: ADD CHECK SO USER CANNOT MODIFY AFTER JOINT HAS BEEN FINALIZED
public:
    /*!
     * @brief default construtor
     * @param file pointer to the urdf file writer
     */
    explicit Joint(std::ofstream* file){
        filepointer = file;
    }

    /*!
     * @brief begins joint tag, sets name of the joint and error handling for redeclaration of joint names
     * @param name desired name of the joint
     * @param type type of joint
     */
    void SetNameAndType(const std::string& name, const std::string& type = "fixed"){
        checkIfFinalized(); //prevent from using function if joint has been finalized
        if(global_list::list_of_joints.count(name)){
            std::string error = "Redeclaration of joint name " + name + " found. Please use a different name.";
            throw std::runtime_error(error);
        }

        global_list::list_of_joints.insert(name);
        jointname_ = name;
        *filepointer << "\t<joint name = \"" << name <<"\" type = \""<< type << "\" > \n";
    }

    /*!
     * @brief set the parent link of the joint
     * @param parent Link object instance of desired parent link
     */
    void setParentLink(Link parent){
        checkIfFinalized(); //prevent from using function if joint has been finalized
        *filepointer << "\t\t<parent link = \"" << parent.getName() << "\" /> \n";
        setParent = true;
    }

    /*!
     * @brief set the child link of the joint
     * @param child Link object instance of desired child link
     */
    void setChildLink(Link child){
        checkIfFinalized(); //prevent from using function if joint has been finalized
        *filepointer << "\t\t<child link = \"" << child.getName() << "\" /> \n";
        setChild = true;
    }

    /*!
     * @brief set axis of the joint
     * @param x
     * @param y
     * @param z
     */
    void setAxis(int x = 0, int y = 0, int z = 0){
        checkIfFinalized(); //prevent from using function if joint has been finalized
        *filepointer << "\t\t<axis xyz = \"" << x << " "<< y <<" "<< z << "\" /> \n";
    }

    /*!
     * @brief set origin of the joint
     * @param roll
     * @param pitch
     * @param yaw
     * @param x
     * @param y
     * @param z
     */
    void setOrigin(float roll, float pitch, float yaw, float x, float y, float z){
        checkIfFinalized(); //prevent from using function if joint has been finalized
        helper_functions:: setOriginHelper(roll, pitch, yaw, x, y, z, filepointer);
    }

    /*!
     * @brief set joint limits
     * @param effort
     * @param upper
     * @param lower
     * @param velocity
     */
    void setLimits(float effort = 0.0, float upper = 10000.0, float lower = -10000.0, float velocity = 0.0){
        checkIfFinalized(); //prevent from using function if joint has been finalized
        *filepointer << "\t\t<limit effort =\"" << effort << "\" lower = \"" << lower << "\" upper = \"" << upper << "\" velocity = \"" << velocity << "\" />\n";
    }

    /*!
     * @brief ends joint tag and does error handling
     */
    void finalizeJoint(){
        checkIfFinalized(); //prevent from using function if joint has been finalized
        if(!setParent || !setChild){
            std::string error = "Joint " + jointname_ + " must have a parent and child link declared.";
            throw std::runtime_error(error);
        }

        *filepointer << "\t</joint> \n\n";
        isFinalized = true;
    }

    /*!
     * @brief returns name of the joint instance
     * @return name of the joint instance
     */
    std::string getName(){
        return  jointname_;
    }

private:

    /*!
     * @brief checks if joint has been finalized
     */
    void checkIfFinalized(){
        if(isFinalized){
            std::string error = "Cannot make changes to joint " + jointname_ + " after it has been finalized";
            throw std::runtime_error(error);
        }
    }

    std::ofstream* filepointer; ///< pointer to the urdf file writer
    std::string jointname_; ///< Member variable to store name of the joint instance
    bool setParent = false; ///< flag to check if a parent has been assigned
    bool setChild = false; ///< flag to check if a child has been assigned
    bool isFinalized = false; ///< flag to check if joint has been finalized
};

/*!
 * @brief Robot class to define new robots and manage urdf files
 */
class Robot{
public:
    /*!
     * @brief starts the urdf file and writes preprocessing arguments
     * @param file pointer to the urdf file writer
     */
    void beginURDF(std::ofstream* file){
        filepointer = file;
        *filepointer << "<?xml version=\"1.0\" ?>\n\n";
        *filepointer << "<!-- | This document was custom generated using the cpp-to-urdf library. For more details visit https://github.com/kmolan/cpp-to-urdf-converter | -->\n";
        *filepointer << "<!-- | Do not edit this file by hand unless you know what you're doing                                                                          | -->\n\n\n";
    }

    /*!
     * @brief start the robot tag and set robot name
     * @param name desired name of the robot
     */
    void openRobotAndSetName(std::string name){
        robot_name = std::move(name);
        *filepointer << "<robot name=\""<< robot_name <<"\" xmlns:xacro=\"http://ros.org/wiki/xacro\">\n";
    }

    /*!
     * @brief close the robot tag
     */
    void finalizeRobot(){
        *filepointer << "</robot>\n";
    }

private:
    std::string robot_name; ///< name of the object instance
    std::ofstream* filepointer; ///< pointer of the current urdf file writer
};