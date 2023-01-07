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
char convolutionMad_descr[] = "Convolution: Mad";
void convolutionMad(int dim, pixel *src, pixel *ker, unsigned *dst)
{
    int i, j, k;
    int limit = dim - 7;
    pixel *kerRow = ker;
    int val = 0;
    int k0r, k1r, k2r, k3r, k4r, k5r, k6r, k7r;
    int k0g, k1g, k2g, k3g, k4g, k5g, k6g, k7g;
    int k0b, k1b, k2b, k3b, k4b, k5b, k6b, k7b;

    int p0r, p1r, p2r, p3r, p4r, p5r, p6r, p7r;
    int p0g, p1g, p2g, p3g, p4g, p5g, p6g, p7g;
    int p0b, p1b, p2b, p3b, p4b, p5b, p6b, p7b;
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
            p1r = elem[0].red;
            p1g = elem[0].green;
            p1b = elem[0].blue;

            p2r = elem[1].red;
            p2g = elem[1].green;
            p2b = elem[1].blue;

            p3r = elem[2].red;
            p3g = elem[2].green;
            p3b = elem[2].blue;

            p4r = elem[3].red;
            p4g = elem[3].green;
            p4b = elem[3].blue;

            p5r = elem[4].red;
            p5g = elem[4].green;
            p5b = elem[4].blue;

            p6r = elem[5].red;
            p6g = elem[5].green;
            p6b = elem[5].blue;

            p7r = elem[6].red;
            p7g = elem[6].green;
            p7b = elem[6].blue;

            for (j = 0; j < limit; j += 8, elem += 8)
            {
                p0r = elem[0].red;
                p0g = elem[0].green;
                p0b = elem[0].blue;

                p1r = elem[1].red;
                p1g = elem[1].green;
                p1b = elem[1].blue;

                p2r = elem[2].red;
                p2g = elem[2].green;
                p2b = elem[2].blue;

                p3r = elem[3].red;
                p3g = elem[3].green;
                p3b = elem[3].blue;

                p4r = elem[4].red;
                p4g = elem[4].green;
                p4b = elem[4].blue;

                p5r = elem[5].red;
                p5g = elem[5].green;
                p5b = elem[5].blue;

                p6r = elem[6].red;
                p6g = elem[6].green;
                p6b = elem[6].blue;

                p7r = elem[7].red;
                p7g = elem[7].green;
                p7b = elem[7].blue;

                dstL[j] += (p0r * k0r) + (p0g * k0g) + (p0b * k0b) + (p1r * k1r) + (p1g * k1g) + (p1b * k1b) + (p2r * k2r) + (p2g * k2g) + (p2b * k2b) +
                           (p3r * k3r) + (p3g * k3g) + (p3b * k3b) + (p4r * k4r) + (p4g * k4g) + (p4b * k4b) + (p5r * k5r) + (p5g * k5g) + (p5b * k5b) + (p6r * k6r) + (p6g * k6g) + (p6b * k6b) + (p7r * k7r) + (p7g * k7g) + (p7b * k7b);

                p0r = elem[8].red;
                p0g = elem[8].green;
                p0b = elem[8].blue;

                dstL[j + 1] += (p1r * k0r) + (p1g * k0g) + (p1b * k0b) + (p2r * k1r) + (p2g * k1g) + (p2b * k1b) + (p3r * k2r) + (p3g * k2g) + (p3b * k2b) +
                               (p4r * k3r) + (p4g * k3g) + (p4b * k3b) + (p5r * k4r) + (p5g * k4g) + (p5b * k4b) + (p6r * k5r) + (p6g * k5g) + (p6b * k5b) + (p7r * k6r) + (p7g * k6g) + (p7b * k6b) + (p0r * k7r) + (p0g * k7g) + (p0b * k7b);

                p1r = elem[9].red;
                p1g = elem[9].green;
                p1b = elem[9].blue;

                dstL[j + 2] += (p2r * k0r) + (p2g * k0g) + (p2b * k0b) + (p3r * k1r) + (p3g * k1g) + (p3b * k1b) + (p4r * k2r) + (p4g * k2g) + (p4b * k2b) +
                               (p5r * k3r) + (p5g * k3g) + (p5b * k3b) + (p6r * k4r) + (p6g * k4g) + (p6b * k4b) + (p7r * k5r) + (p7g * k5g) + (p7b * k5b) + (p0r * k6r) + (p0g * k6g) + (p0b * k6b) + (p1r * k7r) + (p1g * k7g) + (p1b * k7b);

                p2r = elem[10].red;
                p2g = elem[10].green;
                p2b = elem[10].blue;

                dstL[j + 3] += (p3r * k0r) + (p3g * k0g) + (p3b * k0b) + (p4r * k1r) + (p4g * k1g) + (p4b * k1b) + (p5r * k2r) + (p5g * k2g) + (p5b * k2b) +
                               (p6r * k3r) + (p6g * k3g) + (p6b * k3b) + (p7r * k4r) + (p7g * k4g) + (p7b * k4b) + (p0r * k5r) + (p0g * k5g) + (p0b * k5b) + (p1r * k6r) + (p1g * k6g) + (p1b * k6b) + (p2r * k7r) + (p2g * k7g) + (p2b * k7b);

                p3r = elem[11].red;
                p3g = elem[11].green;
                p3b = elem[11].blue;

                dstL[j + 4] += (p4r * k0r) + (p4g * k0g) + (p4b * k0b) + (p5r * k1r) + (p5g * k1g) + (p5b * k1b) + (p6r * k2r) + (p6g * k2g) + (p6b * k2b) +
                               (p7r * k3r) + (p7g * k3g) + (p7b * k3b) + (p0r * k4r) + (p0g * k4g) + (p0b * k4b) + (p1r * k5r) + (p1g * k5g) + (p1b * k5b) + (p2r * k6r) + (p2g * k6g) + (p2b * k6b) + (p3r * k7r) + (p3g * k7g) + (p3b * k7b);

                p4r = elem[12].red;
                p4g = elem[12].green;
                p4b = elem[12].blue;

                dstL[j + 5] += (p5r * k0r) + (p5g * k0g) + (p5b * k0b) + (p6r * k1r) + (p6g * k1g) + (p6b * k1b) + (p7r * k2r) + (p7g * k2g) + (p7b * k2b) +
                               (p0r * k3r) + (p0g * k3g) + (p0b * k3b) + (p1r * k4r) + (p1g * k4g) + (p1b * k4b) + (p2r * k5r) + (p2g * k5g) + (p2b * k5b) + (p3r * k6r) + (p3g * k6g) + (p3b * k6b) + (p4r * k7r) + (p4g * k7g) + (p4b * k7b);

                p5r = elem[13].red;
                p5g = elem[13].green;
                p5b = elem[13].blue;

                dstL[j + 6] += (p6r * k0r) + (p6g * k0g) + (p6b * k0b) + (p7r * k1r) + (p7g * k1g) + (p7b * k1b) + (p0r * k2r) + (p0g * k2g) + (p0b * k2b) +
                               (p1r * k3r) + (p1g * k3g) + (p1b * k3b) + (p2r * k4r) + (p2g * k4g) + (p2b * k4b) + (p3r * k5r) + (p3g * k5g) + (p3b * k5b) + (p4r * k6r) + (p4g * k6g) + (p4b * k6b) + (p5r * k7r) + (p5g * k7g) + (p5b * k7b);

                p6r = elem[14].red;
                p6g = elem[14].green;
                p6b = elem[14].blue;

                dstL[j + 7] += (p7r * k0r) + (p7g * k0g) + (p7b * k0b) + (p0r * k1r) + (p0g * k1g) + (p0b * k1b) + (p1r * k2r) + (p1g * k2g) + (p1b * k2b) +
                               (p2r * k3r) + (p2g * k3g) + (p2b * k3b) + (p3r * k4r) + (p3g * k4g) + (p3b * k4b) + (p4r * k5r) + (p4g * k5g) + (p4b * k5b) + (p5r * k6r) + (p5g * k6g) + (p5b * k6b) + (p6r * k7r) + (p6g * k7g) + (p6b * k7b);
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
    unsigned i, j, k;
    unsigned limit = dim - 7;
    pixel *kerRow = ker;
    unsigned val = 0;
    unsigned short k0r, k1r, k2r, k3r, k4r, k5r, k6r, k7r;
    unsigned short k0g, k1g, k2g, k3g, k4g, k5g, k6g, k7g;
    unsigned short k0b, k1b, k2b, k3b, k4b, k5b, k6b, k7b;
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
    // add_conv_function(&convolutionMad, convolutionMad_descr);
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
