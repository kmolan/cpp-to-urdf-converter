/* Header with helper functions for the common variant of urdf specifications*/

#pragma once

namespace helper_functions {
    const void setOriginHelper(float roll, float pitch, float yaw, float x, float y, float z, std::ofstream *filepointer){
        *filepointer << "   <origin rpy = \"" << roll << " " << pitch << " " << yaw << "\" xyz= \"" << x << " " << y << " "
                     << z << "\"/>\n";
    }

    const void setGeometryHelperBox(float l, float b, float h, std::ofstream *filepointer) {
        *filepointer << "   <geometry>\n";
        *filepointer << "    <" << "box" << " size=\"" << l << " " << b << " " << h << "\"/>\n";
        *filepointer << "   </geometry>\n";
    }

    const void setGeometryHelperCylinder(float l, float r, std::ofstream *filepointer) {
        *filepointer << "   <geometry>\n";
        *filepointer << "    <" << "cylinder" << " length=\"" << l << "\" radius = \"" << r << "\"/>\n";
        *filepointer << "   </geometry>\n";
    }

    const void setGeometryHelperSphere(float r, std::ofstream *filepointer) {
        *filepointer << "   <geometry>\n";
        *filepointer << "    <" << "sphere" << " radius=\"" << r << "\"/>\n";
        *filepointer << "   </geometry>\n";
    }

    const void setGeometryHelperMesh(const std::string& meshfilename, std::ofstream *filepointer) {
        *filepointer << "   <geometry>\n";
        *filepointer << "    <mesh filename=\"" << meshfilename << "\"/>\n";
        *filepointer << "   </geometry>\n";
    }
}