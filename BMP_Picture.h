#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<stdlib.h>
#include<memory.h>
#include<math.h>
using namespace std;

int BYTE_PER_PIXEL = 3; //记录格式为24位bmp格式，每个像素有3bytes 
int biClrMapBit = 0; //记录调色板位数 
char* IMAGE_NAME = "90.bmp"; //图片的文件名 

class BMP_Picture {
	private:
		char BMP_Head[14]; //记录bmp格式的文件头信息 
		char biSize[4];	//记录biSize信息 
		char biClrUsed[4];//调色板实际所用颜色索引数
		int height; //图片高的int表示 
		int width; // 图片宽的int表示 
		char h[4]; //图片高的char数组表示 
		char w[4]; //图片宽的char数组表示 
		char biPlanes_biMeter[20]; //记录bmp格式头中biPlanes到biMeter的信息 
		char biClrImportant[4]; //记录biClrImportant信息 
		char* biClrMap; //记录调色板
		char** bitMap; //---------------------记录像素矩阵--------------------------- 
		int externWidth; //记录像素矩阵每行保证为32位的倍数而补齐的位数 
	public:
		void ReadImage(char* imageName);
		void WriteImage(string fileName); 
		void CreateColorImage(); //将图片转化成彩图 
		void CreateOutlineImage(); //将图片转化为轮廓图 
		friend void MixColorAndOutline(BMP_Picture Color, BMP_Picture Outline); //将彩图与 
};
/*
bmp文件头  14Bytes
位图信息头 40Bytes
调色板 0bytes
位图数据 h X w bytes 
*/

void BMP_Picture::ReadImage(char* imageName) {
	ifstream imgF(imageName, ios::binary);
	if (!imgF) {
		cout << "Open error!" << endl;
		abort(); 
	}
	imgF.read(BMP_Head, 14);
	imgF.read(biSize, 4);
	imgF.read(w, 4);
	imgF.read(h, 4);
	imgF.read(biPlanes_biMeter, 20);
	imgF.read(biClrUsed, 4);
	imgF.read(biClrImportant, 4);
	//顺序化读取bmp文件的头54字节文件头 
	
	width = (int)(unsigned char)(w[3])<<24|(int)(unsigned char)(w[2])<<16|(int)(unsigned char)(w[1])<<8|(int)(unsigned char)(w[0]);
	height = (int)(unsigned char)(h[3])<<24|(int)(unsigned char)(h[2])<<16|(int)(unsigned char)(h[1])<<8|(int)(unsigned char)(h[0]);
	//将长和宽转化为int形式易于后面处理时的调用。
	externWidth = width * BYTE_PER_PIXEL - ((int)(width + 1) * BYTE_PER_PIXEL) / 4 * 4; //计算为补齐位图每一行为32位的整数而需要的byte数 
	bitMap = new char*[height];
	for (int i = 0; i < height; i++) {
		bitMap[i] = new char[width * BYTE_PER_PIXEL];
	}
	//申请位图空间 
	biClrMap = new char[biClrMapBit];
	imgF.read(biClrMap, biClrMapBit);  //读取调色板 
	
	for (int i = 0; i < height; i++) {
		imgF.read(bitMap[i], width * BYTE_PER_PIXEL);
	}
	//读取位图 
	imgF.close();
}
//读取图片信息 
void BMP_Picture::WriteImage(string fileName) {
	char *tempName = new char[fileName.length() + 1]; 
	fileName.copy(tempName, fileName.length(), 0);
	*(tempName + fileName.length()) = '\0';
	ofstream imgF(tempName, ios::binary);
	if(!imgF) {
		cout << "Write Open error!" << endl;
		abort();
	}
	
	imgF.write(BMP_Head, 14);
	imgF.write(biSize, 4);
	imgF.write(w, 4);
	imgF.write(h, 4);
	imgF.write(biPlanes_biMeter, 20);
	imgF.write(biClrUsed, 4);
	imgF.write(biClrImportant, 4);
	imgF.write(biClrMap, biClrMapBit);
	//顺序化写bmp文件的文件头54字节以及调色板的biClrMapBit字节 
	for (int i = 0; i < height; i++) {
		imgF.write(bitMap[i], width * BYTE_PER_PIXEL + externWidth);
	}
	//写bmp文件的位图信息 
	imgF.close();
}
//写图片信息 
