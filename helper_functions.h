#pragma once

namespace helper_functions {
    void setOriginHelper(float roll, float pitch, float yaw, float x, float y, float z, std::ofstream *filepointer) {
        *filepointer << "\t\t\t<origin rpy = \"" << roll << " " << pitch << " " << yaw << "\" xyz= \"" << x << " " << y << " "
                     << z << "\"/>\n";
    }

    void setGeometryHelper(const std::string& type, float l, float b, float h, std::ofstream *filepointer) {
        *filepointer << "\t\t\t<geometry>\n";
        *filepointer << "\t\t\t\t<" << type << " size=\"" << l << " " << b << " " << h << "\"/>\n";
        *filepointer << "\t\t\t</geometry>\n";
    }
}