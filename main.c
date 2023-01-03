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

char convolutionGEMM_descr[] = "GEMM";
void convolutionGEMM(int dim, pixel *src, pixel *ker, unsigned *dst)
{
    // int i, j, k;

    // for (i = 0; i < 16; i++)
    // {
    //     dst[i] = 0;
    // }

    // pixel *kerRow = ker;
    // for (k = 0; k < 2; k++, kerRow += 2)
    // {
    //     int crow = k * dim;
    //     for (i = k; i < dim - 1 + k; i++, crow += dim)
    //     {
    //         for (j = 0; j < dim - 1; j++)
    //         {
    //             int sum = src[crow + j].red * kerRow[0].red + src[crow + j].green * kerRow[0].green + src[crow + j].blue * kerRow[0].blue;
    //             sum += src[crow + j + 1].red * kerRow[1].red + src[crow + j + 1].green * kerRow[1].green + src[crow + j + 1].blue * kerRow[1].blue;
    //             // sum += src[crow + j + 2].red * kerRow[2].red + src[crow + j + 2].green * kerRow[2].green + src[crow + j + 2].blue * kerRow[2].blue;
    //             // sum += src[crow + j + 3].red * kerRow[3].red + src[crow + j + 3].green * kerRow[3].green + src[crow + j + 3].blue * kerRow[3].blue;
    //             // sum += src[crow + j + 4].red * kerRow[4].red + src[crow + j + 4].green * kerRow[4].green + src[crow + j + 4].blue * kerRow[4].blue;
    //             // sum += src[crow + j + 5].red * kerRow[5].red + src[crow + j + 5].green * kerRow[5].green + src[crow + j + 5].blue * kerRow[5].blue;
    //             // sum += src[crow + j + 6].red * kerRow[6].red + src[crow + j + 6].green * kerRow[6].green + src[crow + j + 6].blue * kerRow[6].blue;
    //             // sum += src[crow + j + 7].red * kerRow[7].red + src[crow + j + 7].green * kerRow[7].green + src[crow + j + 7].blue * kerRow[7].blue;
    //             dst[crow - k * dim + j] += sum;
    //         }
    //     }
    // }

    int i, j, k;

    for (i = 0; i < 16; i++)
    {
        dst[i] = 0;
    }

    pixel *kerRow = ker;
    for (k = 0; k < 2; k += 1, kerRow += 2)
    {
        printf("hola hola \n");
        int crow = k * dim;
        for (i = k; i < dim - 1 + k; i += 1, crow += dim)
        {
            for (j = 0; j < dim - 1; j++)
            {
                int sum = src[crow + j].red * kerRow[0].red + src[crow + j].green * kerRow[0].green + src[crow + j].blue * kerRow[0].blue;
                sum += src[crow + j + 1].red * kerRow[1].red + src[crow + j + 1].green * kerRow[1].green + src[crow + j + 1].blue * kerRow[1].blue;
                // sum += src[crow + j + 2].red * kerRow[2].red + src[crow + j + 2].green * kerRow[2].green + src[crow + j + 2].blue * kerRow[2].blue;
                // sum += src[crow + j + 3].red * kerRow[3].red + src[crow + j + 3].green * kerRow[3].green + src[crow + j + 3].blue * kerRow[3].blue;
                // sum += src[crow + j + 4].red * kerRow[4].red + src[crow + j + 4].green * kerRow[4].green + src[crow + j + 4].blue * kerRow[4].blue;
                // sum += src[crow + j + 5].red * kerRow[5].red + src[crow + j + 5].green * kerRow[5].green + src[crow + j + 5].blue * kerRow[5].blue;
                // sum += src[crow + j + 6].red * kerRow[6].red + src[crow + j + 6].green * kerRow[6].green + src[crow + j + 6].blue * kerRow[6].blue;
                // sum += src[crow + j + 7].red * kerRow[7].red + src[crow + j + 7].green * kerRow[7].green + src[crow + j + 7].blue * kerRow[7].blue;

                // int sum2 = src[crow + dim + j].red * kerRow[2].red + src[crow + dim + j].green * kerRow[2].green + src[crow + dim + j].blue * kerRow[2].blue;
                // sum2 += src[crow + dim + j + 1].red * kerRow[3].red + src[crow + dim + j + 1].green * kerRow[3].green + src[crow + dim + j + 1].blue * kerRow[3].blue;
                // sum2 += src[crow + dim + j + 2].red * kerRow[10].red + src[crow + dim + j + 2].green * kerRow[10].green + src[crow + dim + j + 2].blue * kerRow[10].blue;
                // sum2 += src[crow + dim + j + 3].red * kerRow[11].red + src[crow + dim + j + 3].green * kerRow[11].green + src[crow + dim + j + 3].blue * kerRow[11].blue;
                // sum2 += src[crow + dim + j + 4].red * kerRow[12].red + src[crow + dim + j + 4].green * kerRow[12].green + src[crow + dim + j + 4].blue * kerRow[12].blue;
                // sum2 += src[crow + dim + j + 5].red * kerRow[13].red + src[crow + dim + j + 5].green * kerRow[13].green + src[crow + dim + j + 5].blue * kerRow[13].blue;
                // sum2 += src[crow + dim + j + 6].red * kerRow[14].red + src[crow + dim + j + 6].green * kerRow[14].green + src[crow + dim + j + 6].blue * kerRow[14].blue;
                // sum2 += src[crow + dim + j + 7].red * kerRow[15].red + src[crow + dim + j + 7].green * kerRow[15].green + src[crow + dim + j + 7].blue * kerRow[15].blue;

                dst[crow - k * dim + j] += sum;
                // dst[crow - k * dim + dim + j] += sum2;

                printf("k=%d i=%d j=%d****************************\n", k, i, j);
                for (int x = 0; x < (dim - 1); x++)
                {
                    for (int y = 0; y < (dim - 1); y++)
                    {
                        printf("%d  ", dst[x * (dim - 1) + y]);
                    }
                    printf(" \n");
                }
            }
        }
    }
    printf("%ld %ld ************\n ", sizeof(pixel), sizeof(unsigned));
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

    // convolutionMustafaV1(dim, src, ker, dst);
    // for (int i = 0; i < 16; i++)
    // {
    //     printf("%d \n", dst[i]);
    // }

    convolutionGEMM(dim, src, ker, dst);

    for (int i = 0; i < 16; i++)
    {
        printf("%d \n", dst[i]);
    }
}