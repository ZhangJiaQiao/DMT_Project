#ifndef BF_IMG
#define BF_IMG

#include <cstdio>

class bf {
/*  A memory copy of a bitmap image file.

    This class stores both header and body
    information completely of a bitmap image file
    with some simple access and I/O functions.
    Note that all matrices are stored in one-dimension
    arrays. Maybe reload functions can be written to
    simplify the pixel-wide access operations in the future.
*/
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

    /*  COLORPALETTE is an array of int, whose single element
        represents a color with four-byte information (B, G, R
        and alpha, order from rightmost(LSB) to leftmost(MSB))
    */
    int *COLORPALETTE;

    /*  BITMAPDATA is an array of int, whose single element
        represents a single pixel of the bitmap. You can
        access a pixel in row i, col j (start from 0) like
        BITMAPDATA[i * width + j]
    */
    int *BITMAPDATA;

    void init_data(FILE *bitmap);

public:
    bf(const char *img_path);
    bf(const bf &obj);
    ~bf();

    int *getBITMAPDATA() const;
    int getHeight() const;
    int getWidth() const;
    int getLevel() const;

    void setBITMAPDATA(int *data);
    void setHeight(int h);
    void setWidth(int w);
    void setBfSize(int s);
    void setBiSizeImage(int s);

    void output(const char *img_path);
};

#endif // !BF_IMG
