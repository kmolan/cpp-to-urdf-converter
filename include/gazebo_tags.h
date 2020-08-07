#pragma once

#include "run_conversion.h"

void setGazeboMaterial(std::ofstream* file, std::string material, Link link){
    *file << "  <gazebo reference = \""<< link.getName() << "\">\n";
    *file << "    <material>" << material << "</material>\n";
    *file << "  </gazebo>\n\n";
}