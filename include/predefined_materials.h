/* This header contains predefined Material objects. The current list of materials available are:
 * 1. White
 * 2. Black
 * 3. Blue
 * 4. Red
 * 5. Green
 * 6. Yellow
 * 7. Grey
 * 8. Orange
 * 9. Brown
 *
 * The intent is to ease the workload while prototyping URDF files by providing predefined colours. If this library was of use to
 * you please consider citing or giving credits to the author */

#pragma once

#include "run_conversion.h"

namespace predefined_materials{

    Material white(std::ofstream* filepointer){
        Material White(filepointer);
        White.setMaterialNameAndRGBA("White",1.0,1.0,1.0,1.0);
        return White;
    }

    Material black(std::ofstream* filepointer){
        Material Black(filepointer);
        Black.setMaterialNameAndRGBA("Black",0,0,0,1);
        return Black;
    }

    Material blue(std::ofstream* filepointer){
        Material Blue(filepointer);
        Blue.setMaterialNameAndRGBA("Blue",0,0,0.8,1.0);
        return Blue;
    }

    Material red(std::ofstream* filepointer){
        Material Red(filepointer);
        Red.setMaterialNameAndRGBA("Red",1,0,0,1);
        return Red;
    }

    Material green(std::ofstream* filepointer){
        Material Green(filepointer);
        Green.setMaterialNameAndRGBA("Green",0,1,0,1);
        return Green;
    }

    Material yellow(std::ofstream* filepointer){
        Material Yellow(filepointer);
        Yellow.setMaterialNameAndRGBA("Yellow",1,1,0,1);
        return Yellow;
    }

    Material grey(std::ofstream* filepointer) {
        Material Grey(filepointer);
        Grey.setMaterialNameAndRGBA("Grey",0.5, 0.5, 0.5, 1.0);
        return Grey;
    }

    Material orange(std::ofstream* filepointer){
        Material Orange(filepointer);
        Orange.setMaterialNameAndRGBA("Orange", 1.0, 0.423529, 0.039215, 1.0);
        return Orange;
    }

    Material brown(std::ofstream* filepointer){
        Material Brown(filepointer);
        Brown.setMaterialNameAndRGBA("Brown", 0.87058, 0.811764, 0.76470, 1.0);
        return Brown;
    }
}