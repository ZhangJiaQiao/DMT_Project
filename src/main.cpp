#include "../include/bf.h"

const char *INPUT_IMG_PATH = "../res/samplePicture.bmp";
const char *OUTPUT_IMG_PATH = "../res/result.bmp";

int main() {
	bf bmp(INPUT_IMG_PATH);
    bmp.output(OUTPUT_IMG_PATH);
	return 0;
} 
