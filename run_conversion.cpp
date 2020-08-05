#include <iostream>
#include <fstream>
#include "run_conversion.h"

#define filename "test.urdf"

int main () {

    std::ofstream target_file (filename);

    Link linkobj(&target_file);
    Link newlinkobj(&target_file);

    Material matobj(&target_file);

    Joint jointobj(&target_file);

    try {

        matobj.setMaterialName("Grey");
        matobj.setRGBA(0.4,0.4,0.4,1);

        linkobj.setName("foreaft_constraint_element");
        linkobj.Finalize();

        newlinkobj.setName("pitch_constraint_element");
        newlinkobj.Finalize();

        jointobj.SetNameAndType("foreaft");
        jointobj.setOrigin(0,0,0,0,0,0);
        jointobj.setAxis(1,0,0);
        jointobj.setChildLink(newlinkobj);
        jointobj.setParentLink(linkobj);
        jointobj.setLimits();
        jointobj.Finalize();
    }
    catch(const char* msg){
        std::cerr << msg << std::endl;
    }

    target_file.close();

    return 0;
}