#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <limits.h>
#include "image.h"
#define TWOPI 6.2831853
#define MIN INT_MAX
#define MAX INT_MIN
void l1_normalize(image im)
{
    for (int i = 0; i < im.w; i++)
    {
        for (int j = 0; j < im.h; j++)
        {
            set_pixel(im, i, j, 0, get_pixel(im, i, j, 0) / (im.h * im.w));
        }
    }
}

image make_box_filter(int w)
{
    // TODO
    image temp = make_image(w, w, 1);
    printf("filter_channel: %d", temp.c);
    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < w; j++)
        {
            set_pixel(temp, i, j, 0, 1);
        }
    }
    l1_normalize(temp);
    return temp;
}

image convolve_image(image im, image filter, int preserve)
{
    image res = make_image(im.w, im.h, im.c);
    if (filter.c == 1 && preserve == 1 && im.c == 3)
    {
        for (int i = 0; i < im.w; i++)
        {
            for (int j = 0; j < im.h; j++)
            {
                float val1 = 0;
                for (int k = 0; k < filter.w; k++)
                {
                    for (int l = 0; l < filter.h; l++)
                    {
                        val1 += get_pixel(filter, k, l, 0) * get_pixel(im, i - k, j - k, 0);
                        // printf("val1: %lf\n", val1);
                    }
                }
                set_pixel(res, i, j, 0, val1);
                val1 = 0;
                for (int k = 0; k < filter.w; k++)
                {
                    for (int l = 0; l < filter.h; l++)
                    {
                        val1 += get_pixel(filter, k, l, 0) * get_pixel(im, i - k, j - k, 1);
                        // printf("val1: %lf\n", val1);
                    }
                }
                set_pixel(res, i, j, 1, val1);
                val1 = 0;
                for (int k = 0; k < filter.w; k++)
                {
                    for (int l = 0; l < filter.h; l++)
                    {
                        val1 += get_pixel(filter, k, l, 0) * get_pixel(im, i - k, j - k, 2);
                        // printf("val1: %lf\n", val1);
                    }
                }
                set_pixel(res, i, j, 2, val1);
            }
        }
    }
    return res;
}

image make_highpass_filter()
{
    // TODO
    return make_image(1, 1, 1);
}

image make_sharpen_filter()
{
    // TODO
    image im = make_image(3, 3, 1);
    set_pixel(im, 0, 0, 0, 0);
    set_pixel(im, 1, 0, 0, -1);
    set_pixel(im, 2, 0, 0, 0);

    set_pixel(im, 0, 1, 0, -1);
    set_pixel(im, 1, 1, 0, 5);
    set_pixel(im, 2, 1, 0, -1);

    set_pixel(im, 0, 2, 0, 0);
    set_pixel(im, 1, 2, 0, -1);
    set_pixel(im, 2, 2, 0, 0);

    return im;
}

image make_emboss_filter()
{
    // TODO
    return make_image(1, 1, 1);
}

// Question 2.2.1: Which of these filters should we use preserve when we run our convolution and which ones should we not? Why?
// Answer: TODO

// Question 2.2.2: Do we have to do any post-processing for the above filters? Which ones and why?
// Answer: TODO

image make_gaussian_filter(float sigma)
{
    // TODO
    return make_image(1, 1, 1);
}

image add_image(image a, image b)
{
    // TODO
    return make_image(1, 1, 1);
}

image sub_image(image a, image b)
{
    // TODO
    return make_image(1, 1, 1);
}

image make_gx_filter()
{
    // TODO
    return make_image(1, 1, 1);
}

image make_gy_filter()
{
    // TODO
    return make_image(1, 1, 1);
}

void feature_normalize(image im)
{
    // TODO
}

image *sobel_image(image im)
{
    // TODO
    return calloc(2, sizeof(image));
}

image colorize_sobel(image im)
{
    // TODO
    return make_image(1, 1, 1);
}
