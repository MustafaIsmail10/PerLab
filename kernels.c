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

    "e2492387", /* Third student ID */
    "Syed Osama Ahmad"  /* Third student Name */
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
                // sum8 += srcPixel8->blue * blue;git push --set-upstream origin mustafa


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

char convolution_mahdi_descr[] = "CONVOLUTION: MAHDI v1";
void convolution_mahdi(int dim, pixel *src, pixel *ker, unsigned *dst) {
    int i,j,res, res2, res3,limit = dim - 7;
    // int kernValues[64];
    pixel *tmpSrc, *rwSrc, *rwSrc2;
    unsigned *rwDst;
    // kernValues = ker;
    for(i = 0; i < limit; i++) 
    {
        tmpSrc = src; 
        rwDst = dst;
        for(j = 0; j < limit; j++) 
        {
            rwSrc = tmpSrc;
            // res = (rwSrc[0].red * kernValues[0].red);
            // res += (rwSrc[0].green * kernValues[0].green);
            //res += (rwSrc[0].blue * kernValues[0].blue);
            // res = (rwSrc[0].red * kernValues[0].red);
            rwSrc2 = tmpSrc + dim;

            res = (rwSrc[0].red * ker[0].red) + (rwSrc[1].red * ker[1].red) + (rwSrc[2].red * ker[2].red) +
                   (rwSrc[3].red * ker[3].red) + (rwSrc[4].red * ker[4].red) + (rwSrc[5].red * ker[5].red) +
                   (rwSrc[6].red * ker[6].red) + (rwSrc[7].red * ker[7].red);

            res2 = (rwSrc[0].green * ker[0].green) + (rwSrc[1].green * ker[1].green) + (rwSrc[2].green * ker[2].green) +
                   (rwSrc[3].green * ker[3].green) + (rwSrc[4].green * ker[4].green) + (rwSrc[5].green * ker[5].green) +
                   (rwSrc[6].green * ker[6].green) + (rwSrc[7].green * ker[7].green);

            res3 = (rwSrc[0].blue * ker[0].blue) + (rwSrc[1].blue * ker[1].blue) + (rwSrc[2].blue * ker[2].blue) +
                   (rwSrc[3].blue * ker[3].blue) + (rwSrc[4].blue * ker[4].blue) + (rwSrc[5].blue * ker[5].blue) +
                   (rwSrc[6].blue * ker[6].blue) + (rwSrc[7].blue * ker[7].blue);
            // Even
            rwSrc += (dim << 1);

            res += (rwSrc2[0].red * ker[8].red) + (rwSrc2[1].red * ker[9].red) + (rwSrc2[2].red * ker[10].red) +
                   (rwSrc2[3].red * ker[11].red) + (rwSrc2[4].red * ker[12].red) + (rwSrc2[5].red * ker[13].red) +
                   (rwSrc2[6].red * ker[14].red) + (rwSrc2[7].red * ker[15].red);

            res2 += (rwSrc2[0].green * ker[8].green) + (rwSrc2[1].green * ker[9].green) + (rwSrc2[2].green * ker[10].green) +
                   (rwSrc2[3].green * ker[11].green) + (rwSrc2[4].green * ker[12].green) + (rwSrc2[5].green * ker[13].green) +
                   (rwSrc2[6].green * ker[14].green) + (rwSrc2[7].green * ker[15].green);

            res3 += (rwSrc2[0].blue * ker[8].blue) + (rwSrc2[1].blue * ker[9].blue) + (rwSrc2[2].blue * ker[10].blue) +
                   (rwSrc2[3].blue * ker[11].blue) + (rwSrc2[4].blue * ker[12].blue) + (rwSrc2[5].blue * ker[13].blue) +
                   (rwSrc2[6].blue * ker[14].blue) + (rwSrc2[7].blue * ker[15].blue);
            // Odd
            rwSrc2 += (dim << 1);

            res += (rwSrc[0].red * ker[16].red) + (rwSrc[1].red * ker[17].red) + (rwSrc[2].red * ker[18].red) +
                   (rwSrc[3].red * ker[19].red) + (rwSrc[4].red * ker[20].red) + (rwSrc[5].red * ker[21].red) +
                   (rwSrc[6].red * ker[22].red) + (rwSrc[7].red * ker[23].red);

            res2 += (rwSrc[0].green * ker[16].green) + (rwSrc[1].green * ker[17].green) + (rwSrc[2].green * ker[18].green) +
                   (rwSrc[3].green * ker[19].green) + (rwSrc[4].green * ker[20].green) + (rwSrc[5].green * ker[21].green) +
                   (rwSrc[6].green * ker[22].green) + (rwSrc[7].green * ker[23].green);

            res3 += (rwSrc[0].blue * ker[16].blue) + (rwSrc[1].blue * ker[17].blue) + (rwSrc[2].blue * ker[18].blue) +
                   (rwSrc[3].blue * ker[19].blue) + (rwSrc[4].blue * ker[20].blue) + (rwSrc[5].blue * ker[21].blue) +
                   (rwSrc[6].blue * ker[22].blue) + (rwSrc[7].blue * ker[23].blue);
            // Even
            rwSrc += (dim << 1);

            res += (rwSrc2[0].red * ker[24].red) + (rwSrc2[1].red * ker[25].red) + (rwSrc2[2].red * ker[26].red) +
                   (rwSrc2[3].red * ker[27].red) + (rwSrc2[4].red * ker[28].red) + (rwSrc2[5].red * ker[29].red) +
                   (rwSrc2[6].red * ker[30].red) + (rwSrc2[7].red * ker[31].red);

            res2 += (rwSrc2[0].green * ker[24].green) + (rwSrc2[1].green * ker[25].green) + (rwSrc2[2].green * ker[26].green) +
                   (rwSrc2[3].green * ker[27].green) + (rwSrc2[4].green * ker[28].green) + (rwSrc2[5].green * ker[29].green) +
                   (rwSrc2[6].green * ker[30].green) + (rwSrc2[7].green * ker[31].green);

            res3 += (rwSrc2[0].blue * ker[24].blue) + (rwSrc2[1].blue * ker[25].blue) + (rwSrc2[2].blue * ker[26].blue) +
                   (rwSrc2[3].blue * ker[27].blue) + (rwSrc2[4].blue * ker[28].blue) + (rwSrc2[5].blue * ker[29].blue) +
                   (rwSrc2[6].blue * ker[30].blue) + (rwSrc2[7].blue * ker[31].blue);
            // Odd
            rwSrc2 += (dim << 1);

            res += (rwSrc[0].red * ker[32].red) + (rwSrc[1].red * ker[33].red) + (rwSrc[2].red * ker[34].red) +
                   (rwSrc[3].red * ker[35].red) + (rwSrc[4].red * ker[36].red) + (rwSrc[5].red * ker[37].red) +
                   (rwSrc[6].red * ker[38].red) + (rwSrc[7].red * ker[39].red);

            res2 += (rwSrc[0].green * ker[32].green) + (rwSrc[1].green * ker[33].green) + (rwSrc[2].green * ker[34].green) +
                   (rwSrc[3].green * ker[35].green) + (rwSrc[4].green * ker[36].green) + (rwSrc[5].green * ker[37].green) +
                   (rwSrc[6].green * ker[38].green) + (rwSrc[7].green * ker[39].green);

            res3 += (rwSrc[0].blue * ker[32].blue) + (rwSrc[1].blue * ker[33].blue) + (rwSrc[2].blue * ker[34].blue) +
                   (rwSrc[3].blue * ker[35].blue) + (rwSrc[4].blue * ker[36].blue) + (rwSrc[5].blue * ker[37].blue) +
                   (rwSrc[6].blue * ker[38].blue) + (rwSrc[7].blue * ker[39].blue);
            // Even
            rwSrc += (dim << 1);

            res += (rwSrc2[0].red * ker[40].red) + (rwSrc2[1].red * ker[41].red) + (rwSrc2[2].red * ker[42].red) +
                   (rwSrc2[3].red * ker[43].red) + (rwSrc2[4].red * ker[44].red) + (rwSrc2[5].red * ker[45].red) +
                   (rwSrc2[6].red * ker[46].red) + (rwSrc2[7].red * ker[47].red);

            res2 += (rwSrc2[0].green * ker[40].green) + (rwSrc2[1].green * ker[41].green) + (rwSrc2[2].green * ker[42].green) +
                   (rwSrc2[3].green * ker[43].green) + (rwSrc2[4].green * ker[44].green) + (rwSrc2[5].green * ker[45].green) +
                   (rwSrc2[6].green * ker[46].green) + (rwSrc2[7].green * ker[47].green);

            res3 += (rwSrc2[0].blue * ker[40].blue) + (rwSrc2[1].blue * ker[41].blue) + (rwSrc2[2].blue * ker[42].blue) +
                   (rwSrc2[3].blue * ker[43].blue) + (rwSrc2[4].blue * ker[44].blue) + (rwSrc2[5].blue * ker[45].blue) +
                   (rwSrc2[6].blue * ker[46].blue) + (rwSrc2[7].blue * ker[47].blue);
            // Odd
            rwSrc2 += (dim << 1);

            res += (rwSrc[0].red * ker[48].red) + (rwSrc[1].red * ker[49].red) + (rwSrc[2].red * ker[50].red) +
                   (rwSrc[3].red * ker[51].red) + (rwSrc[4].red * ker[52].red) + (rwSrc[5].red * ker[53].red) +
                   (rwSrc[6].red * ker[54].red) + (rwSrc[7].red * ker[55].red);

            res2 += (rwSrc[0].green * ker[48].green) + (rwSrc[1].green * ker[49].green) + (rwSrc[2].green * ker[50].green) +
                   (rwSrc[3].green * ker[51].green) + (rwSrc[4].green * ker[52].green) + (rwSrc[5].green * ker[53].green) +
                   (rwSrc[6].green * ker[54].green) + (rwSrc[7].green * ker[55].green);

            res3 += (rwSrc[0].blue * ker[48].blue) + (rwSrc[1].blue * ker[49].blue) + (rwSrc[2].blue * ker[50].blue) +
                   (rwSrc[3].blue * ker[51].blue) + (rwSrc[4].blue * ker[52].blue) + (rwSrc[5].blue * ker[53].blue) +
                   (rwSrc[6].blue * ker[54].blue) + (rwSrc[7].blue * ker[55].blue);
            // Even
            rwSrc += (dim << 1);

            res += (rwSrc2[0].red * ker[56].red) + (rwSrc2[1].red * ker[57].red) + (rwSrc2[2].red * ker[58].red) +
                   (rwSrc2[3].red * ker[59].red) + (rwSrc2[4].red * ker[60].red) + (rwSrc2[5].red * ker[61].red) +
                   (rwSrc2[6].red * ker[62].red) + (rwSrc2[7].red * ker[63].red);

            res2 += (rwSrc2[0].green * ker[56].green) + (rwSrc2[1].green * ker[57].green) + (rwSrc2[2].green * ker[58].green) +
                   (rwSrc2[3].green * ker[59].green) + (rwSrc2[4].green * ker[60].green) + (rwSrc2[5].green * ker[61].green) +
                   (rwSrc2[6].green * ker[62].green) + (rwSrc2[7].green * ker[63].green);

            res3 += (rwSrc2[0].blue * ker[56].blue) + (rwSrc2[1].blue * ker[57].blue) + (rwSrc2[2].blue * ker[58].blue) +
                   (rwSrc2[3].blue * ker[59].blue) + (rwSrc2[4].blue * ker[60].blue) + (rwSrc2[5].blue * ker[61].blue) +
                   (rwSrc2[6].blue * ker[62].blue) + (rwSrc2[7].blue * ker[63].blue);


            ++tmpSrc;
            *rwDst++ = res + res2 + res3;
        }
        src += dim;
        dst += dim;
    }
}

/*
 * convolution - Your current working version of convolution
 * IMPORTANT: This is the version you will be graded on
 */
char convolution_descr[] = "Convolution: Current working version";
void convolution(int dim, pixel *src, pixel *ker, unsigned *dst)
{
    convolution_mahdi(dim, src, ker,dst);
// 
//     int i, j, k;
//     for (i = 0; i < dim - 8 + 1; i++)
//         for (j = 0; j < dim - 8 + 1; j++)
//         {
//             int sum = 0;
//             pixel *kerPixel = ker;
//             for (k = 0; k < 8; k++)
//             {
//                 pixel *srcPixel = src + RIDX((i + k), j, dim);
// 
//                 int redc0 = srcPixel->red * kerPixel->red;
//                 int greenc0 = srcPixel->green * kerPixel->green;
//                 int bluec0 = srcPixel->blue * kerPixel->blue;
// 
//                 kerPixel += 1;
//                 srcPixel += 1;
// 
//                 int redc1 = srcPixel->red * kerPixel->red;
//                 int greenc1 = srcPixel->green * kerPixel->green;
//                 int bluec1 = srcPixel->blue * kerPixel->blue;
// 
//                 int sumc0 = redc0 + greenc0;
//                 int sumc1 = redc1 + greenc1;
//                 sum += sumc0 + bluec0;
//                 sum += sumc1 + bluec1;
// 
//                 kerPixel += 1;
//                 srcPixel += 1;
// 
//                 int redc2 = srcPixel->red * kerPixel->red;
//                 int greenc2 = srcPixel->green * kerPixel->green;
//                 int bluec2 = srcPixel->blue * kerPixel->blue;
// 
//                 kerPixel += 1;
//                 srcPixel += 1;
// 
//                 int redc3 = srcPixel->red * kerPixel->red;
//                 int greenc3 = srcPixel->green * kerPixel->green;
//                 int bluec3 = srcPixel->blue * kerPixel->blue;
// 
//                 int sumc2 = redc2 + greenc2;
//                 int sumc3 = redc3 + greenc3;
// 
//                 sum += sumc2 + bluec2;
//                 sum += sumc3 + bluec3;
// 
//                 kerPixel += 1;
//                 srcPixel += 1;
// 
//                 int redc4 = srcPixel->red * kerPixel->red;
//                 int greenc4 = srcPixel->green * kerPixel->green;
//                 int bluec4 = srcPixel->blue * kerPixel->blue;
// 
//                 kerPixel += 1;
//                 srcPixel += 1;
// 
//                 int redc5 = srcPixel->red * kerPixel->red;
//                 int greenc5 = srcPixel->green * kerPixel->green;
//                 int bluec5 = srcPixel->blue * kerPixel->blue;
// 
//                 int sumc4 = redc4 + greenc4;
//                 int sumc5 = redc5 + greenc5;
//                 sum += sumc4 + bluec4;
//                 sum += sumc5 + bluec5;
// 
//                 kerPixel += 1;
//                 srcPixel += 1;
// 
//                 int redc6 = srcPixel->red * kerPixel->red;
//                 int greenc6 = srcPixel->green * kerPixel->green;
//                 int bluec6 = srcPixel->blue * kerPixel->blue;
// 
//                 kerPixel += 1;
//                 srcPixel += 1;
// 
//                 int redc7 = srcPixel->red * kerPixel->red;
//                 int greenc7 = srcPixel->green * kerPixel->green;
//                 int bluec7 = srcPixel->blue * kerPixel->blue;
// 
//                 kerPixel += 1;
// 
//                 int sumc6 = redc6 + greenc6;
//                 int sumc7 = redc7 + greenc7;
// 
//                 sum += sumc6 + bluec6;
//                 sum += sumc7 + bluec7;
//             }
//             dst[RIDX(i, j, dim)] = sum;
//         }
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
    add_conv_function(&convolution_mahdi, convolution_mahdi_descr);
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
