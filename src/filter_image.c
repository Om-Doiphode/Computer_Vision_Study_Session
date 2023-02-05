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
#include <math.h>

void l1_normalize(image im)
{
    // for (int c = 0; c < 3; c++)
    // {
    //     float sum = 0;
    //     for (int i = 0; i < im.w; i++)
    //     {
    //         for (int j = 0; j < im.h; j++)
    //         {
    //             sum += get_pixel(im, i, j, c);
    //         }
    //     }
    //     for (int i = 0; i < im.w; i++)
    //     {
    //         for (int j = 0; j < im.h; j++)
    //         {
    //             set_pixel(im, i, j, c, get_pixel(im, i, j, c) / sum);
    //         }
    //     }
    // }
    for (int i = 0; i < im.w; i++)
    {
        for (int j = 0; j < im.h; j++)
        {
            set_pixel(im, i, j, 0, get_pixel(im, i, j, 0) / (im.w * im.h));
        }
    }
}

image make_box_filter(int w)
{
    // TODO
    image temp = make_image(w, w, 1);
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
    int out_h = im.h - filter.h + 1; // Height of the output image
    int out_w = im.w - filter.w + 1; // Width of the output image
    image ret = make_image(out_w, out_h, im.c);
    if (filter.c == 1 && preserve == 1 && im.c == 3)
    {
        float val = 0;
        for (int c = 0; c < im.c; c++)
        {
            for (int i = 0; i < out_w; i++)
            {
                for (int j = 0; j < out_h; j++)
                {
                    val = 0;
                    for (int muli = 0; muli < filter.h; muli++)
                    {
                        for (int mulj = 0; mulj < filter.w; mulj++)
                        {
                            val += get_pixel(im, i + muli, j + mulj, c) * get_pixel(filter, muli, mulj, 0);
                        }
                    }
                    // These conditions are for preventing occurence of patches of high frequency elements in the output image
                    if (val > 1)
                        set_pixel(ret, i, j, c, 1);
                    else if (val < 0)
                        set_pixel(ret, i, j, c, 0);
                    else
                        set_pixel(ret, i, j, c, val);
                }
            }
        }
    }
    return ret;
}
image make_highpass_filter()
{
    // TODO
    image im = make_image(3, 3, 1);
    set_pixel(im, 0, 0, 0, 0);
    set_pixel(im, 1, 0, 0, -1);
    set_pixel(im, 2, 0, 0, 0);

    set_pixel(im, 0, 1, 0, -1);
    set_pixel(im, 1, 1, 0, 4);
    set_pixel(im, 2, 1, 0, -1);

    set_pixel(im, 0, 2, 0, 0);
    set_pixel(im, 1, 2, 0, -1);
    set_pixel(im, 2, 2, 0, 0);

    return im;
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
    image im = make_image(3, 3, 1);
    set_pixel(im, 0, 0, 0, -2);
    set_pixel(im, 1, 0, 0, -1);
    set_pixel(im, 2, 0, 0, 0);

    set_pixel(im, 0, 1, 0, -1);
    set_pixel(im, 1, 1, 0, 1);
    set_pixel(im, 2, 1, 0, 1);

    set_pixel(im, 0, 2, 0, 0);
    set_pixel(im, 1, 2, 0, 1);
    set_pixel(im, 2, 2, 0, 2);

    return im;
}

// Question 2.2.1: Which of these filters should we use preserve when we run our convolution and which ones should we not? Why?
// Answer: TODO

// Question 2.2.2: Do we have to do any post-processing for the above filters? Which ones and why?
// Answer: TODO

image make_gaussian_filter(float sigma)
{
    // TODO
    int size = sigma * 6 + 1;

    image kernel = make_image(size, size, 1);
    float r, s = 2.0 * sigma * sigma;

    // sum is for normalization
    float sum = 0.0;

    // generating (size x size) kernel
    for (int x = -size / 2; x <= size / 2; x++)
    {
        for (int y = -size / 2; y <= size / 2; y++)
        {
            r = sqrt(x * x + y * y);
            set_pixel(kernel, x + 2, y + 2, 0, (exp(-(r * r) / s)) / (M_PI * s));
            sum += get_pixel(kernel, x + 2, y + 2, 0);
        }
    }

    // normalising the Kernel
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            kernel.data[i + j * kernel.w + 0 * kernel.w * kernel.h] /= sum;
    return kernel;
}
image add_image(image a, image b)
{
    // TODO
    image temp = make_image(a.w, a.h, a.c);
    for (int c = 0; c < a.c; c++)
    {
        for (int i = 0; i < a.w; i++)
        {
            for (int j = 0; j < a.h; j++)
            {
                set_pixel(temp, i, j, c, (get_pixel(a, i, j, c) + get_pixel(b, i, j, c)));
            }
        }
    }
    return temp;
}

image sub_image(image a, image b)
{
    // TODO
    image temp = make_image(a.w, a.h, a.c);
    for (int c = 0; c < a.c; c++)
    {
        for (int i = 0; i < a.w; i++)
        {
            for (int j = 0; j < a.h; j++)
            {
                set_pixel(temp, i, j, c, (get_pixel(a, i, j, c) - get_pixel(b, i, j, c)));
            }
        }
    }
    return temp;
}

image make_gx_filter()
{
    // TODO
    image im = make_image(3, 3, 1);
    set_pixel(im, 0, 0, 0, -1);
    set_pixel(im, 1, 0, 0, 0);
    set_pixel(im, 2, 0, 0, 1);

    set_pixel(im, 0, 1, 0, -2);
    set_pixel(im, 1, 1, 0, 0);
    set_pixel(im, 2, 1, 0, 2);

    set_pixel(im, 0, 2, 0, -1);
    set_pixel(im, 1, 2, 0, 0);
    set_pixel(im, 2, 2, 0, 1);

    return im;
}

image make_gy_filter()
{
    // TODO
    image im = make_image(3, 3, 1);
    set_pixel(im, 0, 0, 0, 1);
    set_pixel(im, 1, 0, 0, 2);
    set_pixel(im, 2, 0, 0, 1);

    set_pixel(im, 0, 1, 0, 0);
    set_pixel(im, 1, 1, 0, 0);
    set_pixel(im, 2, 1, 0, 0);

    set_pixel(im, 0, 2, 0, -1);
    set_pixel(im, 1, 2, 0, -2);
    set_pixel(im, 2, 2, 0, -1);

    return im;
}

void feature_normalize(image im)
{
    // TODO
    float r_min = INT_MAX, r_max = INT_MIN, g_min = INT_MAX, g_max = INT_MIN, b_min = INT_MAX, b_max = INT_MIN;
    for (int c = 0; c < im.c; c++)
    {
        for (int i = 0; i < im.w; i++)
        {
            for (int j = 0; j < im.h; j++)
            {
                if (c == 0)
                {
                    if (get_pixel(im, i, j, c) < r_min)
                        r_min = get_pixel(im, i, j, c);
                    if (get_pixel(im, i, j, c) > r_max)
                        r_max = get_pixel(im, i, j, c);
                }
                if (c == 1)
                {
                    if (get_pixel(im, i, j, c) < g_min)
                        g_min = get_pixel(im, i, j, c);
                    if (get_pixel(im, i, j, c) > g_max)
                        g_max = get_pixel(im, i, j, c);
                }
                if (c == 2)
                {
                    if (get_pixel(im, i, j, c) < b_min)
                        b_min = get_pixel(im, i, j, c);
                    if (get_pixel(im, i, j, c) > b_max)
                        b_max = get_pixel(im, i, j, c);
                }
            }
        }
    }
    for (int c = 0; c < im.c; c++)
    {
        for (int i = 0; i < im.w; i++)
        {
            for (int j = 0; j < im.h; j++)
            {
                if (c == 0)
                {
                    float val = (float)(get_pixel(im, i, j, c) - r_min) / (r_max - r_min);
                    set_pixel(im, i, j, c, val);
                }
                if (c == 1)
                {
                    float val = (float)(get_pixel(im, i, j, c) - g_min) / (g_max - g_min);
                    set_pixel(im, i, j, c, val);
                }
                if (c == 2)
                {
                    float val = (float)(get_pixel(im, i, j, c) - b_min) / (b_max - b_min);
                    set_pixel(im, i, j, c, val);
                }
            }
        }
    }
}

image *sobel_image(image im)
{
    // TODO
    // return calloc(2, sizeof(image));
    image Gx = make_image(im.w, im.h, im.c);
    image Gy = make_image(im.w, im.h, im.c);
    image G = make_image(im.w, im.h, im.c);
    image theta = make_image(im.w, im.h, im.c);

    image *finalImage = calloc(2, sizeof(image));

    Gx = convolve_image(im, make_gx_filter(), 1);
    Gy = convolve_image(im, make_gy_filter(), 1);

    for (int c = 0; c < im.c; c++)
    {
        for (int i = 0; i < im.w; i++)
        {
            for (int j = 0; j < im.h; j++)
            {
                float gx_squared = pow(get_pixel(Gx, i, j, c), 2);
                float gy_squared = pow(get_pixel(Gy, i, j, c), 2);
                float val = sqrt(gx_squared + gy_squared);
                set_pixel(G, i, j, c, val);
                float angle = atan2f(get_pixel(Gy, i, j, c), get_pixel(Gx, i, j, c));
                set_pixel(theta, i, j, c, angle);
            }
        }
    }
    finalImage[0] = G;
    finalImage[1] = theta;

    return finalImage;
}

image colorize_sobel(image im)
{
    // TODO
    return make_image(1, 1, 1);
}
