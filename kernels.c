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
    int i,j;
    int limit = dim - 7;
    pixel *src_ptr;
    pixel *loop_ptr, *loop_ptr1;
    unsigned *dst_pointer;
    int res, res2, res3;
    for(i = 0; i < limit; i++) 
    {
        src_ptr = src; 
        dst_pointer = dst;
        for(j = 0; j < limit; j++) 
        {
            loop_ptr = src_ptr;
            loop_ptr1 = src_ptr + dim;

            res = (loop_ptr[0].red * ker[0].red) + (loop_ptr[1].red * ker[1].red) + (loop_ptr[2].red * ker[2].red) +
                   (loop_ptr[3].red * ker[3].red) + (loop_ptr[4].red * ker[4].red) + (loop_ptr[5].red * ker[5].red) +
                   (loop_ptr[6].red * ker[6].red) + (loop_ptr[7].red * ker[7].red);

            res2 = (loop_ptr[0].green * ker[0].green) + (loop_ptr[1].green * ker[1].green) + (loop_ptr[2].green * ker[2].green) +
                   (loop_ptr[3].green * ker[3].green) + (loop_ptr[4].green * ker[4].green) + (loop_ptr[5].green * ker[5].green) +
                   (loop_ptr[6].green * ker[6].green) + (loop_ptr[7].green * ker[7].green);

            res3 = (loop_ptr[0].blue * ker[0].blue) + (loop_ptr[1].blue * ker[1].blue) + (loop_ptr[2].blue * ker[2].blue) +
                   (loop_ptr[3].blue * ker[3].blue) + (loop_ptr[4].blue * ker[4].blue) + (loop_ptr[5].blue * ker[5].blue) +
                   (loop_ptr[6].blue * ker[6].blue) + (loop_ptr[7].blue * ker[7].blue);
            // Even
            loop_ptr += (dim << 1);

            res += (loop_ptr1[0].red * ker[8].red) + (loop_ptr1[1].red * ker[9].red) + (loop_ptr1[2].red * ker[10].red) +
                   (loop_ptr1[3].red * ker[11].red) + (loop_ptr1[4].red * ker[12].red) + (loop_ptr1[5].red * ker[13].red) +
                   (loop_ptr1[6].red * ker[14].red) + (loop_ptr1[7].red * ker[15].red);

            res2 += (loop_ptr1[0].green * ker[8].green) + (loop_ptr1[1].green * ker[9].green) + (loop_ptr1[2].green * ker[10].green) +
                   (loop_ptr1[3].green * ker[11].green) + (loop_ptr1[4].green * ker[12].green) + (loop_ptr1[5].green * ker[13].green) +
                   (loop_ptr1[6].green * ker[14].green) + (loop_ptr1[7].green * ker[15].green);

            res3 += (loop_ptr1[0].blue * ker[8].blue) + (loop_ptr1[1].blue * ker[9].blue) + (loop_ptr1[2].blue * ker[10].blue) +
                   (loop_ptr1[3].blue * ker[11].blue) + (loop_ptr1[4].blue * ker[12].blue) + (loop_ptr1[5].blue * ker[13].blue) +
                   (loop_ptr1[6].blue * ker[14].blue) + (loop_ptr1[7].blue * ker[15].blue);
            // Odd
            loop_ptr1 += (dim << 1);

            res += (loop_ptr[0].red * ker[16].red) + (loop_ptr[1].red * ker[17].red) + (loop_ptr[2].red * ker[18].red) +
                   (loop_ptr[3].red * ker[19].red) + (loop_ptr[4].red * ker[20].red) + (loop_ptr[5].red * ker[21].red) +
                   (loop_ptr[6].red * ker[22].red) + (loop_ptr[7].red * ker[23].red);

            res2 += (loop_ptr[0].green * ker[16].green) + (loop_ptr[1].green * ker[17].green) + (loop_ptr[2].green * ker[18].green) +
                   (loop_ptr[3].green * ker[19].green) + (loop_ptr[4].green * ker[20].green) + (loop_ptr[5].green * ker[21].green) +
                   (loop_ptr[6].green * ker[22].green) + (loop_ptr[7].green * ker[23].green);

            res3 += (loop_ptr[0].blue * ker[16].blue) + (loop_ptr[1].blue * ker[17].blue) + (loop_ptr[2].blue * ker[18].blue) +
                   (loop_ptr[3].blue * ker[19].blue) + (loop_ptr[4].blue * ker[20].blue) + (loop_ptr[5].blue * ker[21].blue) +
                   (loop_ptr[6].blue * ker[22].blue) + (loop_ptr[7].blue * ker[23].blue);
            // Even
            loop_ptr += (dim << 1);

            res += (loop_ptr1[0].red * ker[24].red) + (loop_ptr1[1].red * ker[25].red) + (loop_ptr1[2].red * ker[26].red) +
                   (loop_ptr1[3].red * ker[27].red) + (loop_ptr1[4].red * ker[28].red) + (loop_ptr1[5].red * ker[29].red) +
                   (loop_ptr1[6].red * ker[30].red) + (loop_ptr1[7].red * ker[31].red);

            res2 += (loop_ptr1[0].green * ker[24].green) + (loop_ptr1[1].green * ker[25].green) + (loop_ptr1[2].green * ker[26].green) +
                   (loop_ptr1[3].green * ker[27].green) + (loop_ptr1[4].green * ker[28].green) + (loop_ptr1[5].green * ker[29].green) +
                   (loop_ptr1[6].green * ker[30].green) + (loop_ptr1[7].green * ker[31].green);

            res3 += (loop_ptr1[0].blue * ker[24].blue) + (loop_ptr1[1].blue * ker[25].blue) + (loop_ptr1[2].blue * ker[26].blue) +
                   (loop_ptr1[3].blue * ker[27].blue) + (loop_ptr1[4].blue * ker[28].blue) + (loop_ptr1[5].blue * ker[29].blue) +
                   (loop_ptr1[6].blue * ker[30].blue) + (loop_ptr1[7].blue * ker[31].blue);
            // Odd
            loop_ptr1 += (dim << 1);

            res += (loop_ptr[0].red * ker[32].red) + (loop_ptr[1].red * ker[33].red) + (loop_ptr[2].red * ker[34].red) +
                   (loop_ptr[3].red * ker[35].red) + (loop_ptr[4].red * ker[36].red) + (loop_ptr[5].red * ker[37].red) +
                   (loop_ptr[6].red * ker[38].red) + (loop_ptr[7].red * ker[39].red);

            res2 += (loop_ptr[0].green * ker[32].green) + (loop_ptr[1].green * ker[33].green) + (loop_ptr[2].green * ker[34].green) +
                   (loop_ptr[3].green * ker[35].green) + (loop_ptr[4].green * ker[36].green) + (loop_ptr[5].green * ker[37].green) +
                   (loop_ptr[6].green * ker[38].green) + (loop_ptr[7].green * ker[39].green);

            res3 += (loop_ptr[0].blue * ker[32].blue) + (loop_ptr[1].blue * ker[33].blue) + (loop_ptr[2].blue * ker[34].blue) +
                   (loop_ptr[3].blue * ker[35].blue) + (loop_ptr[4].blue * ker[36].blue) + (loop_ptr[5].blue * ker[37].blue) +
                   (loop_ptr[6].blue * ker[38].blue) + (loop_ptr[7].blue * ker[39].blue);
            // Even
            loop_ptr += (dim << 1);

            res += (loop_ptr1[0].red * ker[40].red) + (loop_ptr1[1].red * ker[41].red) + (loop_ptr1[2].red * ker[42].red) +
                   (loop_ptr1[3].red * ker[43].red) + (loop_ptr1[4].red * ker[44].red) + (loop_ptr1[5].red * ker[45].red) +
                   (loop_ptr1[6].red * ker[46].red) + (loop_ptr1[7].red * ker[47].red);

            res2 += (loop_ptr1[0].green * ker[40].green) + (loop_ptr1[1].green * ker[41].green) + (loop_ptr1[2].green * ker[42].green) +
                   (loop_ptr1[3].green * ker[43].green) + (loop_ptr1[4].green * ker[44].green) + (loop_ptr1[5].green * ker[45].green) +
                   (loop_ptr1[6].green * ker[46].green) + (loop_ptr1[7].green * ker[47].green);

            res3 += (loop_ptr1[0].blue * ker[40].blue) + (loop_ptr1[1].blue * ker[41].blue) + (loop_ptr1[2].blue * ker[42].blue) +
                   (loop_ptr1[3].blue * ker[43].blue) + (loop_ptr1[4].blue * ker[44].blue) + (loop_ptr1[5].blue * ker[45].blue) +
                   (loop_ptr1[6].blue * ker[46].blue) + (loop_ptr1[7].blue * ker[47].blue);
            // Odd
            loop_ptr1 += (dim << 1);

            res += (loop_ptr[0].red * ker[48].red) + (loop_ptr[1].red * ker[49].red) + (loop_ptr[2].red * ker[50].red) +
                   (loop_ptr[3].red * ker[51].red) + (loop_ptr[4].red * ker[52].red) + (loop_ptr[5].red * ker[53].red) +
                   (loop_ptr[6].red * ker[54].red) + (loop_ptr[7].red * ker[55].red);

            res2 += (loop_ptr[0].green * ker[48].green) + (loop_ptr[1].green * ker[49].green) + (loop_ptr[2].green * ker[50].green) +
                   (loop_ptr[3].green * ker[51].green) + (loop_ptr[4].green * ker[52].green) + (loop_ptr[5].green * ker[53].green) +
                   (loop_ptr[6].green * ker[54].green) + (loop_ptr[7].green * ker[55].green);

            res3 += (loop_ptr[0].blue * ker[48].blue) + (loop_ptr[1].blue * ker[49].blue) + (loop_ptr[2].blue * ker[50].blue) +
                   (loop_ptr[3].blue * ker[51].blue) + (loop_ptr[4].blue * ker[52].blue) + (loop_ptr[5].blue * ker[53].blue) +
                   (loop_ptr[6].blue * ker[54].blue) + (loop_ptr[7].blue * ker[55].blue);
            // Even
            loop_ptr += (dim << 1);

            res += (loop_ptr1[0].red * ker[56].red) + (loop_ptr1[1].red * ker[57].red) + (loop_ptr1[2].red * ker[58].red) +
                   (loop_ptr1[3].red * ker[59].red) + (loop_ptr1[4].red * ker[60].red) + (loop_ptr1[5].red * ker[61].red) +
                   (loop_ptr1[6].red * ker[62].red) + (loop_ptr1[7].red * ker[63].red);

            res2 += (loop_ptr1[0].green * ker[56].green) + (loop_ptr1[1].green * ker[57].green) + (loop_ptr1[2].green * ker[58].green) +
                   (loop_ptr1[3].green * ker[59].green) + (loop_ptr1[4].green * ker[60].green) + (loop_ptr1[5].green * ker[61].green) +
                   (loop_ptr1[6].green * ker[62].green) + (loop_ptr1[7].green * ker[63].green);

            res3 += (loop_ptr1[0].blue * ker[56].blue) + (loop_ptr1[1].blue * ker[57].blue) + (loop_ptr1[2].blue * ker[58].blue) +
                   (loop_ptr1[3].blue * ker[59].blue) + (loop_ptr1[4].blue * ker[60].blue) + (loop_ptr1[5].blue * ker[61].blue) +
                   (loop_ptr1[6].blue * ker[62].blue) + (loop_ptr1[7].blue * ker[63].blue);


            *dst_pointer = res + res2 + res3;
            src_ptr++;
            dst_pointer++;
        }
        src += dim;
        dst += dim;
    }
}

char convolution_mahdi_v2_descr[] = "CONVOLUTION: MAHDIIII v2!";
void convolution_mahdi_v2(int dim, pixel *src, pixel *ker, unsigned *dst) {
    int i,j;
    int limit = dim - 7;
    pixel *src_ptr, *src_back = src;
    pixel *loop_ptr, *loop_ptr1;
    unsigned *dst_pointer;
    int res;
    unsigned * dst_back = dst;

    int ker0_red, ker1_red, ker2_red, ker3_red, ker4_red, ker5_red, ker6_red, ker7_red, ker8_red;
    int ker9_red, ker10_red, ker11_red, ker12_red, ker13_red, ker14_red, ker15_red, ker16_red;
    int ker17_red, ker18_red, ker19_red, ker20_red, ker21_red, ker22_red, ker23_red, ker24_red;
    int ker25_red, ker26_red, ker27_red, ker28_red, ker29_red, ker30_red, ker31_red, ker32_red;
    int ker33_red, ker34_red, ker35_red, ker36_red, ker37_red, ker38_red, ker39_red, ker40_red;
    int ker41_red, ker42_red, ker43_red, ker44_red, ker45_red, ker46_red, ker47_red, ker48_red;
    int ker49_red, ker50_red, ker51_red, ker52_red, ker53_red, ker54_red, ker55_red, ker56_red;
    int ker57_red, ker58_red, ker59_red, ker60_red, ker61_red, ker62_red, ker63_red;
    
    ker0_red = ker[0].red; ker1_red = ker[1].red; ker2_red = ker[2].red; ker3_red = ker[3].red; 
    ker4_red = ker[4].red; ker5_red = ker[5].red; ker6_red = ker[6].red; ker7_red = ker[7].red;
    ker8_red = ker[8].red; ker9_red = ker[9].red; ker10_red = ker[10].red; ker11_red = ker[11].red;
    ker12_red = ker[12].red; ker13_red = ker[13].red; ker14_red = ker[14].red; ker15_red = ker[15].red;

    ker16_red = ker[16].red; ker17_red = ker[17].red; ker18_red = ker[18].red; ker19_red = ker[19].red; 
    ker20_red = ker[20].red; ker21_red = ker[21].red; ker22_red = ker[22].red; ker23_red = ker[23].red;
    ker24_red = ker[24].red; ker25_red = ker[25].red; ker26_red = ker[26].red; ker27_red = ker[27].red;
    ker28_red = ker[28].red; ker29_red = ker[29].red; ker30_red = ker[30].red; ker31_red = ker[31].red;

    ker32_red = ker[32].red; ker33_red = ker[33].red; ker34_red = ker[34].red; ker35_red = ker[35].red; 
    ker36_red = ker[36].red; ker37_red = ker[37].red; ker38_red = ker[38].red; ker39_red = ker[39].red;
    ker40_red = ker[40].red; ker41_red = ker[41].red; ker42_red = ker[42].red; ker43_red = ker[43].red;
    ker44_red = ker[44].red; ker45_red = ker[45].red; ker46_red = ker[46].red; ker47_red = ker[47].red;

    ker48_red = ker[48].red; ker49_red = ker[49].red; ker50_red = ker[50].red; ker51_red = ker[51].red; 
    ker52_red = ker[52].red; ker53_red = ker[53].red; ker54_red = ker[54].red; ker55_red = ker[55].red;
    ker56_red = ker[56].red; ker57_red = ker[57].red; ker58_red = ker[58].red; ker59_red = ker[59].red;
    ker60_red = ker[60].red; ker61_red = ker[61].red; ker62_red = ker[62].red; ker63_red = ker[63].red;

    for(i = 0; i != limit; i++) 
    {
        src_ptr = src; 
        dst_pointer = dst;
        for(j = 0; j != limit; j++) 
        {
            loop_ptr = src_ptr;
            loop_ptr1 = src_ptr + dim;

            res = (loop_ptr[0].red * ker0_red) + (loop_ptr[1].red * ker1_red) + (loop_ptr[2].red * ker2_red) +
                   (loop_ptr[3].red * ker3_red) + (loop_ptr[4].red * ker4_red) + (loop_ptr[5].red * ker5_red) +
                   (loop_ptr[6].red * ker6_red) + (loop_ptr[7].red * ker7_red);

            // res2 = (loop_ptr[0].green * ker[0].green) + (loop_ptr[1].green * ker[1].green) + (loop_ptr[2].green * ker[2].green) +
            //        (loop_ptr[3].green * ker[3].green) + (loop_ptr[4].green * ker[4].green) + (loop_ptr[5].green * ker[5].green) +
            //        (loop_ptr[6].green * ker[6].green) + (loop_ptr[7].green * ker[7].green);

            // res3 = (loop_ptr[0].blue * ker[0].blue) + (loop_ptr[1].blue * ker[1].blue) + (loop_ptr[2].blue * ker[2].blue) +
            //        (loop_ptr[3].blue * ker[3].blue) + (loop_ptr[4].blue * ker[4].blue) + (loop_ptr[5].blue * ker[5].blue) +
            //        (loop_ptr[6].blue * ker[6].blue) + (loop_ptr[7].blue * ker[7].blue);
            // Even
            loop_ptr += (dim << 1);

            res += (loop_ptr1[0].red * ker8_red) + (loop_ptr1[1].red * ker9_red) + (loop_ptr1[2].red * ker10_red) +
                   (loop_ptr1[3].red * ker11_red) + (loop_ptr1[4].red * ker12_red) + (loop_ptr1[5].red * ker13_red) +
                   (loop_ptr1[6].red * ker14_red) + (loop_ptr1[7].red * ker15_red);

            // res2 += (loop_ptr1[0].green * ker[8].green) + (loop_ptr1[1].green * ker[9].green) + (loop_ptr1[2].green * ker[10].green) +
            //        (loop_ptr1[3].green * ker[11].green) + (loop_ptr1[4].green * ker[12].green) + (loop_ptr1[5].green * ker[13].green) +
            //        (loop_ptr1[6].green * ker[14].green) + (loop_ptr1[7].green * ker[15].green);

            // res3 += (loop_ptr1[0].blue * ker[8].blue) + (loop_ptr1[1].blue * ker[9].blue) + (loop_ptr1[2].blue * ker[10].blue) +
            //        (loop_ptr1[3].blue * ker[11].blue) + (loop_ptr1[4].blue * ker[12].blue) + (loop_ptr1[5].blue * ker[13].blue) +
            //        (loop_ptr1[6].blue * ker[14].blue) + (loop_ptr1[7].blue * ker[15].blue);
            // Odd
            loop_ptr1 += (dim << 1);

            res += (loop_ptr[0].red * ker16_red) + (loop_ptr[1].red * ker17_red) + (loop_ptr[2].red * ker18_red) +
                   (loop_ptr[3].red * ker19_red) + (loop_ptr[4].red * ker20_red) + (loop_ptr[5].red * ker21_red) +
                   (loop_ptr[6].red * ker22_red) + (loop_ptr[7].red * ker23_red);

            // res2 += (loop_ptr[0].green * ker[16].green) + (loop_ptr[1].green * ker[17].green) + (loop_ptr[2].green * ker[18].green) +
            //        (loop_ptr[3].green * ker[19].green) + (loop_ptr[4].green * ker[20].green) + (loop_ptr[5].green * ker[21].green) +
            //        (loop_ptr[6].green * ker[22].green) + (loop_ptr[7].green * ker[23].green);

            // res3 += (loop_ptr[0].blue * ker[16].blue) + (loop_ptr[1].blue * ker[17].blue) + (loop_ptr[2].blue * ker[18].blue) +
            //        (loop_ptr[3].blue * ker[19].blue) + (loop_ptr[4].blue * ker[20].blue) + (loop_ptr[5].blue * ker[21].blue) +
            //        (loop_ptr[6].blue * ker[22].blue) + (loop_ptr[7].blue * ker[23].blue);
            // Even
            loop_ptr += (dim << 1);

            res += (loop_ptr1[0].red * ker24_red) + (loop_ptr1[1].red * ker25_red) + (loop_ptr1[2].red * ker26_red) +
                   (loop_ptr1[3].red * ker27_red) + (loop_ptr1[4].red * ker28_red) + (loop_ptr1[5].red * ker29_red) +
                   (loop_ptr1[6].red * ker30_red) + (loop_ptr1[7].red * ker31_red);

            // res2 += (loop_ptr1[0].green * ker[24].green) + (loop_ptr1[1].green * ker[25].green) + (loop_ptr1[2].green * ker[26].green) +
            //        (loop_ptr1[3].green * ker[27].green) + (loop_ptr1[4].green * ker[28].green) + (loop_ptr1[5].green * ker[29].green) +
            //        (loop_ptr1[6].green * ker[30].green) + (loop_ptr1[7].green * ker[31].green);

            // res3 += (loop_ptr1[0].blue * ker[24].blue) + (loop_ptr1[1].blue * ker[25].blue) + (loop_ptr1[2].blue * ker[26].blue) +
            //        (loop_ptr1[3].blue * ker[27].blue) + (loop_ptr1[4].blue * ker[28].blue) + (loop_ptr1[5].blue * ker[29].blue) +
            //        (loop_ptr1[6].blue * ker[30].blue) + (loop_ptr1[7].blue * ker[31].blue);
            // Odd
            loop_ptr1 += (dim << 1);

            res += (loop_ptr[0].red * ker32_red) + (loop_ptr[1].red * ker33_red) + (loop_ptr[2].red * ker34_red) +
                   (loop_ptr[3].red * ker35_red) + (loop_ptr[4].red * ker36_red) + (loop_ptr[5].red * ker37_red) +
                   (loop_ptr[6].red * ker38_red) + (loop_ptr[7].red * ker39_red);

            // res2 += (loop_ptr[0].green * ker[32].green) + (loop_ptr[1].green * ker[33].green) + (loop_ptr[2].green * ker[34].green) +
            //        (loop_ptr[3].green * ker[35].green) + (loop_ptr[4].green * ker[36].green) + (loop_ptr[5].green * ker[37].green) +
            //        (loop_ptr[6].green * ker[38].green) + (loop_ptr[7].green * ker[39].green);

            // res3 += (loop_ptr[0].blue * ker[32].blue) + (loop_ptr[1].blue * ker[33].blue) + (loop_ptr[2].blue * ker[34].blue) +
            //        (loop_ptr[3].blue * ker[35].blue) + (loop_ptr[4].blue * ker[36].blue) + (loop_ptr[5].blue * ker[37].blue) +
            //        (loop_ptr[6].blue * ker[38].blue) + (loop_ptr[7].blue * ker[39].blue);
            // Even
            loop_ptr += (dim << 1);

            res += (loop_ptr1[0].red * ker40_red) + (loop_ptr1[1].red * ker41_red) + (loop_ptr1[2].red * ker42_red) +
                   (loop_ptr1[3].red * ker43_red) + (loop_ptr1[4].red * ker44_red) + (loop_ptr1[5].red * ker45_red) +
                   (loop_ptr1[6].red * ker46_red) + (loop_ptr1[7].red * ker47_red);

           // res2 += (loop_ptr1[0].green * ker[40].green) + (loop_ptr1[1].green * ker[41].green) + (loop_ptr1[2].green * ker[42].green) +
           //        (loop_ptr1[3].green * ker[43].green) + (loop_ptr1[4].green * ker[44].green) + (loop_ptr1[5].green * ker[45].green) +
           //        (loop_ptr1[6].green * ker[46].green) + (loop_ptr1[7].green * ker[47].green);

           // res3 += (loop_ptr1[0].blue * ker[40].blue) + (loop_ptr1[1].blue * ker[41].blue) + (loop_ptr1[2].blue * ker[42].blue) +
           //        (loop_ptr1[3].blue * ker[43].blue) + (loop_ptr1[4].blue * ker[44].blue) + (loop_ptr1[5].blue * ker[45].blue) +
           //        (loop_ptr1[6].blue * ker[46].blue) + (loop_ptr1[7].blue * ker[47].blue);
            // Odd
            loop_ptr1 += (dim << 1);

            res += (loop_ptr[0].red * ker48_red) + (loop_ptr[1].red * ker49_red) + (loop_ptr[2].red * ker50_red) +
                   (loop_ptr[3].red * ker51_red) + (loop_ptr[4].red * ker52_red) + (loop_ptr[5].red * ker53_red) +
                   (loop_ptr[6].red * ker54_red) + (loop_ptr[7].red * ker55_red);

           //  res2 += (loop_ptr[0].green * ker[48].green) + (loop_ptr[1].green * ker[49].green) + (loop_ptr[2].green * ker[50].green) +
           //         (loop_ptr[3].green * ker[51].green) + (loop_ptr[4].green * ker[52].green) + (loop_ptr[5].green * ker[53].green) +
           //         (loop_ptr[6].green * ker[54].green) + (loop_ptr[7].green * ker[55].green);

           //  res3 += (loop_ptr[0].blue * ker[48].blue) + (loop_ptr[1].blue * ker[49].blue) + (loop_ptr[2].blue * ker[50].blue) +
           //         (loop_ptr[3].blue * ker[51].blue) + (loop_ptr[4].blue * ker[52].blue) + (loop_ptr[5].blue * ker[53].blue) +
           //         (loop_ptr[6].blue * ker[54].blue) + (loop_ptr[7].blue * ker[55].blue);
            // Even
            loop_ptr += (dim << 1);

            res += (loop_ptr1[0].red * ker56_red) + (loop_ptr1[1].red * ker57_red) + (loop_ptr1[2].red * ker58_red) +
                   (loop_ptr1[3].red * ker59_red) + (loop_ptr1[4].red * ker60_red) + (loop_ptr1[5].red * ker61_red) +
                   (loop_ptr1[6].red * ker62_red) + (loop_ptr1[7].red * ker63_red);

           //  res2 += (loop_ptr1[0].green * ker[56].green) + (loop_ptr1[1].green * ker[57].green) + (loop_ptr1[2].green * ker[58].green) +
           //         (loop_ptr1[3].green * ker[59].green) + (loop_ptr1[4].green * ker[60].green) + (loop_ptr1[5].green * ker[61].green) +
           //         (loop_ptr1[6].green * ker[62].green) + (loop_ptr1[7].green * ker[63].green);

           //  res3 += (loop_ptr1[0].blue * ker[56].blue) + (loop_ptr1[1].blue * ker[57].blue) + (loop_ptr1[2].blue * ker[58].blue) +
           //         (loop_ptr1[3].blue * ker[59].blue) + (loop_ptr1[4].blue * ker[60].blue) + (loop_ptr1[5].blue * ker[61].blue) +
           //         (loop_ptr1[6].blue * ker[62].blue) + (loop_ptr1[7].blue * ker[63].blue);


            *dst_pointer = res;
            src_ptr++;
            dst_pointer++;
        }
        src += dim;
        dst += dim;
    }
    dst = dst_back;
    src = src_back;

    ker0_red = ker[0].green; ker1_red = ker[1].green; ker2_red = ker[2].green; ker3_red = ker[3].green; 
    ker4_red = ker[4].green; ker5_red = ker[5].green; ker6_red = ker[6].green; ker7_red = ker[7].green;
    ker8_red = ker[8].green; ker9_red = ker[9].green; ker10_red = ker[10].green; ker11_red = ker[11].green;
    ker12_red = ker[12].green; ker13_red = ker[13].green; ker14_red = ker[14].green; ker15_red = ker[15].green;

    ker16_red = ker[16].green; ker17_red = ker[17].green; ker18_red = ker[18].green; ker19_red = ker[19].green; 
    ker20_red = ker[20].green; ker21_red = ker[21].green; ker22_red = ker[22].green; ker23_red = ker[23].green;
    ker24_red = ker[24].green; ker25_red = ker[25].green; ker26_red = ker[26].green; ker27_red = ker[27].green;
    ker28_red = ker[28].green; ker29_red = ker[29].green; ker30_red = ker[30].green; ker31_red = ker[31].green;

    ker32_red = ker[32].green; ker33_red = ker[33].green; ker34_red = ker[34].green; ker35_red = ker[35].green; 
    ker36_red = ker[36].green; ker37_red = ker[37].green; ker38_red = ker[38].green; ker39_red = ker[39].green;
    ker40_red = ker[40].green; ker41_red = ker[41].green; ker42_red = ker[42].green; ker43_red = ker[43].green;
    ker44_red = ker[44].green; ker45_red = ker[45].green; ker46_red = ker[46].green; ker47_red = ker[47].green;

    ker48_red = ker[48].green; ker49_red = ker[49].green; ker50_red = ker[50].green; ker51_red = ker[51].green; 
    ker52_red = ker[52].green; ker53_red = ker[53].green; ker54_red = ker[54].green; ker55_red = ker[55].green;
    ker56_red = ker[56].green; ker57_red = ker[57].green; ker58_red = ker[58].green; ker59_red = ker[59].green;
    ker60_red = ker[60].green; ker61_red = ker[61].green; ker62_red = ker[62].green; ker63_red = ker[63].green;

    for(i = 0; i != limit; i++) 
    {
        src_ptr = src; 
        dst_pointer = dst;
        for(j = 0; j != limit; j++) 
        {
            loop_ptr = src_ptr;
            loop_ptr1 = src_ptr + dim;

            res = (loop_ptr[0].green * ker0_red) + (loop_ptr[1].green * ker1_red) + (loop_ptr[2].green * ker2_red) +
                   (loop_ptr[3].green * ker3_red) + (loop_ptr[4].green * ker4_red) + (loop_ptr[5].green * ker5_red) +
                   (loop_ptr[6].green * ker6_red) + (loop_ptr[7].green * ker7_red);

            // res2 = (loop_ptr[0].green * ker[0].green) + (loop_ptr[1].green * ker[1].green) + (loop_ptr[2].green * ker[2].green) +
            //        (loop_ptr[3].green * ker[3].green) + (loop_ptr[4].green * ker[4].green) + (loop_ptr[5].green * ker[5].green) +
            //        (loop_ptr[6].green * ker[6].green) + (loop_ptr[7].green * ker[7].green);

            // res3 = (loop_ptr[0].blue * ker[0].blue) + (loop_ptr[1].blue * ker[1].blue) + (loop_ptr[2].blue * ker[2].blue) +
            //        (loop_ptr[3].blue * ker[3].blue) + (loop_ptr[4].blue * ker[4].blue) + (loop_ptr[5].blue * ker[5].blue) +
            //        (loop_ptr[6].blue * ker[6].blue) + (loop_ptr[7].blue * ker[7].blue);
            // Even
            loop_ptr += (dim << 1);

            res += (loop_ptr1[0].green * ker8_red) + (loop_ptr1[1].green * ker9_red) + (loop_ptr1[2].green * ker10_red) +
                   (loop_ptr1[3].green * ker11_red) + (loop_ptr1[4].green * ker12_red) + (loop_ptr1[5].green * ker13_red) +
                   (loop_ptr1[6].green * ker14_red) + (loop_ptr1[7].green * ker15_red);

            // res2 += (loop_ptr1[0].green * ker[8].green) + (loop_ptr1[1].green * ker[9].green) + (loop_ptr1[2].green * ker[10].green) +
            //        (loop_ptr1[3].green * ker[11].green) + (loop_ptr1[4].green * ker[12].green) + (loop_ptr1[5].green * ker[13].green) +
            //        (loop_ptr1[6].green * ker[14].green) + (loop_ptr1[7].green * ker[15].green);

            // res3 += (loop_ptr1[0].blue * ker[8].blue) + (loop_ptr1[1].blue * ker[9].blue) + (loop_ptr1[2].blue * ker[10].blue) +
            //        (loop_ptr1[3].blue * ker[11].blue) + (loop_ptr1[4].blue * ker[12].blue) + (loop_ptr1[5].blue * ker[13].blue) +
            //        (loop_ptr1[6].blue * ker[14].blue) + (loop_ptr1[7].blue * ker[15].blue);
            // Odd
            loop_ptr1 += (dim << 1);

            res += (loop_ptr[0].green * ker16_red) + (loop_ptr[1].green * ker17_red) + (loop_ptr[2].green * ker18_red) +
                   (loop_ptr[3].green * ker19_red) + (loop_ptr[4].green * ker20_red) + (loop_ptr[5].green * ker21_red) +
                   (loop_ptr[6].green * ker22_red) + (loop_ptr[7].green * ker23_red);

            // res2 += (loop_ptr[0].green * ker[16].green) + (loop_ptr[1].green * ker[17].green) + (loop_ptr[2].green * ker[18].green) +
            //        (loop_ptr[3].green * ker[19].green) + (loop_ptr[4].green * ker[20].green) + (loop_ptr[5].green * ker[21].green) +
            //        (loop_ptr[6].green * ker[22].green) + (loop_ptr[7].green * ker[23].green);

            // res3 += (loop_ptr[0].blue * ker[16].blue) + (loop_ptr[1].blue * ker[17].blue) + (loop_ptr[2].blue * ker[18].blue) +
            //        (loop_ptr[3].blue * ker[19].blue) + (loop_ptr[4].blue * ker[20].blue) + (loop_ptr[5].blue * ker[21].blue) +
            //        (loop_ptr[6].blue * ker[22].blue) + (loop_ptr[7].blue * ker[23].blue);
            // Even
            loop_ptr += (dim << 1);

            res += (loop_ptr1[0].green * ker24_red) + (loop_ptr1[1].green * ker25_red) + (loop_ptr1[2].green * ker26_red) +
                   (loop_ptr1[3].green * ker27_red) + (loop_ptr1[4].green * ker28_red) + (loop_ptr1[5].green * ker29_red) +
                   (loop_ptr1[6].green * ker30_red) + (loop_ptr1[7].green * ker31_red);

            // res2 += (loop_ptr1[0].green * ker[24].green) + (loop_ptr1[1].green * ker[25].green) + (loop_ptr1[2].green * ker[26].green) +
            //        (loop_ptr1[3].green * ker[27].green) + (loop_ptr1[4].green * ker[28].green) + (loop_ptr1[5].green * ker[29].green) +
            //        (loop_ptr1[6].green * ker[30].green) + (loop_ptr1[7].green * ker[31].green);

            // res3 += (loop_ptr1[0].blue * ker[24].blue) + (loop_ptr1[1].blue * ker[25].blue) + (loop_ptr1[2].blue * ker[26].blue) +
            //        (loop_ptr1[3].blue * ker[27].blue) + (loop_ptr1[4].blue * ker[28].blue) + (loop_ptr1[5].blue * ker[29].blue) +
            //        (loop_ptr1[6].blue * ker[30].blue) + (loop_ptr1[7].blue * ker[31].blue);
            // Odd
            loop_ptr1 += (dim << 1);

            res += (loop_ptr[0].green * ker32_red) + (loop_ptr[1].green * ker33_red) + (loop_ptr[2].green * ker34_red) +
                   (loop_ptr[3].green * ker35_red) + (loop_ptr[4].green * ker36_red) + (loop_ptr[5].green * ker37_red) +
                   (loop_ptr[6].green * ker38_red) + (loop_ptr[7].green * ker39_red);

            // res2 += (loop_ptr[0].green * ker[32].green) + (loop_ptr[1].green * ker[33].green) + (loop_ptr[2].green * ker[34].green) +
            //        (loop_ptr[3].green * ker[35].green) + (loop_ptr[4].green * ker[36].green) + (loop_ptr[5].green * ker[37].green) +
            //        (loop_ptr[6].green * ker[38].green) + (loop_ptr[7].green * ker[39].green);

            // res3 += (loop_ptr[0].blue * ker[32].blue) + (loop_ptr[1].blue * ker[33].blue) + (loop_ptr[2].blue * ker[34].blue) +
            //        (loop_ptr[3].blue * ker[35].blue) + (loop_ptr[4].blue * ker[36].blue) + (loop_ptr[5].blue * ker[37].blue) +
            //        (loop_ptr[6].blue * ker[38].blue) + (loop_ptr[7].blue * ker[39].blue);
            // Even
            loop_ptr += (dim << 1);

            res += (loop_ptr1[0].green * ker40_red) + (loop_ptr1[1].green * ker41_red) + (loop_ptr1[2].green * ker42_red) +
                   (loop_ptr1[3].green * ker43_red) + (loop_ptr1[4].green * ker44_red) + (loop_ptr1[5].green * ker45_red) +
                   (loop_ptr1[6].green * ker46_red) + (loop_ptr1[7].green * ker47_red);

           // res2 += (loop_ptr1[0].green * ker[40].green) + (loop_ptr1[1].green * ker[41].green) + (loop_ptr1[2].green * ker[42].green) +
           //        (loop_ptr1[3].green * ker[43].green) + (loop_ptr1[4].green * ker[44].green) + (loop_ptr1[5].green * ker[45].green) +
           //        (loop_ptr1[6].green * ker[46].green) + (loop_ptr1[7].green * ker[47].green);

           // res3 += (loop_ptr1[0].blue * ker[40].blue) + (loop_ptr1[1].blue * ker[41].blue) + (loop_ptr1[2].blue * ker[42].blue) +
           //        (loop_ptr1[3].blue * ker[43].blue) + (loop_ptr1[4].blue * ker[44].blue) + (loop_ptr1[5].blue * ker[45].blue) +
           //        (loop_ptr1[6].blue * ker[46].blue) + (loop_ptr1[7].blue * ker[47].blue);
            // Odd
            loop_ptr1 += (dim << 1);

            res += (loop_ptr[0].green * ker48_red) + (loop_ptr[1].green * ker49_red) + (loop_ptr[2].green * ker50_red) +
                   (loop_ptr[3].green * ker51_red) + (loop_ptr[4].green * ker52_red) + (loop_ptr[5].green * ker53_red) +
                   (loop_ptr[6].green * ker54_red) + (loop_ptr[7].green * ker55_red);

           //  res2 += (loop_ptr[0].green * ker[48].green) + (loop_ptr[1].green * ker[49].green) + (loop_ptr[2].green * ker[50].green) +
           //         (loop_ptr[3].green * ker[51].green) + (loop_ptr[4].green * ker[52].green) + (loop_ptr[5].green * ker[53].green) +
           //         (loop_ptr[6].green * ker[54].green) + (loop_ptr[7].green * ker[55].green);

           //  res3 += (loop_ptr[0].blue * ker[48].blue) + (loop_ptr[1].blue * ker[49].blue) + (loop_ptr[2].blue * ker[50].blue) +
           //         (loop_ptr[3].blue * ker[51].blue) + (loop_ptr[4].blue * ker[52].blue) + (loop_ptr[5].blue * ker[53].blue) +
           //         (loop_ptr[6].blue * ker[54].blue) + (loop_ptr[7].blue * ker[55].blue);
            // Even
            loop_ptr += (dim << 1);

            res += (loop_ptr1[0].green * ker56_red) + (loop_ptr1[1].green * ker57_red) + (loop_ptr1[2].green * ker58_red) +
                   (loop_ptr1[3].green * ker59_red) + (loop_ptr1[4].green * ker60_red) + (loop_ptr1[5].green * ker61_red) +
                   (loop_ptr1[6].green * ker62_red) + (loop_ptr1[7].green * ker63_red);

           //  res2 += (loop_ptr1[0].green * ker[56].green) + (loop_ptr1[1].green * ker[57].green) + (loop_ptr1[2].green * ker[58].green) +
           //         (loop_ptr1[3].green * ker[59].green) + (loop_ptr1[4].green * ker[60].green) + (loop_ptr1[5].green * ker[61].green) +
           //         (loop_ptr1[6].green * ker[62].green) + (loop_ptr1[7].green * ker[63].green);

           //  res3 += (loop_ptr1[0].blue * ker[56].blue) + (loop_ptr1[1].blue * ker[57].blue) + (loop_ptr1[2].blue * ker[58].blue) +
           //         (loop_ptr1[3].blue * ker[59].blue) + (loop_ptr1[4].blue * ker[60].blue) + (loop_ptr1[5].blue * ker[61].blue) +
           //         (loop_ptr1[6].blue * ker[62].blue) + (loop_ptr1[7].blue * ker[63].blue);


            *dst_pointer += res;
            src_ptr++;
            dst_pointer++;
        }
        src += dim;
        dst += dim;
    }
    dst = dst_back;
    src = src_back;

    ker0_red = ker[0].blue; ker1_red = ker[1].blue; ker2_red = ker[2].blue; ker3_red = ker[3].blue; 
    ker4_red = ker[4].blue; ker5_red = ker[5].blue; ker6_red = ker[6].blue; ker7_red = ker[7].blue;
    ker8_red = ker[8].blue; ker9_red = ker[9].blue; ker10_red = ker[10].blue; ker11_red = ker[11].blue;
    ker12_red = ker[12].blue; ker13_red = ker[13].blue; ker14_red = ker[14].blue; ker15_red = ker[15].blue;

    ker16_red = ker[16].blue; ker17_red = ker[17].blue; ker18_red = ker[18].blue; ker19_red = ker[19].blue; 
    ker20_red = ker[20].blue; ker21_red = ker[21].blue; ker22_red = ker[22].blue; ker23_red = ker[23].blue;
    ker24_red = ker[24].blue; ker25_red = ker[25].blue; ker26_red = ker[26].blue; ker27_red = ker[27].blue;
    ker28_red = ker[28].blue; ker29_red = ker[29].blue; ker30_red = ker[30].blue; ker31_red = ker[31].blue;

    ker32_red = ker[32].blue; ker33_red = ker[33].blue; ker34_red = ker[34].blue; ker35_red = ker[35].blue; 
    ker36_red = ker[36].blue; ker37_red = ker[37].blue; ker38_red = ker[38].blue; ker39_red = ker[39].blue;
    ker40_red = ker[40].blue; ker41_red = ker[41].blue; ker42_red = ker[42].blue; ker43_red = ker[43].blue;
    ker44_red = ker[44].blue; ker45_red = ker[45].blue; ker46_red = ker[46].blue; ker47_red = ker[47].blue;

    ker48_red = ker[48].blue; ker49_red = ker[49].blue; ker50_red = ker[50].blue; ker51_red = ker[51].blue; 
    ker52_red = ker[52].blue; ker53_red = ker[53].blue; ker54_red = ker[54].blue; ker55_red = ker[55].blue;
    ker56_red = ker[56].blue; ker57_red = ker[57].blue; ker58_red = ker[58].blue; ker59_red = ker[59].blue;
    ker60_red = ker[60].blue; ker61_red = ker[61].blue; ker62_red = ker[62].blue; ker63_red = ker[63].blue;

    for(i = 0; i != limit; i++) 
    {
        src_ptr = src; 
        dst_pointer = dst;
        for(j = 0; j != limit; j++) 
        {
            loop_ptr = src_ptr;
            loop_ptr1 = src_ptr + dim;

            res = (loop_ptr[0].blue * ker0_red) + (loop_ptr[1].blue * ker1_red) + (loop_ptr[2].blue * ker2_red) +
                   (loop_ptr[3].blue * ker3_red) + (loop_ptr[4].blue * ker4_red) + (loop_ptr[5].blue * ker5_red) +
                   (loop_ptr[6].blue * ker6_red) + (loop_ptr[7].blue * ker7_red);

            // res2 = (loop_ptr[0].blue * ker[0].blue) + (loop_ptr[1].blue * ker[1].blue) + (loop_ptr[2].blue * ker[2].blue) +
            //        (loop_ptr[3].blue * ker[3].blue) + (loop_ptr[4].blue * ker[4].blue) + (loop_ptr[5].blue * ker[5].blue) +
            //        (loop_ptr[6].blue * ker[6].blue) + (loop_ptr[7].blue * ker[7].blue);

            // res3 = (loop_ptr[0].blue * ker[0].blue) + (loop_ptr[1].blue * ker[1].blue) + (loop_ptr[2].blue * ker[2].blue) +
            //        (loop_ptr[3].blue * ker[3].blue) + (loop_ptr[4].blue * ker[4].blue) + (loop_ptr[5].blue * ker[5].blue) +
            //        (loop_ptr[6].blue * ker[6].blue) + (loop_ptr[7].blue * ker[7].blue);
            // Even
            loop_ptr += (dim << 1);

            res += (loop_ptr1[0].blue * ker8_red) + (loop_ptr1[1].blue * ker9_red) + (loop_ptr1[2].blue * ker10_red) +
                   (loop_ptr1[3].blue * ker11_red) + (loop_ptr1[4].blue * ker12_red) + (loop_ptr1[5].blue * ker13_red) +
                   (loop_ptr1[6].blue * ker14_red) + (loop_ptr1[7].blue * ker15_red);

            // res2 += (loop_ptr1[0].blue * ker[8].blue) + (loop_ptr1[1].blue * ker[9].blue) + (loop_ptr1[2].blue * ker[10].blue) +
            //        (loop_ptr1[3].blue * ker[11].blue) + (loop_ptr1[4].blue * ker[12].blue) + (loop_ptr1[5].blue * ker[13].blue) +
            //        (loop_ptr1[6].blue * ker[14].blue) + (loop_ptr1[7].blue * ker[15].blue);

            // res3 += (loop_ptr1[0].blue * ker[8].blue) + (loop_ptr1[1].blue * ker[9].blue) + (loop_ptr1[2].blue * ker[10].blue) +
            //        (loop_ptr1[3].blue * ker[11].blue) + (loop_ptr1[4].blue * ker[12].blue) + (loop_ptr1[5].blue * ker[13].blue) +
            //        (loop_ptr1[6].blue * ker[14].blue) + (loop_ptr1[7].blue * ker[15].blue);
            // Odd
            loop_ptr1 += (dim << 1);

            res += (loop_ptr[0].blue * ker16_red) + (loop_ptr[1].blue * ker17_red) + (loop_ptr[2].blue * ker18_red) +
                   (loop_ptr[3].blue * ker19_red) + (loop_ptr[4].blue * ker20_red) + (loop_ptr[5].blue * ker21_red) +
                   (loop_ptr[6].blue * ker22_red) + (loop_ptr[7].blue * ker23_red);

            // res2 += (loop_ptr[0].blue * ker[16].blue) + (loop_ptr[1].blue * ker[17].blue) + (loop_ptr[2].blue * ker[18].blue) +
            //        (loop_ptr[3].blue * ker[19].blue) + (loop_ptr[4].blue * ker[20].blue) + (loop_ptr[5].blue * ker[21].blue) +
            //        (loop_ptr[6].blue * ker[22].blue) + (loop_ptr[7].blue * ker[23].blue);

            // res3 += (loop_ptr[0].blue * ker[16].blue) + (loop_ptr[1].blue * ker[17].blue) + (loop_ptr[2].blue * ker[18].blue) +
            //        (loop_ptr[3].blue * ker[19].blue) + (loop_ptr[4].blue * ker[20].blue) + (loop_ptr[5].blue * ker[21].blue) +
            //        (loop_ptr[6].blue * ker[22].blue) + (loop_ptr[7].blue * ker[23].blue);
            // Even
            loop_ptr += (dim << 1);

            res += (loop_ptr1[0].blue * ker24_red) + (loop_ptr1[1].blue * ker25_red) + (loop_ptr1[2].blue * ker26_red) +
                   (loop_ptr1[3].blue * ker27_red) + (loop_ptr1[4].blue * ker28_red) + (loop_ptr1[5].blue * ker29_red) +
                   (loop_ptr1[6].blue * ker30_red) + (loop_ptr1[7].blue * ker31_red);

            // res2 += (loop_ptr1[0].blue * ker[24].blue) + (loop_ptr1[1].blue * ker[25].blue) + (loop_ptr1[2].blue * ker[26].blue) +
            //        (loop_ptr1[3].blue * ker[27].blue) + (loop_ptr1[4].blue * ker[28].blue) + (loop_ptr1[5].blue * ker[29].blue) +
            //        (loop_ptr1[6].blue * ker[30].blue) + (loop_ptr1[7].blue * ker[31].blue);

            // res3 += (loop_ptr1[0].blue * ker[24].blue) + (loop_ptr1[1].blue * ker[25].blue) + (loop_ptr1[2].blue * ker[26].blue) +
            //        (loop_ptr1[3].blue * ker[27].blue) + (loop_ptr1[4].blue * ker[28].blue) + (loop_ptr1[5].blue * ker[29].blue) +
            //        (loop_ptr1[6].blue * ker[30].blue) + (loop_ptr1[7].blue * ker[31].blue);
            // Odd
            loop_ptr1 += (dim << 1);

            res += (loop_ptr[0].blue * ker32_red) + (loop_ptr[1].blue * ker33_red) + (loop_ptr[2].blue * ker34_red) +
                   (loop_ptr[3].blue * ker35_red) + (loop_ptr[4].blue * ker36_red) + (loop_ptr[5].blue * ker37_red) +
                   (loop_ptr[6].blue * ker38_red) + (loop_ptr[7].blue * ker39_red);

            // res2 += (loop_ptr[0].blue * ker[32].blue) + (loop_ptr[1].blue * ker[33].blue) + (loop_ptr[2].blue * ker[34].blue) +
            //        (loop_ptr[3].blue * ker[35].blue) + (loop_ptr[4].blue * ker[36].blue) + (loop_ptr[5].blue * ker[37].blue) +
            //        (loop_ptr[6].blue * ker[38].blue) + (loop_ptr[7].blue * ker[39].blue);

            // res3 += (loop_ptr[0].blue * ker[32].blue) + (loop_ptr[1].blue * ker[33].blue) + (loop_ptr[2].blue * ker[34].blue) +
            //        (loop_ptr[3].blue * ker[35].blue) + (loop_ptr[4].blue * ker[36].blue) + (loop_ptr[5].blue * ker[37].blue) +
            //        (loop_ptr[6].blue * ker[38].blue) + (loop_ptr[7].blue * ker[39].blue);
            // Even
            loop_ptr += (dim << 1);

            res += (loop_ptr1[0].blue * ker40_red) + (loop_ptr1[1].blue * ker41_red) + (loop_ptr1[2].blue * ker42_red) +
                   (loop_ptr1[3].blue * ker43_red) + (loop_ptr1[4].blue * ker44_red) + (loop_ptr1[5].blue * ker45_red) +
                   (loop_ptr1[6].blue * ker46_red) + (loop_ptr1[7].blue * ker47_red);

           // res2 += (loop_ptr1[0].blue * ker[40].blue) + (loop_ptr1[1].blue * ker[41].blue) + (loop_ptr1[2].blue * ker[42].blue) +
           //        (loop_ptr1[3].blue * ker[43].blue) + (loop_ptr1[4].blue * ker[44].blue) + (loop_ptr1[5].blue * ker[45].blue) +
           //        (loop_ptr1[6].blue * ker[46].blue) + (loop_ptr1[7].blue * ker[47].blue);

           // res3 += (loop_ptr1[0].blue * ker[40].blue) + (loop_ptr1[1].blue * ker[41].blue) + (loop_ptr1[2].blue * ker[42].blue) +
           //        (loop_ptr1[3].blue * ker[43].blue) + (loop_ptr1[4].blue * ker[44].blue) + (loop_ptr1[5].blue * ker[45].blue) +
           //        (loop_ptr1[6].blue * ker[46].blue) + (loop_ptr1[7].blue * ker[47].blue);
            // Odd
            loop_ptr1 += (dim << 1);

            res += (loop_ptr[0].blue * ker48_red) + (loop_ptr[1].blue * ker49_red) + (loop_ptr[2].blue * ker50_red) +
                   (loop_ptr[3].blue * ker51_red) + (loop_ptr[4].blue * ker52_red) + (loop_ptr[5].blue * ker53_red) +
                   (loop_ptr[6].blue * ker54_red) + (loop_ptr[7].blue * ker55_red);

           //  res2 += (loop_ptr[0].blue * ker[48].blue) + (loop_ptr[1].blue * ker[49].blue) + (loop_ptr[2].blue * ker[50].blue) +
           //         (loop_ptr[3].blue * ker[51].blue) + (loop_ptr[4].blue * ker[52].blue) + (loop_ptr[5].blue * ker[53].blue) +
           //         (loop_ptr[6].blue * ker[54].blue) + (loop_ptr[7].blue * ker[55].blue);

           //  res3 += (loop_ptr[0].blue * ker[48].blue) + (loop_ptr[1].blue * ker[49].blue) + (loop_ptr[2].blue * ker[50].blue) +
           //         (loop_ptr[3].blue * ker[51].blue) + (loop_ptr[4].blue * ker[52].blue) + (loop_ptr[5].blue * ker[53].blue) +
           //         (loop_ptr[6].blue * ker[54].blue) + (loop_ptr[7].blue * ker[55].blue);
            // Even
            loop_ptr += (dim << 1);

            res += (loop_ptr1[0].blue * ker56_red) + (loop_ptr1[1].blue * ker57_red) + (loop_ptr1[2].blue * ker58_red) +
                   (loop_ptr1[3].blue * ker59_red) + (loop_ptr1[4].blue * ker60_red) + (loop_ptr1[5].blue * ker61_red) +
                   (loop_ptr1[6].blue * ker62_red) + (loop_ptr1[7].blue * ker63_red);

           //  res2 += (loop_ptr1[0].green * ker[56].green) + (loop_ptr1[1].green * ker[57].green) + (loop_ptr1[2].green * ker[58].green) +
           //         (loop_ptr1[3].green * ker[59].green) + (loop_ptr1[4].green * ker[60].green) + (loop_ptr1[5].green * ker[61].green) +
           //         (loop_ptr1[6].green * ker[62].green) + (loop_ptr1[7].green * ker[63].green);

           //  res3 += (loop_ptr1[0].blue * ker[56].blue) + (loop_ptr1[1].blue * ker[57].blue) + (loop_ptr1[2].blue * ker[58].blue) +
           //         (loop_ptr1[3].blue * ker[59].blue) + (loop_ptr1[4].blue * ker[60].blue) + (loop_ptr1[5].blue * ker[61].blue) +
           //         (loop_ptr1[6].blue * ker[62].blue) + (loop_ptr1[7].blue * ker[63].blue);


            *dst_pointer += res;
            src_ptr++;
            dst_pointer++;
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
    convolution_mahdi_v2(dim, src, ker,dst);
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
    add_conv_function(&convolution_mahdi_v2, convolution_mahdi_v2_descr);
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
