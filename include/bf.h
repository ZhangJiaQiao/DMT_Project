#ifndef BF_IMG
#define BF_IMG

#include <cstdio>

class bf {
private:
    struct {
        int bfType;
        int bfSize;
        int bfReserved1;
        int bfReserved2;
        int bfOffBits;
    } BITMAPFILEHEADER;

    struct {
        int biSize;
        int biWidth;
        int biHeight;
        int biPlanes;
        int biBitCount;
        int biCompression;
        int biSizeImage;
        int biXPelsPerMeter;
        int biYPelsPerMeter;
        int biClrUsed;
        int biClrImportant;
    } BITMAPINFOHEADER;  // For windows format.

    int **COLORPALETTE;

    int **BITMAPDATA;

    void init_data(FILE *bitmap);

public:
    bf(const char *img_path);
    bf(const bf &obj);
    ~bf();

    int **getBITMAPDATA() const;
    int getHeight() const;
    int getWidth() const;
    int getLevel() const;

    void setBITMAPDATA(int **data);
    void setHeight(int h);
    void setWidth(int w);
    void setBfSize(int s);
    void setBiSizeImage(int s);

    void output(const char *img_path);
};

#endif // !BF_IMG
