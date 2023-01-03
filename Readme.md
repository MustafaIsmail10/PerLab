## Problem 1

### Original 
```C
    for(i = 0; i < dim-8+1; i++)
        for(j = 0; j < dim-8+1; j++) {
            dst[RIDX(i, j, dim)] = 0;
            for(k = 0; k < 8; k++)
                for(l = 0; l < 8; l++) {
                    dst[RIDX(i, j, dim)] += src[RIDX((i+k),(j+l), dim)].red * ker[RIDX(k, l, 8)].red;
                    dst[RIDX(i, j, dim)] += src[RIDX((i+k),(j+l), dim)].green * ker[RIDX(k, l, 8)].green;
                    dst[RIDX(i, j, dim)] += src[RIDX((i+k),(j+l), dim)].blue * ker[RIDX(k, l, 8)].blue;
                }

        }
```

### V1 

```C
void convolution(int dim, pixel *src, pixel *ker, unsigned *dst)
{

    int i, j, k, l;
    for (i = 0; i < dim - 8 + 1; i++)
        for (j = 0; j < dim - 8 + 1; j++)
        {
            int sum = 0;
            for (k = 0; k < 8; k++)
                for (l = 0; l < 8; l++)
                {
                    int srcPixel = RIDX((i + k), (j + l), dim);
                    int kerPixel = RIDX(k, l, 8);
                    sum += src[srcPixel].red * ker[kerPixel].red;
                    sum += src[srcPixel].green * ker[kerPixel].green;
                    sum += src[srcPixel].blue * ker[kerPixel].blue;
                }
            dst[RIDX(i, j, dim)] = sum;
        }
}

```

### V2_1.8

```C
/*
 * convolution - 1.8
 */
char convolutionMustafa1_8_descr[] = "Convolution: Mustafa v1";
void convolutionMustafa1_8(int dim, pixel *src, pixel *ker, unsigned *dst)
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
```
### V3

```C
char convolutionMustafaV1_descr[] = "Convolution: Mustafa v1";
void convolutionMustafaV1(int dim, pixel *src, pixel *ker, unsigned *dst)
{

    int i, j, k, l;

    for (i = 0; i < (dim - 7) * (dim - 7); i++)
    {
        dst[i] = 0;
    }

    for (i = 0; i < dim; i++)
        for (j = 0; j < dim; j++)
        {
            pixel *srcPixel = src + RIDX(i, j, dim);
            int diff = 0;
            for (k = i; k > i - 8 && k >= 0; k--, diff++)
            {
                pixel *kerPixel = ker + diff*8;
                for (l = j; l > j - 8 && l >= 0; l--)
                {
                    unsigned *dstVal = dst + RIDX(k, l, dim);
                    *dstVal += (srcPixel->red * kerPixel->red);
                    *dstVal += (srcPixel->green * kerPixel->green);
                    *dstVal += (srcPixel->blue * kerPixel->blue);
                    kerPixel +=1;
                }
            }
        }
}

```


### V4 (2.2)

```C
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
```

### V5 2.2


```C
/*
 * convolution - Mustafa v1
 */
char convolutionMustafaV1_descr[] = "Convolution: Mustafa v1";
void convolutionMustafaV1(int dim, pixel *src, pixel *ker, unsigned *dst)
{

    int i, j, k;
    pixel *kerPixel = ker;
    int limit = dim - 7;

    for (k = 0; k < 64; k++, kerPixel++)
    {
        int red = kerPixel->red;
        int blue = kerPixel->blue;
        int green = kerPixel->green;
        unsigned *dstPixel = dst;
        int temp = (k >> 3) * dim;
        pixel *start = src + (k % 8);

        for (i = 0; i < limit; i++)
        {
            pixel *srcPixel = start + temp;
            for (j = 0; j < limit - 7; j += 8)
            {

                int sum1 = srcPixel->red * red;
                int sum2 = (srcPixel + 1)->red * red;
                int sum3 = (srcPixel + 2)->red * red;
                int sum4 = (srcPixel + 3)->red * red;
                int sum5 = (srcPixel + 4)->red * red;
                int sum6 = (srcPixel + 5)->red * red;
                int sum7 = (srcPixel + 6)->red * red;
                int sum8 = (srcPixel + 7)->red * red;

                sum1 += srcPixel->green * green;
                sum2 += (srcPixel + 1)->green * green;
                sum3 += (srcPixel + 2)->green * green;
                sum4 += (srcPixel + 3)->green * green;
                sum5 += (srcPixel + 4)->green * green;
                sum6 += (srcPixel + 5)->green * green;
                sum7 += (srcPixel + 6)->green * green;
                sum8 += (srcPixel + 7)->green * green;

                sum1 += srcPixel->blue * blue;
                sum2 += (srcPixel + 1)->blue * blue;
                sum3 += (srcPixel + 2)->blue * blue;
                sum4 += (srcPixel + 3)->blue * blue;
                sum5 += (srcPixel + 4)->blue * blue;
                sum6 += (srcPixel + 5)->blue * blue;
                sum7 += (srcPixel + 6)->blue * blue;
                sum8 += (srcPixel + 7)->blue * blue;

                *dstPixel += sum1;
                *(dstPixel + 1) += sum2;
                *(dstPixel + 2) += sum3;
                *(dstPixel + 3) += sum4;
                *(dstPixel + 4) += sum5;
                *(dstPixel + 5) += sum6;
                *(dstPixel + 6) += sum7;
                *(dstPixel + 7) += sum8;

                dstPixel += 8;
                srcPixel += 8;
            }

            for (; j < limit; j++, dstPixel++)
            {

                int sum = srcPixel->red * red;
                sum += srcPixel->green * green;
                sum += srcPixel->blue * blue;

                *dstPixel += sum;
                srcPixel++;
            }
            dstPixel += 7;
            temp += dim;
        }
    }
}

```

### V5 1,9
```C

/*
 * convolution - Mustafa v1
 */
char convolutionMustafaV1_descr[] = "Convolution: Mustafa v1";
void convolutionMustafaV1(int dim, pixel *src, pixel *ker, unsigned *dst)
{

    int i, j, k;

    for (i = 0; i < 16; i++)
    {
        dst[i] = 0;
    }

    pixel *kerRow = ker;
    for (k = 0; k < 8; k += 1, kerRow += 8)
    {
        int crow = k * dim;
        for (i = k; i < dim - 7 + k ; i += 1, crow += dim)
        {
            for (j = 0; j < dim - 7; j++)
            {
                int sum = src[crow + j].red * kerRow[0].red + src[crow + j].green * kerRow[0].green + src[crow + j].blue * kerRow[0].blue;
                sum += src[crow + j + 1].red * kerRow[1].red + src[crow + j + 1].green * kerRow[1].green + src[crow + j + 1].blue * kerRow[1].blue;
                sum += src[crow + j + 2].red * kerRow[2].red + src[crow + j + 2].green * kerRow[2].green + src[crow + j + 2].blue * kerRow[2].blue;
                sum += src[crow + j + 3].red * kerRow[3].red + src[crow + j + 3].green * kerRow[3].green + src[crow + j + 3].blue * kerRow[3].blue;
                sum += src[crow + j + 4].red * kerRow[4].red + src[crow + j + 4].green * kerRow[4].green + src[crow + j + 4].blue * kerRow[4].blue;
                sum += src[crow + j + 5].red * kerRow[5].red + src[crow + j + 5].green * kerRow[5].green + src[crow + j + 5].blue * kerRow[5].blue;
                sum += src[crow + j + 6].red * kerRow[6].red + src[crow + j + 6].green * kerRow[6].green + src[crow + j + 6].blue * kerRow[6].blue;
                sum += src[crow + j + 7].red * kerRow[7].red + src[crow + j + 7].green * kerRow[7].green + src[crow + j + 7].blue * kerRow[7].blue;

                dst[crow - k * dim + j] += sum;
            }
        }
    }
}
```

### V6 1,6

```c

/*
 * convolution - Mustafa v1
 */
char convolutionMustafaV1_descr[] = "Convolution: Mustafa v1";
void convolutionMustafaV1(int dim, pixel *src, pixel *ker, unsigned *dst)
{

    int i, j, k;

    for (i = 0; i < dim - 8 + 1; i++)
        for (j = 0; j < dim - 8 + 1; j++)
        {
            int sum = 0;
            dst[RIDX(i, j, dim)] = 0;
            for (k = 0; k < 8; k++)
            {
                int srcL = RIDX((i + k), (j + 0), dim);
                sum += src[srcL].red * ker[RIDX(k, 0, 8)].red;
                sum += src[srcL].green * ker[RIDX(k, 0, 8)].green;
                sum += src[srcL].blue * ker[RIDX(k, 0, 8)].blue;
                srcL++;
                sum += src[srcL].red * ker[RIDX(k, 1, 8)].red;
                sum += src[srcL ].green * ker[RIDX(k, 1, 8)].green;
                sum += src[srcL].blue * ker[RIDX(k, 1, 8)].blue;
                srcL++;
                sum += src[srcL].red * ker[RIDX(k, 2, 8)].red;
                sum += src[srcL].green * ker[RIDX(k, 2, 8)].green;
                sum += src[srcL ].blue * ker[RIDX(k, 2, 8)].blue;
                srcL++;
                sum += src[srcL ].red * ker[RIDX(k, 3, 8)].red;
                sum += src[srcL ].green * ker[RIDX(k, 3, 8)].green;
                sum += src[srcL ].blue * ker[RIDX(k, 3, 8)].blue;
                srcL++;
                sum += src[srcL ].red * ker[RIDX(k, 4, 8)].red;
                sum += src[srcL ].green * ker[RIDX(k, 4, 8)].green;
                sum += src[srcL ].blue * ker[RIDX(k, 4, 8)].blue;
                srcL++;
                sum += src[srcL ].red * ker[RIDX(k, 5, 8)].red;
                sum += src[srcL ].green * ker[RIDX(k, 5, 8)].green;
                sum += src[srcL ].blue * ker[RIDX(k, 5, 8)].blue;
                srcL++;
                sum += src[srcL ].red * ker[RIDX(k, 6, 8)].red;
                sum += src[srcL ].green * ker[RIDX(k, 6, 8)].green;
                sum += src[srcL ].blue * ker[RIDX(k, 6, 8)].blue;
                srcL++;
                sum += src[srcL ].red * ker[RIDX(k, 7, 8)].red;
                sum += src[srcL ].green * ker[RIDX(k, 7, 8)].green;
                sum += src[srcL ].blue * ker[RIDX(k, 7, 8)].blue;
            }
            dst[RIDX(i, j, dim)] += sum;
        }
}
```



### v7 1,6 

```C
/*
 * convolution - Mustafa v1
 */
char convolutionMustafaV1_descr[] = "Convolution: Mustafa v1";
void convolutionMustafaV1(int dim, pixel *src, pixel *ker, unsigned *dst)
{

    int i, j, k;

    for (i = 0; i < 16; i++)
    {
        dst[i] = 0;
    }

    pixel *kerRow = ker;
    for (k = 0; k < 8; k += 1, kerRow += 8)
    {
        int crow = k * dim;
        for (i = k; i < dim - 7 + k; i += 1, crow += dim)
        {
            for (j = 0; j < dim - 7; j++)
            {
                int sumRed = src[crow + j].red * kerRow[0].red;
                int sumGreen = src[crow + j].green * kerRow[0].green;
                int sumBlue = src[crow + j].blue * kerRow[0].blue;

                sumRed += src[crow + j + 1].red * kerRow[1].red;
                sumGreen += src[crow + j + 1].green * kerRow[1].green;
                sumBlue += src[crow + j + 1].blue * kerRow[1].blue;

                sumRed += src[crow + j + 2].red * kerRow[2].red;
                sumGreen += src[crow + j + 2].green * kerRow[2].green;
                sumBlue += src[crow + j + 2].blue * kerRow[2].blue;

                sumRed += src[crow + j + 3].red * kerRow[3].red;
                sumGreen += src[crow + j + 3].green * kerRow[3].green;
                sumBlue += src[crow + j + 3].blue * kerRow[3].blue;

                sumRed += src[crow + j + 4].red * kerRow[4].red;
                sumGreen += src[crow + j + 4].green * kerRow[4].green;
                sumBlue += src[crow + j + 4].blue * kerRow[4].blue;

                sumRed += src[crow + j + 5].red * kerRow[5].red;
                sumGreen += src[crow + j + 5].green * kerRow[5].green;
                sumBlue += src[crow + j + 5].blue * kerRow[5].blue;

                sumRed += src[crow + j + 6].red * kerRow[6].red;
                sumGreen += src[crow + j + 6].green * kerRow[6].green;
                sumBlue += src[crow + j + 6].blue * kerRow[6].blue;

                sumRed += src[crow + j + 7].red * kerRow[7].red;
                sumGreen += src[crow + j + 7].green * kerRow[7].green;
                sumBlue += src[crow + j + 7].blue * kerRow[7].blue;

                dst[crow - k * dim + j] += sumRed+ sumGreen + sumBlue;
                // j++;
                // sum = src[crow + j].red * kerRow[0].red + src[crow + j].green * kerRow[0].green + src[crow + j].blue * kerRow[0].blue;
                // sum += src[crow + j + 1].red * kerRow[1].red + src[crow + j + 1].green * kerRow[1].green + src[crow + j + 1].blue * kerRow[1].blue;
                // sum += src[crow + j + 2].red * kerRow[2].red + src[crow + j + 2].green * kerRow[2].green + src[crow + j + 2].blue * kerRow[2].blue;
                // sum += src[crow + j + 3].red * kerRow[3].red + src[crow + j + 3].green * kerRow[3].green + src[crow + j + 3].blue * kerRow[3].blue;
                // sum += src[crow + j + 4].red * kerRow[4].red + src[crow + j + 4].green * kerRow[4].green + src[crow + j + 4].blue * kerRow[4].blue;
                // sum += src[crow + j + 5].red * kerRow[5].red + src[crow + j + 5].green * kerRow[5].green + src[crow + j + 5].blue * kerRow[5].blue;
                // sum += src[crow + j + 6].red * kerRow[6].red + src[crow + j + 6].green * kerRow[6].green + src[crow + j + 6].blue * kerRow[6].blue;
                // sum += src[crow + j + 7].red * kerRow[7].red + src[crow + j + 7].green * kerRow[7].green + src[crow + j + 7].blue * kerRow[7].blue;
                // dst[crow - k * dim + j] += sum;
            }
        }
    }
}
```