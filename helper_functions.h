#pragma once

namespace helper_functions {
    void setOriginHelper(float roll, float pitch, float yaw, float x, float y, float z, std::ofstream *filepointer) {
        *filepointer << "<origin rpy = \"" << roll << " " << pitch << " " << yaw << "\" xyz= \"" << x << " " << y << " "
                     << z << "\"/>\n";
    }

    void setGeometryHelper(std::string type, float l, float b, float h, std::ofstream *filepointer) {
        *filepointer << "<geometry>\n";
        *filepointer << "<" << type << "size=\"" << l << " " << b << " " << h << "\"/>\n";
        *filepointer << "</geometry\n";
    }
}