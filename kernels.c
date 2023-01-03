/********************************************************
 * Kernels to be optimized for the CS:APP Performance Lab
 ********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
/*
 * Please fill in the following team_t struct
 */
team_t team = {
    "HOLA", /* Team Name */

    "e246581",                              /* First student ID */
    "Moustafa Ismail Hamed Mohamed Ismail", /* First student name */

    "e248923",                 /* Second student ID */
    "Mohammad Mahdi Khosravi", /* Second student name */

    "", /* Third student ID */
    ""  /* Third student Name */
};

/********************
 * CONVOLUTION KERNEL
 ********************/

/***************************************************************
 * Your different versions of the convolution functions  go here
 ***************************************************************/

/*
 * naive_conv - The naive baseline version of convolution
 */
char naive_conv_descr[] = "naive_conv: Naive baseline implementation";
void naive_conv(int dim, pixel *src, pixel *ker, unsigned *dst)
{
    int i, j, k, l;

    for (i = 0; i < dim - 8 + 1; i++)
        for (j = 0; j < dim - 8 + 1; j++)
        {
            dst[RIDX(i, j, dim)] = 0;
            for (k = 0; k < 8; k++)
                for (l = 0; l < 8; l++)
                {
                    dst[RIDX(i, j, dim)] += src[RIDX((i + k), (j + l), dim)].red * ker[RIDX(k, l, 8)].red;
                    dst[RIDX(i, j, dim)] += src[RIDX((i + k), (j + l), dim)].green * ker[RIDX(k, l, 8)].green;
                    dst[RIDX(i, j, dim)] += src[RIDX((i + k), (j + l), dim)].blue * ker[RIDX(k, l, 8)].blue;
                }
        }
}

/*
 * convolution - Mustafa v1
 */
char convolutionMustafaV1_descr[] = "Convolution: Mustafa v1";
void convolutionMustafaV1(int dim, pixel *src, pixel *ker, unsigned *dst)
{

    int i, j, k;
    pixel *kerPixel = ker;
    int limit = dim-7;
    for (k = 0; k < 64; k++, kerPixel++)
    {
        int red = kerPixel->red;
        int blue = kerPixel->blue;
        int green = kerPixel->green;
        unsigned *dstPixel1 = dst;
        int temp = (k >> 3) * dim;
        pixel *start = src + (k % 8);

        for (i = 0; i < limit; i++)
        {
            pixel *srcPixel1 = start + temp;
            for (j = 0; j < limit - 3; j += 4)
            {
                pixel *srcPixel2 = srcPixel1 + 1;
                pixel *srcPixel3 = srcPixel1 + 2;
                pixel *srcPixel4 = srcPixel1 + 3;
                // pixel *srcPixel5 = srcPixel1 + 4;
                // pixel *srcPixel6 = srcPixel1 + 5;
                // pixel *srcPixel7 = srcPixel1 + 6;
                // pixel *srcPixel8 = srcPixel1 + 7;

                int sum1 = srcPixel1->red * red;
                int sum2 = srcPixel2->red * red;
                int sum3 = srcPixel3->red * red;
                int sum4 = srcPixel4->red * red;
                // int sum5 = srcPixel5->red * red;
                // int sum6 = srcPixel6->red * red;
                // int sum7 = srcPixel7->red * red;
                // int sum8 = srcPixel8->red * red;

                sum1 += srcPixel1->green * green;
                sum2 += srcPixel2->green * green;
                sum3 += srcPixel3->green * green;
                sum4 += srcPixel4->green * green;
                // sum5 += srcPixel5->green * green;
                // sum6 += srcPixel6->green * green;
                // sum7 += srcPixel7->green * green;
                // sum8 += srcPixel8->green * green;

                sum1 += srcPixel1->blue * blue;
                sum2 += srcPixel2->blue * blue;
                sum3 += srcPixel3->blue * blue;
                sum4 += srcPixel4->blue * blue;
                // sum5 += srcPixel5->blue * blue;
                // sum6 += srcPixel6->blue * blue;
                // sum7 += srcPixel7->blue * blue;
                // sum8 += srcPixel8->blue * blue;

                unsigned *dstPixel2 = dstPixel1 + 1;
                unsigned *dstPixel3 = dstPixel1 + 2;
                unsigned *dstPixel4 = dstPixel1 + 3;
                // unsigned *dstPixel5 = dstPixel1 + 4;
                // unsigned *dstPixel6 = dstPixel1 + 5;
                // unsigned *dstPixel7 = dstPixel1 + 6;
                // unsigned *dstPixel8 = dstPixel1 + 7;

                *dstPixel1 += sum1;
                *dstPixel2 += sum2;
                *dstPixel3 += sum3;
                *dstPixel4 += sum4;
                // *dstPixel5 += sum5;
                // *dstPixel6 += sum6;
                // *dstPixel7 += sum7;
                // *dstPixel8 += sum8;

                dstPixel1 += 4;
                srcPixel1 += 4;
            }

            for (; j < limit; j++, dstPixel1++)
            {

                int sum = srcPixel1->red * red;
                sum += srcPixel1->green * green;
                sum += srcPixel1->blue * blue;

                *dstPixel1 += sum;
                srcPixel1++;
            }
            dstPixel1 += 7;
            temp += dim;
        }
    }
}

/*
 * convolution - Your current working version of convolution
 * IMPORTANT: This is the version you will be graded on
 */
char convolution_descr[] = "Convolution: Current working version";
void convolution(int dim, pixel *src, pixel *ker, unsigned *dst)
{

    int i, j, k;
    for (i = 0; i < dim - 8 + 1; i++)
        for (j = 0; j < dim - 8 + 1; j++)
        {
            int sum = 0;
            pixel *kerPixel = ker;
            for (k = 0; k < 8; k++)
            {
                pixel *srcPixel = src + RIDX((i + k), j, dim);

                int redc0 = srcPixel->red * kerPixel->red;
                int greenc0 = srcPixel->green * kerPixel->green;
                int bluec0 = srcPixel->blue * kerPixel->blue;

                kerPixel += 1;
                srcPixel += 1;

                int redc1 = srcPixel->red * kerPixel->red;
                int greenc1 = srcPixel->green * kerPixel->green;
                int bluec1 = srcPixel->blue * kerPixel->blue;

                int sumc0 = redc0 + greenc0;
                int sumc1 = redc1 + greenc1;
                sum += sumc0 + bluec0;
                sum += sumc1 + bluec1;

                kerPixel += 1;
                srcPixel += 1;

                int redc2 = srcPixel->red * kerPixel->red;
                int greenc2 = srcPixel->green * kerPixel->green;
                int bluec2 = srcPixel->blue * kerPixel->blue;

                kerPixel += 1;
                srcPixel += 1;

                int redc3 = srcPixel->red * kerPixel->red;
                int greenc3 = srcPixel->green * kerPixel->green;
                int bluec3 = srcPixel->blue * kerPixel->blue;

                int sumc2 = redc2 + greenc2;
                int sumc3 = redc3 + greenc3;

                sum += sumc2 + bluec2;
                sum += sumc3 + bluec3;

                kerPixel += 1;
                srcPixel += 1;

                int redc4 = srcPixel->red * kerPixel->red;
                int greenc4 = srcPixel->green * kerPixel->green;
                int bluec4 = srcPixel->blue * kerPixel->blue;

                kerPixel += 1;
                srcPixel += 1;

                int redc5 = srcPixel->red * kerPixel->red;
                int greenc5 = srcPixel->green * kerPixel->green;
                int bluec5 = srcPixel->blue * kerPixel->blue;

                int sumc4 = redc4 + greenc4;
                int sumc5 = redc5 + greenc5;
                sum += sumc4 + bluec4;
                sum += sumc5 + bluec5;

                kerPixel += 1;
                srcPixel += 1;

                int redc6 = srcPixel->red * kerPixel->red;
                int greenc6 = srcPixel->green * kerPixel->green;
                int bluec6 = srcPixel->blue * kerPixel->blue;

                kerPixel += 1;
                srcPixel += 1;

                int redc7 = srcPixel->red * kerPixel->red;
                int greenc7 = srcPixel->green * kerPixel->green;
                int bluec7 = srcPixel->blue * kerPixel->blue;

                kerPixel += 1;

                int sumc6 = redc6 + greenc6;
                int sumc7 = redc7 + greenc7;

                sum += sumc6 + bluec6;
                sum += sumc7 + bluec7;
            }
            dst[RIDX(i, j, dim)] = sum;
        }
}

/*********************************************************************
 * register_conv_functions - Register all of your different versions
 *     of the convolution functions  with the driver by calling the
 *     add_conv_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.
 *********************************************************************/

void register_conv_functions()
{
    add_conv_function(&naive_conv, naive_conv_descr);
    add_conv_function(&convolutionMustafaV1, convolutionMustafaV1_descr);
    add_conv_function(&convolution, convolution_descr);
    /* ... Register additional test functions here */
}

/************************
 * AVERAGE POOLING KERNEL
 ************************/

/*********************************************************
 * Your different versions of the average pooling  go here
 *********************************************************/

/*
 * naive_average_pooling - The naive baseline version of average pooling
 */
char naive_average_pooling_descr[] = "Naive Average Pooling: Naive baseline implementation";
void naive_average_pooling(int dim, pixel *src, pixel *dst)
{
    int i, j, k, l;

    for (i = 0; i < dim / 2; i++)
        for (j = 0; j < dim / 2; j++)
        {
            dst[RIDX(i, j, dim / 2)].red = 0;
            dst[RIDX(i, j, dim / 2)].green = 0;
            dst[RIDX(i, j, dim / 2)].blue = 0;
            for (k = 0; k < 2; k++)
            {
                for (l = 0; l < 2; l++)
                {
                    dst[RIDX(i, j, dim / 2)].red += src[RIDX(i * 2 + k, j * 2 + l, dim)].red;
                    dst[RIDX(i, j, dim / 2)].green += src[RIDX(i * 2 + k, j * 2 + l, dim)].green;
                    dst[RIDX(i, j, dim / 2)].blue += src[RIDX(i * 2 + k, j * 2 + l, dim)].blue;
                }
            }
            dst[RIDX(i, j, dim / 2)].red /= 4;
            dst[RIDX(i, j, dim / 2)].green /= 4;
            dst[RIDX(i, j, dim / 2)].blue /= 4;
        }
}

/*
 * average_pooling - Your current working version of average_pooling
 * IMPORTANT: This is the version you will be graded on
 */
char average_pooling_descr[] = "Average Pooling: Current working version";
void average_pooling(int dim, pixel *src, pixel *dst)
{

    naive_average_pooling(dim, src, dst);
}

/******************************************************************************
 * register_average_pooling_functions - Register all of your different versions
 *     of the average pooling  with the driver by calling the
 *     add_average_pooling_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.
 ******************************************************************************/

void register_average_pooling_functions()
{
    add_average_pooling_function(&naive_average_pooling, naive_average_pooling_descr);
    add_average_pooling_function(&average_pooling, average_pooling_descr);
    /* ... Register additional test functions here */
}
