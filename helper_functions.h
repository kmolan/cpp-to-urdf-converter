/* Header with helper functions for the common variant of urdf specifications*/

#pragma once

namespace helper_functions {
    const void setOriginHelper(float roll, float pitch, float yaw, float x, float y, float z, std::ofstream *filepointer){
        *filepointer << "\t\t\t<origin rpy = \"" << roll << " " << pitch << " " << yaw << "\" xyz= \"" << x << " " << y << " "
                     << z << "\"/>\n";
    }

    const void setGeometryHelperBox(float l, float b, float h, std::ofstream *filepointer) {
        *filepointer << "\t\t\t<geometry>\n";
        *filepointer << "\t\t\t\t<" << "box" << " size=\"" << l << " " << b << " " << h << "\"/>\n";
        *filepointer << "\t\t\t</geometry>\n";
    }

    const void setGeometryHelperCylinder(float l, float r, std::ofstream *filepointer) {
        *filepointer << "\t\t\t<geometry>\n";
        *filepointer << "\t\t\t\t<" << "cylinder" << " length=\"" << l << "\" radius = \"" << r << "\"/>\n";
        *filepointer << "\t\t\t</geometry>\n";
    }

    const void setGeometryHelperSphere(float r, std::ofstream *filepointer) {
        *filepointer << "\t\t\t<geometry>\n";
        *filepointer << "\t\t\t\t<" << "sphere" << " radius=\"" << r << "\"/>\n";
        *filepointer << "\t\t\t</geometry>\n";
    }

    const void setGeometryHelperMesh(const std::string& meshfilename, std::ofstream *filepointer) {
        *filepointer << "\t\t\t<geometry>\n";
        *filepointer << "\t\t\t\t<mesh filename=\"" << meshfilename << "\"/>\n";
        *filepointer << "\t\t\t</geometry>\n";
    }
}