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
    "AYA", /* Team Name */

    "e246581",                              /* First student ID */
    "Moustafa Ismail Hamed Mohamed Ismail", /* First student name */

    "e2489235",                /* Second student ID */
    "Mohammad Mahdi Khosravi", /* Second student name */

    "e2492387", /* Third student ID */
    "Syed Osama Ahmad"};

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

char convolutionMustafaV2_descr[] = "Convolution: Mustafa v6565";
void convolutionMustafaV2(int dim, pixel *src, pixel *ker, unsigned *dst)
{
    int i, j, k;
    int limit = dim - 7;
    pixel *kerRow = ker;
    int val = 0;
    int k0r, k1r, k2r, k3r, k4r, k5r, k6r, k7r;
    int k0g, k1g, k2g, k3g, k4g, k5g, k6g, k7g;
    int k0b, k1b, k2b, k3b, k4b, k5b, k6b, k7b;
    for (k = 0; k < 8; k += 1, kerRow += 8)
    {

        k0r = kerRow[0].red;
        k1r = kerRow[1].red;
        k2r = kerRow[2].red;
        k3r = kerRow[3].red;
        k4r = kerRow[4].red;
        k5r = kerRow[5].red;
        k6r = kerRow[6].red;
        k7r = kerRow[7].red;

        k0g = kerRow[0].green;
        k1g = kerRow[1].green;
        k2g = kerRow[2].green;
        k3g = kerRow[3].green;
        k4g = kerRow[4].green;
        k5g = kerRow[5].green;
        k6g = kerRow[6].green;
        k7g = kerRow[7].green;

        k0b = kerRow[0].blue;
        k1b = kerRow[1].blue;
        k2b = kerRow[2].blue;
        k3b = kerRow[3].blue;
        k4b = kerRow[4].blue;
        k5b = kerRow[5].blue;
        k6b = kerRow[6].blue;
        k7b = kerRow[7].blue;

        unsigned *dstL = dst;
        pixel *elem = src + val;
        for (i = k; i < limit + k; i += 1, dstL += dim)
        {
            for (j = 0; j < limit; j++, elem++)
            {
                unsigned red, blue, green;
                red = (elem[0].red * k0r) + (elem[1].red * k1r) + (elem[2].red * k2r) + (elem[3].red * k3r) + (elem[4].red * k4r) + (elem[5].red * k5r) + (elem[6].red * k6r) + (elem[7].red * k7r);

                green = (elem[0].green * k0g) + (elem[1].green * k1g) + (elem[2].green * k2g) + (elem[3].green * k3g) + (elem[4].green * k4g) + (elem[5].green * k5g) + (elem[6].green * k6g) + (elem[7].green * k7g);

                blue = (elem[0].blue * k0b) + (elem[1].blue * k1b) + (elem[2].blue * k2b) +
                       (elem[3].blue * k3b) + (elem[4].blue * k4b) + (elem[5].blue * k5b) +
                       (elem[6].blue * k6b) + (elem[7].blue * k7b);

                // green = (elem[0].green * kerRow[0].green) + (elem[1].green * kerRow[1].green) + (elem[2].green * kerRow[2].green) + (elem[3].green * kerRow[3].green) + (elem[4].green * kerRow[4].green) + (elem[5].green * kerRow[5].green) + (elem[6].green * kerRow[6].green) + (elem[7].green * kerRow[7].green);

                // blue = (elem[0].blue * kerRow[0].blue) + (elem[1].blue * kerRow[1].blue) + (elem[2].blue * kerRow[2].blue) + (elem[3].blue * kerRow[3].blue) + (elem[4].blue * kerRow[4].blue) + (elem[5].blue * kerRow[5].blue) + (elem[6].blue * kerRow[6].blue) + (elem[7].blue * kerRow[7].blue);

                dstL[j] += red + green + blue;
            }
            elem += 7;
        }
        val += dim;
    }
}

/*
 * convolution - Your current working version of convolution
 * IMPORTANT: This is the version you will be graded on
 */
char convolutionMustafaVf_descr[] = "Convolution: Mustafa Vf";
void convolutionMustafaVf(int dim, pixel *src, pixel *ker, unsigned *dst)
{

    int i, j, k;
    int limit = dim - 7;
    pixel *kerRow = ker;
    int val = 0;
    int k0r, k1r, k2r, k3r, k4r, k5r, k6r, k7r;
    int k0g, k1g, k2g, k3g, k4g, k5g, k6g, k7g;
    int k0b, k1b, k2b, k3b, k4b, k5b, k6b, k7b;
    for (k = 0; k < 8; k += 1, kerRow += 8)
    {

        k0r = kerRow[0].red;
        k0g = kerRow[0].green;
        k0b = kerRow[0].blue;

        k1r = kerRow[1].red;
        k1g = kerRow[1].green;
        k1b = kerRow[1].blue;

        k2r = kerRow[2].red;
        k2g = kerRow[2].green;
        k2b = kerRow[2].blue;

        k3r = kerRow[3].red;
        k3g = kerRow[3].green;
        k3b = kerRow[3].blue;

        k4r = kerRow[4].red;
        k4g = kerRow[4].green;
        k4b = kerRow[4].blue;

        k5r = kerRow[5].red;
        k5g = kerRow[5].green;
        k5b = kerRow[5].blue;

        k6r = kerRow[6].red;
        k6g = kerRow[6].green;
        k6b = kerRow[6].blue;

        k7r = kerRow[7].red;
        k7g = kerRow[7].green;
        k7b = kerRow[7].blue;

        unsigned *dstL = dst;
        pixel *elem = src + val;
        for (i = k; i < limit + k; i += 1, dstL += dim)
        {
            for (j = 0; j < limit; j += 8, elem += 8)
            {
                dstL[j] += (elem[0].red * k0r) + (elem[0].green * k0g) + (elem[0].blue * k0b) + (elem[1].red * k1r) + (elem[1].green * k1g) + (elem[1].blue * k1b) + (elem[2].red * k2r) + (elem[2].green * k2g) + (elem[2].blue * k2b) +
                           (elem[3].red * k3r) + (elem[3].green * k3g) + (elem[3].blue * k3b) + (elem[4].red * k4r) + (elem[4].green * k4g) + (elem[4].blue * k4b) + (elem[5].red * k5r) + (elem[5].green * k5g) + (elem[5].blue * k5b) + (elem[6].red * k6r) + (elem[6].green * k6g) + (elem[6].blue * k6b) + (elem[7].red * k7r) + (elem[7].green * k7g) + (elem[7].blue * k7b);

                dstL[j + 1] += (elem[1].red * k0r) + (elem[1].green * k0g) + (elem[1].blue * k0b) + (elem[2].red * k1r) + (elem[2].green * k1g) + (elem[2].blue * k1b) + (elem[3].red * k2r) + (elem[3].green * k2g) + (elem[3].blue * k2b) +
                               (elem[4].red * k3r) + (elem[4].green * k3g) + (elem[4].blue * k3b) + (elem[5].red * k4r) + (elem[5].green * k4g) + (elem[5].blue * k4b) + (elem[6].red * k5r) + (elem[6].green * k5g) + (elem[6].blue * k5b) + (elem[7].red * k6r) + (elem[7].green * k6g) + (elem[7].blue * k6b) + (elem[8].red * k7r) + (elem[8].green * k7g) + (elem[8].blue * k7b);

                dstL[j + 2] += (elem[2].red * k0r) + (elem[2].green * k0g) + (elem[2].blue * k0b) + (elem[3].red * k1r) + (elem[3].green * k1g) + (elem[3].blue * k1b) + (elem[4].red * k2r) + (elem[4].green * k2g) + (elem[4].blue * k2b) +
                               (elem[5].red * k3r) + (elem[5].green * k3g) + (elem[5].blue * k3b) + (elem[6].red * k4r) + (elem[6].green * k4g) + (elem[6].blue * k4b) + (elem[7].red * k5r) + (elem[7].green * k5g) + (elem[7].blue * k5b) + (elem[8].red * k6r) + (elem[8].green * k6g) + (elem[8].blue * k6b) + (elem[9].red * k7r) + (elem[9].green * k7g) + (elem[9].blue * k7b);

                dstL[j + 3] += (elem[3].red * k0r) + (elem[3].green * k0g) + (elem[3].blue * k0b) + (elem[4].red * k1r) + (elem[4].green * k1g) + (elem[4].blue * k1b) + (elem[5].red * k2r) + (elem[5].green * k2g) + (elem[5].blue * k2b) +
                               (elem[6].red * k3r) + (elem[6].green * k3g) + (elem[6].blue * k3b) + (elem[7].red * k4r) + (elem[7].green * k4g) + (elem[7].blue * k4b) + (elem[8].red * k5r) + (elem[8].green * k5g) + (elem[8].blue * k5b) + (elem[9].red * k6r) + (elem[9].green * k6g) + (elem[9].blue * k6b) + (elem[10].red * k7r) + (elem[10].green * k7g) + (elem[10].blue * k7b);

                dstL[j + 4] += (elem[4].red * k0r) + (elem[4].green * k0g) + (elem[4].blue * k0b) + (elem[5].red * k1r) + (elem[5].green * k1g) + (elem[5].blue * k1b) + (elem[6].red * k2r) + (elem[6].green * k2g) + (elem[6].blue * k2b) +
                               (elem[7].red * k3r) + (elem[7].green * k3g) + (elem[7].blue * k3b) + (elem[8].red * k4r) + (elem[8].green * k4g) + (elem[8].blue * k4b) + (elem[9].red * k5r) + (elem[9].green * k5g) + (elem[9].blue * k5b) + (elem[10].red * k6r) + (elem[10].green * k6g) + (elem[10].blue * k6b) + (elem[11].red * k7r) + (elem[11].green * k7g) + (elem[11].blue * k7b);

                dstL[j + 5] += (elem[5].red * k0r) + (elem[5].green * k0g) + (elem[5].blue * k0b) + (elem[6].red * k1r) + (elem[6].green * k1g) + (elem[6].blue * k1b) + (elem[7].red * k2r) + (elem[7].green * k2g) + (elem[7].blue * k2b) +
                               (elem[8].red * k3r) + (elem[8].green * k3g) + (elem[8].blue * k3b) + (elem[9].red * k4r) + (elem[9].green * k4g) + (elem[9].blue * k4b) + (elem[10].red * k5r) + (elem[10].green * k5g) + (elem[10].blue * k5b) + (elem[11].red * k6r) + (elem[11].green * k6g) + (elem[11].blue * k6b) + (elem[12].red * k7r) + (elem[12].green * k7g) + (elem[12].blue * k7b);

                dstL[j + 6] += (elem[6].red * k0r) + (elem[6].green * k0g) + (elem[6].blue * k0b) + (elem[7].red * k1r) + (elem[7].green * k1g) + (elem[7].blue * k1b) + (elem[8].red * k2r) + (elem[8].green * k2g) + (elem[8].blue * k2b) +
                               (elem[9].red * k3r) + (elem[9].green * k3g) + (elem[9].blue * k3b) + (elem[10].red * k4r) + (elem[10].green * k4g) + (elem[10].blue * k4b) + (elem[11].red * k5r) + (elem[11].green * k5g) + (elem[11].blue * k5b) + (elem[12].red * k6r) + (elem[12].green * k6g) + (elem[12].blue * k6b) + (elem[13].red * k7r) + (elem[13].green * k7g) + (elem[13].blue * k7b);

                dstL[j + 7] += (elem[7].red * k0r) + (elem[7].green * k0g) + (elem[7].blue * k0b) + (elem[8].red * k1r) + (elem[8].green * k1g) + (elem[8].blue * k1b) + (elem[9].red * k2r) + (elem[9].green * k2g) + (elem[9].blue * k2b) +
                               (elem[10].red * k3r) + (elem[10].green * k3g) + (elem[10].blue * k3b) + (elem[11].red * k4r) + (elem[11].green * k4g) + (elem[11].blue * k4b) + (elem[12].red * k5r) + (elem[12].green * k5g) + (elem[12].blue * k5b) + (elem[13].red * k6r) + (elem[13].green * k6g) + (elem[13].blue * k6b) + (elem[14].red * k7r) + (elem[14].green * k7g) + (elem[14].blue * k7b);
            }
        }
        val += dim;
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
    int limit = dim - 7;
    pixel *kerRow = ker;
    int val = 0;
    int k0r, k1r, k2r, k3r, k4r, k5r, k6r, k7r;
    int k0g, k1g, k2g, k3g, k4g, k5g, k6g, k7g;
    int k0b, k1b, k2b, k3b, k4b, k5b, k6b, k7b;
    for (k = 0; k < 8; k += 1, kerRow += 8)
    {

        k0r = kerRow[0].red;
        k0g = kerRow[0].green;
        k0b = kerRow[0].blue;

        k1r = kerRow[1].red;
        k1g = kerRow[1].green;
        k1b = kerRow[1].blue;

        k2r = kerRow[2].red;
        k2g = kerRow[2].green;
        k2b = kerRow[2].blue;

        k3r = kerRow[3].red;
        k3g = kerRow[3].green;
        k3b = kerRow[3].blue;

        k4r = kerRow[4].red;
        k4g = kerRow[4].green;
        k4b = kerRow[4].blue;

        k5r = kerRow[5].red;
        k5g = kerRow[5].green;
        k5b = kerRow[5].blue;

        k6r = kerRow[6].red;
        k6g = kerRow[6].green;
        k6b = kerRow[6].blue;

        k7r = kerRow[7].red;
        k7g = kerRow[7].green;
        k7b = kerRow[7].blue;

        unsigned *dstL = dst;
        pixel *elem = src + val;
        for (i = k; i < limit + k; i += 1, dstL += dim)
        {
            for (j = 0; j < limit; j += 1, elem++)
            {
                dstL[j] += (elem[0].red * k0r) + (elem[0].green * k0g) + (elem[0].blue * k0b) + (elem[1].red * k1r) + (elem[1].green * k1g) + (elem[1].blue * k1b) + (elem[2].red * k2r) + (elem[2].green * k2g) + (elem[2].blue * k2b) +
                           (elem[3].red * k3r) + (elem[3].green * k3g) + (elem[3].blue * k3b) + (elem[4].red * k4r) + (elem[4].green * k4g) + (elem[4].blue * k4b) + (elem[5].red * k5r) + (elem[5].green * k5g) + (elem[5].blue * k5b) + (elem[6].red * k6r) + (elem[6].green * k6g) + (elem[6].blue * k6b) + (elem[7].red * k7r) + (elem[7].green * k7g) + (elem[7].blue * k7b);
            }
            elem += 7;
        }
        val += dim;
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
    add_conv_function(&convolution, convolution_descr);
    add_conv_function(&convolutionMustafaV2, convolutionMustafaV2_descr);
    add_conv_function(&convolutionMustafaVf, convolutionMustafaVf_descr);
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

char avg_pool_mahdi_v2_descr[] = "avg pooling function mahdi v2";
void avg_pool_mahdi_v2(int dim, pixel *src, pixel *dst)
{
    int i, j;
    int limit = dim / 2;

    pixel *row1;
    pixel *row2;
    pixel *dstPixel;

    for (i = 0; i < limit; i++)
        for (j = 0; j < limit; j++)
        {
            dstPixel = dst + RIDX(i, j, limit);
            row1 = src + RIDX(i * 2, j * 2, dim);
            row2 = src + RIDX(i * 2 + 1, j * 2, dim);

            // 0,0
            int sumR0 = row1->red;
            int sumG0 = row1->green;
            int sumB0 = row1->blue;

            // 0,1
            // srcPixel = src + RIDX(i * 2, j * 2 + 1, dim);
            row1++;

            int sumR1 = row1->red;
            int sumG1 = row1->green;
            int sumB1 = row1->blue;

            // 1,0
            // srcPixel = src + RIDX(i * 2 + 1, j * 2, dim);

            int sumR2 = row2->red;
            int sumG2 = row2->green;
            int sumB2 = row2->blue;

            // 1,1
            // srcPixel = src + RIDX(i * 2 + 1, j * 2 + 1, dim);
            row2++;

            int sumR3 = row2->red;
            int sumG3 = row2->green;
            int sumB3 = row2->blue;

            dstPixel->red = (sumR0 + sumR1) + (sumR2 + sumR3);
            dstPixel->green = (sumG0 + sumG1) + (sumG2 + sumG3);
            dstPixel->blue = (sumB0 + sumB1) + (sumB2 + sumB3);

            dstPixel->red >>= 2;
            dstPixel->green >>= 2;
            dstPixel->blue >>= 2;
        }
}

/*
 * average_pooling - Your current working version of average_pooling
 * IMPORTANT: This is the version you will be graded on
 */
char average_pooling_descr[] = "Average Pooling: Current working version";
void average_pooling(int dim, pixel *src, pixel *dst)
{

    // naive_average_pooling(dim,src,dst);
    // avg_pool_mahdi_v2(dim, src, dst);

    int i, j;
    int limit = dim / 2;

    pixel *row1;
    pixel *row2;
    pixel *dstPixel;

    for (i = 0; i < limit; i++)
        for (j = 0; j < limit; j++)
        {
            dstPixel = dst + RIDX(i, j, limit);
            row1 = src + RIDX(i * 2, j * 2, dim);
            row2 = src + RIDX(i * 2 + 1, j * 2, dim);

            // 0,0
            int sumR0 = row1->red;
            int sumG0 = row1->green;
            int sumB0 = row1->blue;

            // 0,1
            // srcPixel = src + RIDX(i * 2, j * 2 + 1, dim);
            row1++;

            int sumR1 = row1->red;
            int sumG1 = row1->green;
            int sumB1 = row1->blue;

            // 1,0
            // srcPixel = src + RIDX(i * 2 + 1, j * 2, dim);

            int sumR2 = row2->red;
            int sumG2 = row2->green;
            int sumB2 = row2->blue;

            // 1,1
            // srcPixel = src + RIDX(i * 2 + 1, j * 2 + 1, dim);
            row2++;

            int sumR3 = row2->red;
            int sumG3 = row2->green;
            int sumB3 = row2->blue;

            dstPixel->red = (sumR0 + sumR1) + (sumR2 + sumR3);
            dstPixel->green = (sumG0 + sumG1) + (sumG2 + sumG3);
            dstPixel->blue = (sumB0 + sumB1) + (sumB2 + sumB3);

            dstPixel->red >>= 2;
            dstPixel->green >>= 2;
            dstPixel->blue >>= 2;
        }
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
    add_average_pooling_function(&avg_pool_mahdi_v2, avg_pool_mahdi_v2_descr);
    /* ... Register additional test functions here */
}
