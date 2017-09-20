#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<stdlib.h>
#include<memory.h>
#include<math.h>
using namespace std;

int BYTE_PER_PIXEL = 3; //��¼��ʽΪ24λbmp��ʽ��ÿ��������3bytes 
int biClrMapBit = 0; //��¼��ɫ��λ�� 
char* IMAGE_NAME = "90.bmp"; //ͼƬ���ļ��� 

class BMP_Picture {
	private:
		char BMP_Head[14]; //��¼bmp��ʽ���ļ�ͷ��Ϣ 
		char biSize[4];	//��¼biSize��Ϣ 
		char biClrUsed[4];//��ɫ��ʵ��������ɫ������
		int height; //ͼƬ�ߵ�int��ʾ 
		int width; // ͼƬ���int��ʾ 
		char h[4]; //ͼƬ�ߵ�char�����ʾ 
		char w[4]; //ͼƬ���char�����ʾ 
		char biPlanes_biMeter[20]; //��¼bmp��ʽͷ��biPlanes��biMeter����Ϣ 
		char biClrImportant[4]; //��¼biClrImportant��Ϣ 
		char* biClrMap; //��¼��ɫ��
		char** bitMap; //---------------------��¼���ؾ���--------------------------- 
		int externWidth; //��¼���ؾ���ÿ�б�֤Ϊ32λ�ı����������λ�� 
	public:
		void ReadImage(char* imageName);
		void WriteImage(string fileName); 
		void CreateColorImage(); //��ͼƬת���ɲ�ͼ 
		void CreateOutlineImage(); //��ͼƬת��Ϊ����ͼ 
		friend void MixColorAndOutline(BMP_Picture Color, BMP_Picture Outline); //����ͼ�� 
};
/*
bmp�ļ�ͷ  14Bytes
λͼ��Ϣͷ 40Bytes
��ɫ�� 0bytes
λͼ���� h X w bytes 
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
	//˳�򻯶�ȡbmp�ļ���ͷ54�ֽ��ļ�ͷ 
	
	width = (int)(unsigned char)(w[3])<<24|(int)(unsigned char)(w[2])<<16|(int)(unsigned char)(w[1])<<8|(int)(unsigned char)(w[0]);
	height = (int)(unsigned char)(h[3])<<24|(int)(unsigned char)(h[2])<<16|(int)(unsigned char)(h[1])<<8|(int)(unsigned char)(h[0]);
	//�����Ϳ�ת��Ϊint��ʽ���ں��洦��ʱ�ĵ��á�
	externWidth = width * BYTE_PER_PIXEL - ((int)(width + 1) * BYTE_PER_PIXEL) / 4 * 4; //����Ϊ����λͼÿһ��Ϊ32λ����������Ҫ��byte�� 
	bitMap = new char*[height];
	for (int i = 0; i < height; i++) {
		bitMap[i] = new char[width * BYTE_PER_PIXEL];
	}
	//����λͼ�ռ� 
	biClrMap = new char[biClrMapBit];
	imgF.read(biClrMap, biClrMapBit);  //��ȡ��ɫ�� 
	
	for (int i = 0; i < height; i++) {
		imgF.read(bitMap[i], width * BYTE_PER_PIXEL);
	}
	//��ȡλͼ 
	imgF.close();
}
//��ȡͼƬ��Ϣ 
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
	//˳��дbmp�ļ����ļ�ͷ54�ֽ��Լ���ɫ���biClrMapBit�ֽ� 
	for (int i = 0; i < height; i++) {
		imgF.write(bitMap[i], width * BYTE_PER_PIXEL + externWidth);
	}
	//дbmp�ļ���λͼ��Ϣ 
	imgF.close();
}
//дͼƬ��Ϣ 
