#include "../include/bf.h"

const char *INPUT_IMG_PATH = "sample0.bmp";
const char *OUTPUT_IMG_PATH = "result.bmp";

int main() {
	bf bmp(INPUT_IMG_PATH);
    bmp.output(OUTPUT_IMG_PATH);
	return 0;
}