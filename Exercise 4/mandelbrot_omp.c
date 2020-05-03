#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <omp.h>

/* picture resolution */
static const int ImageWidth = 1024;
static const int ImageHeight = 1024;
static const double CxMin = -2.5;
static const double CxMax = 1.5;
static const double CyMin = -2.0;
static const double CyMax = 2.0;

int main()
{
    /* Precompute pixel width and height. */
    double PixelWidth = (CxMax - CxMin) / ImageWidth;
    double PixelHeight = (CyMax - CyMin) / ImageHeight;

    const int MaxColorComponentValue = 1 << 8;
    typedef unsigned char pixel_t[6];
    pixel_t *pixels = malloc(sizeof(pixel_t) * ImageHeight * ImageWidth);

    /* Open the file. */
    FILE *fp = fopen("MandelbrotSet.ppm", "wb");

    omp_set_dynamic(1);
    omp_set_num_threads(4);

#pragma omp parallel
    {
        /* Pixel counters */
        int i, j;
#pragma omp for schedule(dynamic)
        for (j = 0; j < ImageHeight; j++)
        {
            for (i = 0; i < ImageWidth; i++)
            {
                double Cx = CxMin + i * PixelWidth;
                double Cy = CyMin + j * PixelHeight;
                /* Coordinates of the iterated point. */
                double Zx = 0.0;
                double Zy = 0.0;
                double Zx2 = Zx * Zx;
                double Zy2 = Zy * Zy;
                /* */
                int n;
                /* Maximum number of iterations. */
                const int N = 5000;

                for (n = 0; n < N && ((Zx2 + Zy2) < 2 * 2); n++)
                {
                    Zy = 2 * Zx * Zy + Cy;
                    Zx = Zx2 - Zy2 + Cx;
                    Zx2 = Zx * Zx;
                    Zy2 = Zy * Zy;
                };
                /* compute  pixel color and write it to file */
                /* If finish loop, |Zn| < 2, put to Mandel_set*/
                if (n == N)
                {
                    /* interior */
                    pixels[j * ImageWidth + i][0] = 0;
                    pixels[j * ImageWidth + i][1] = 0;
                    pixels[j * ImageWidth + i][2] = 0;
                    pixels[j * ImageWidth + i][3] = 0;
                    pixels[j * ImageWidth + i][4] = 0;
                    pixels[j * ImageWidth + i][5] = 0;
                }
                //
                else
                {
                    /* exterior */
                    pixels[j * ImageWidth + i][0] = n & 255;
                    pixels[j * ImageWidth + i][1] = n & 255;
                    pixels[j * ImageWidth + i][2] = n & 255;
                    pixels[j * ImageWidth + i][3] = n & 255;
                    pixels[j * ImageWidth + i][4] = n & 255;
                    pixels[j * ImageWidth + i][5] = n & 255;
                }
            }
        }
    }

    /*write ASCII header to the file*/
    fprintf(fp, "P6\n %s\n %d\n %d\n %d\n", "# no comment", ImageWidth, ImageHeight, MaxColorComponentValue);
    for (int j = 0; j < ImageHeight; j++)
        for (int i = 0; i < ImageWidth; i++)
            fwrite(pixels[j * ImageWidth + i], 1, sizeof(pixel_t), fp);
    fclose(fp);
    free(pixels);
    return 0;
}