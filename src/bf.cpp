#include <cstdio>
#include <cmath>
#include "../include/bf.h"

bf::bf(const char *img_path) {
    FILE *bitmap = fopen(img_path, "rb");
    init_data(bitmap);
    fclose(bitmap);
}

bf::bf(const bf &obj) {
    BITMAPFILEHEADER = obj.BITMAPFILEHEADER;
    BITMAPINFOHEADER = obj.BITMAPINFOHEADER;
    COLORPALETTE = new int*[(BITMAPFILEHEADER.bfOffBits - 54) / 4];
    for (int i = 0; i < (BITMAPFILEHEADER.bfOffBits - 54) / 4; i++) {
        COLORPALETTE[i] = new int[4];
        for (int j = 0; j < 4; j++)
            COLORPALETTE[i][j] = obj.COLORPALETTE[i][j];
    }
    BITMAPDATA = new int*[BITMAPINFOHEADER.biHeight];
    for (int i = 0; i < BITMAPINFOHEADER.biHeight; i++) {
        BITMAPDATA[i] = new int[BITMAPINFOHEADER.biWidth];
        for (int j = 0; j < BITMAPINFOHEADER.biWidth; j++)
            BITMAPDATA[i][j] = obj.BITMAPDATA[i][j];
    }

}

bf::~bf() {
    for (int i = 0; i < (BITMAPFILEHEADER.bfOffBits - 54) / 4; i++) {
        delete[] COLORPALETTE[i];
    }
    delete[] COLORPALETTE;
    for (int i = 0; i < BITMAPINFOHEADER.biHeight; i++) {
        delete[] BITMAPDATA[i];
    }
    delete[] BITMAPDATA;
}

int **bf::getBITMAPDATA() const {
    return BITMAPDATA;
}

int bf::getHeight() const {
    return BITMAPINFOHEADER.biHeight;
}

int bf::getWidth() const {
    return BITMAPINFOHEADER.biWidth;
}

int bf::getLevel() const {
    return (int)pow(2, BITMAPINFOHEADER.biBitCount);
}

void bf::setBITMAPDATA(int **data) {
    for (int i = 0; i < BITMAPINFOHEADER.biHeight; i++)
        delete[] BITMAPDATA[i];
    delete[] BITMAPDATA;
    BITMAPDATA = data;
}

void bf::setHeight(int h) {
    BITMAPINFOHEADER.biHeight = h;
}

void bf::setWidth(int w) {
    BITMAPINFOHEADER.biWidth = w;
}

void bf::setBfSize(int s) {
    BITMAPFILEHEADER.bfSize = s;
}

void bf::setBiSizeImage(int s) {
    BITMAPINFOHEADER.biSizeImage = s;
}

void bf::init_data(FILE *bitmap) {
    fread(&BITMAPFILEHEADER.bfType, 1, 2, bitmap);
    fread(&BITMAPFILEHEADER.bfSize, 1, 4, bitmap);
    fread(&BITMAPFILEHEADER.bfReserved1, 1, 2, bitmap);
    fread(&BITMAPFILEHEADER.bfReserved2, 1, 2, bitmap);
    fread(&BITMAPFILEHEADER.bfOffBits, 1, 4, bitmap);

    fread(&BITMAPINFOHEADER.biSize, 1, 4, bitmap);
    fread(&BITMAPINFOHEADER.biWidth, 1, 4, bitmap);
    fread(&BITMAPINFOHEADER.biHeight, 1, 4, bitmap);
    fread(&BITMAPINFOHEADER.biPlanes, 1, 2, bitmap);
    fread(&BITMAPINFOHEADER.biBitCount, 1, 2, bitmap);
    fread(&BITMAPINFOHEADER.biCompression, 1, 4, bitmap);
    fread(&BITMAPINFOHEADER.biSizeImage, 1, 4, bitmap);
    fread(&BITMAPINFOHEADER.biXPelsPerMeter, 1, 4, bitmap);
    fread(&BITMAPINFOHEADER.biYPelsPerMeter, 1, 4, bitmap);
    fread(&BITMAPINFOHEADER.biClrUsed, 1, 4, bitmap);
    fread(&BITMAPINFOHEADER.biClrImportant, 1, 4, bitmap);

    if (BITMAPFILEHEADER.bfOffBits != 54) {
        COLORPALETTE = new int*[(BITMAPFILEHEADER.bfOffBits - 54) / 4];
        for (int i = 0; i < (BITMAPFILEHEADER.bfOffBits - 54) / 4; i++) {
            COLORPALETTE[i] = new int[4];
            for (int j = 0; j < 4; j++)
                fread(&(COLORPALETTE[i][j]), 1, 1, bitmap);
        }
    }

    BITMAPDATA = new int*[BITMAPINFOHEADER.biHeight];
    for (int i = 0; i < BITMAPINFOHEADER.biHeight; i++) {
        BITMAPDATA[i] = new int[BITMAPINFOHEADER.biWidth];
        for (int j = 0; j < BITMAPINFOHEADER.biWidth; j++)
            fread(&(BITMAPDATA[i][j]), 1, BITMAPINFOHEADER.biBitCount / 8, bitmap);
    }
}

void bf::output(const char *img_path) {
    FILE *output = fopen(img_path, "wb");

    fwrite(&BITMAPFILEHEADER.bfType, 1, 2, output);
    fwrite(&BITMAPFILEHEADER.bfSize, 1, 4, output);
    fwrite(&BITMAPFILEHEADER.bfReserved1, 1, 2, output);
    fwrite(&BITMAPFILEHEADER.bfReserved2, 1, 2, output);
    fwrite(&BITMAPFILEHEADER.bfOffBits, 1, 4, output);

    fwrite(&BITMAPINFOHEADER.biSize, 1, 4, output);
    fwrite(&BITMAPINFOHEADER.biWidth, 1, 4, output);
    fwrite(&BITMAPINFOHEADER.biHeight, 1, 4, output);
    fwrite(&BITMAPINFOHEADER.biPlanes, 1, 2, output);
    fwrite(&BITMAPINFOHEADER.biBitCount, 1, 2, output);
    fwrite(&BITMAPINFOHEADER.biCompression, 1, 4, output);
    fwrite(&BITMAPINFOHEADER.biSizeImage, 1, 4, output);
    fwrite(&BITMAPINFOHEADER.biXPelsPerMeter, 1, 4, output);
    fwrite(&BITMAPINFOHEADER.biYPelsPerMeter, 1, 4, output);
    fwrite(&BITMAPINFOHEADER.biClrUsed, 1, 4, output);
    fwrite(&BITMAPINFOHEADER.biClrImportant, 1, 4, output);

    for (int i = 0; i < (BITMAPFILEHEADER.bfOffBits - 54) / 4; i++) {
        for (int j = 0; j < 4; j++)
            fwrite(&(COLORPALETTE[i][j]), 1, 1, output);
    }

    for (int i = 0; i < BITMAPINFOHEADER.biHeight; i++) {
        int a_width = ceil(BITMAPINFOHEADER.biWidth / 4.0) * 4;
        for (int j = 0; j < a_width; j++)
            fwrite(&(BITMAPDATA[i][j]), 1, BITMAPINFOHEADER.biBitCount / 8, output);
    }

    // 2-Byte zero to align for header.
    fwrite(&BITMAPFILEHEADER.bfReserved2, 1, 2, output);

    fclose(output);
}