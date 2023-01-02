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

### V2


## Mahdi 



## Osama