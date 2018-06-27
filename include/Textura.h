#ifndef TEXTURA_H
#define TEXTURA_H


#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdio.h>
#include <stdlib.h>

class Textura
{
    public:
        Textura();
        virtual ~Textura();
        int num_texture;
        int LoadBitmap(char *filename);
        typedef struct                       /**** BMP file info structure ****/
            {
            unsigned int   biSize;           /* Size of info header */
            int            biWidth;          /* Width of image */
            int            biHeight;         /* Height of image */
            unsigned short biPlanes;         /* Number of color planes */
            unsigned short biBitCount;       /* Number of bits per pixel */
            unsigned int   biCompression;    /* Type of compression to use */
            unsigned int   biSizeImage;      /* Size of image data */
            int            biXPelsPerMeter;  /* X pixels per meter */
            int            biYPelsPerMeter;  /* Y pixels per meter */
            unsigned int   biClrUsed;        /* Number of colors used */
            unsigned int   biClrImportant;   /* Number of important colors */
            char *data;
            } BITMAPINFOHEADER;
    protected:

    private:
};

#endif // TEXTURA_H
