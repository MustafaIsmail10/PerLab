## Original 
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


## Mustafa 

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

## Mahdi 



## Osama