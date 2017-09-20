#include"BMP_Picture.h"

int main() {
	BMP_Picture bmp;
	string fileName = "result.bmp";
	bmp.ReadImage(IMAGE_NAME);
	bmp.WriteImage(fileName);
	return 0;
} 
