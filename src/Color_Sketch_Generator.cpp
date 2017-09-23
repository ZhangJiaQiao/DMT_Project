#include "../include/Color_Sketch_Generator.h"

Color_Sketch_Generator::Color_Sketch_Generator(bf *src) {
    image = src;
}

Color_Sketch_Generator::~Color_Sketch_Generator() {
    ;
}

bf *Color_Sketch_Generator::getBf() {
    return image;
}