#include <cstdio>
#include <cmath>
#include "../include/bf.h"

bf::bf(const char *img_path) {
    FILE *bitmap = fopen(img_path, "rb");

    if (bitmap == 0) {
        printf("FILE NOT FOUND.[READ]\n");
        system("pause");
        return;
    }

    init_data(bitmap);
    fclose(bitmap);
}

bf::bf(const bf &obj) {
    BITMAPFILEHEADER = obj.BITMAPFILEHEADER;
    BITMAPINFOHEADER = obj.BITMAPINFOHEADER;
    COLORPALETTE = new int[(BITMAPFILEHEADER.bfOffBits - 54) / 4];
    for (int i = 0; i < (BITMAPFILEHEADER.bfOffBits - 54) / 4; i++) {
            COLORPALETTE[i] = obj.COLORPALETTE[i];
    }
    BITMAPDATA = new int[BITMAPINFOHEADER.biHeight * BITMAPINFOHEADER.biWidth];
    for (int i = 0; i < BITMAPINFOHEADER.biHeight * BITMAPINFOHEADER.biWidth; i++) {
            BITMAPDATA[i] = obj.BITMAPDATA[i];
    }

}

bf::~bf() {
    delete[] COLORPALETTE;
    delete[] BITMAPDATA;
}

int *bf::getBITMAPDATA() const {
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

void bf::setBITMAPDATA(int *data) {
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
        COLORPALETTE = new int[(BITMAPFILEHEADER.bfOffBits - 54) / 4];
        for (int i = 0; i < (BITMAPFILEHEADER.bfOffBits - 54) / 4; i++) {
            fread(&(COLORPALETTE[i]), 4, 1, bitmap);
        }
    }


    int total_pixel = BITMAPINFOHEADER.biHeight * BITMAPINFOHEADER.biWidth;
    int bytes_per_pixel = fmax(BITMAPINFOHEADER.biBitCount / 8, 1);
    int bytes_per_row = ceil(BITMAPINFOHEADER.biWidth * bytes_per_pixel / 4.0) * 4;
    BITMAPDATA = new int[total_pixel];
    for (int i = 0; i < total_pixel; i++) {
        if (i > 0 && i % BITMAPINFOHEADER.biWidth == 0)
            fseek(bitmap, bytes_per_row - BITMAPINFOHEADER.biWidth * bytes_per_pixel, SEEK_CUR);
        fread(&(BITMAPDATA[i]), bytes_per_pixel, 1, bitmap);
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
        fwrite(&(COLORPALETTE[i]), 4, 1, output);
    }

    int total_pixel = BITMAPINFOHEADER.biHeight * BITMAPINFOHEADER.biWidth;
    int bytes_per_pixel = fmax(BITMAPINFOHEADER.biBitCount / 8, 1);
    int bytes_per_row = ceil(BITMAPINFOHEADER.biWidth * bytes_per_pixel / 4.0) * 4;
    int zero = 0;
    for (int i = 0; i < total_pixel; i++) {
        fwrite(&(BITMAPDATA[i]), bytes_per_pixel, 1, output);
        if ((i + 1) % BITMAPINFOHEADER.biWidth == 0)
            fwrite(&(zero), bytes_per_row - BITMAPINFOHEADER.biWidth * bytes_per_pixel, 1, output);
    }

    // 2-Byte zero to align for header.
    fwrite(&BITMAPFILEHEADER.bfReserved2, 1, 2, output);

    fclose(output);
}