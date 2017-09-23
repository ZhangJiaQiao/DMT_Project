#ifndef COLOR_SKETCH_GENERATOR
#define COLOR_SKETCH_GENERATOR

#include "bf.h"

class Color_Sketch_Generator {

/*  This class generates our final result.

    --- Overall Goal ---
    Implement two main functions, which generate
    color image and sketch image, respectively, to
    generate the final result.

    --- Week 1 Image Preprocess ---
    1. Implement the k-means algorithm.
    2. £¿£¿£¿£¿£¿£¿£¿£¿£¿£¿£¿£¿
*/

private:
    bf *image;

public:
    Color_Sketch_Generator(bf *src);
    ~Color_Sketch_Generator();

    bf *getBf();
};

#endif // !COLOR_SKETCH_GENERATOR
