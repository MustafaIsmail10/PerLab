#include <stdio.h>
#define RIDX(i, j, n) ((i) * (n) + (j))

typedef struct
{
    unsigned short red;
    unsigned short green;
    unsigned short blue;
} pixel;

char convolutionMustafaV1_descr[] = "Convolution: Mustafa v1";
void convolutionMustafaV1(int dim, pixel *src, pixel *ker, unsigned *dst)
{

    int i, j, k, l;

    for (i = 0; i < 16; i++)
    {
        dst[i] = 0;
    }
    pixel *kerPixel = ker;
    for (k = 0; k < 2; k++)
        for (l = 0; l < 2; l++, kerPixel++)
        {
            int red = kerPixel->red;
            int blue = kerPixel->blue;
            int green = kerPixel->green;

            for (i = 0; i < dim - 1; i++)
                for (j = 0; j < dim - 1; j++)
                {
                    pixel *srcPixel = src + RIDX((i + k), (j + l), dim);
                    int sum = srcPixel->red * red;
                    sum += srcPixel->green * green;
                    sum += srcPixel->blue * blue;
                    dst[RIDX(i, j, dim)] += sum;
                    // printf("k=%d l=%d i=%d j=%d****************************\n", k, l, i, j);
                    // for (int x = 0; x < (dim - 1); x++)
                    // {
                    //     for (int y = 0; y < (dim - 1); y++)
                    //     {
                    //         printf("%d  ", dst[x * (dim-1) + y]);
                    //     }
                    //     printf(" \n");
                    // }
                }
        }
}

char naive_conv_descr[] = "naive_conv: Naive baseline implementation";
void naive_conv(int dim, pixel *src, pixel *ker, unsigned *dst)
{
    int i, j, k, l;

    for (i = 0; i < dim - 2 + 1; i++)
        for (j = 0; j < dim - 2 + 1; j++)
        {
            dst[RIDX(i, j, dim)] = 0;
            for (k = 0; k < 2; k++)
                for (l = 0; l < 2; l++)
                {
                    dst[RIDX(i, j, dim)] += src[RIDX((i + k), (j + l), dim)].red * ker[RIDX(k, l, 2)].red;
                    dst[RIDX(i, j, dim)] += src[RIDX((i + k), (j + l), dim)].green * ker[RIDX(k, l, 2)].green;
                    dst[RIDX(i, j, dim)] += src[RIDX((i + k), (j + l), dim)].blue * ker[RIDX(k, l, 2)].blue;
                }
        }
}

int main()
{
    int dim = 4;
    unsigned int dst[16];
    pixel src[16];
    pixel ker[4];

    for (int i = 0; i < 16; i++)
    {

        src[i].red = i;
        src[i].green = i;
        src[i].blue = i;
    }

    for (int i = 0; i < 4; i++)
    {
        ker[i].red = i;
        ker[i].green = i;
        ker[i].blue = i;
    }

    naive_conv(dim, src, ker, dst);

    for (int i = 0; i < 16; i++)
    {
        printf("%d \n", dst[i]);
    }
    printf("****************************************************************************************\n");

    convolutionMustafaV1(dim, src, ker, dst);
    for (int i = 0; i < 16; i++)
    {
        printf("%d \n", dst[i]);
    }
}