#include <math.h>
#include "image.h"

float nn_interpolate(image im, float x, float y, int c)
{
    // TODO Fill in
    return get_pixel(im, round(x), round(y), c);
    // return 0;
}

image nn_resize(image im, int w, int h)
{
    // TODO Fill in (also fix that first line)
    image temp = make_image(w, h, im.c);
    for (int k = 0; k < im.c; k++)
    {
        for (int i = 0; i < w; i++)
        {
            float x_scale = (float)(i * im.w) / (float)w;
            for (int j = 0; j < h; j++)
            {
                float y_scale = (float)(j * im.h) / (float)h;
                float px = nn_interpolate(im, x_scale, y_scale, k);
                set_pixel(temp, i, j, k, px);
            }
        }
    }
    return temp;
}

float bilinear_interpolate(image im, float x, float y, int c)
{
    // TODO
    float x1, y1, x2, y2;
    float q11, q21, q12, q22;
    x1 = floor(x);
    y1 = floor(y);
    x2 = ceil(x);
    y2 = ceil(y);

    q11 = get_pixel(im, x1, y1, c);
    q21 = get_pixel(im, x2, y1, c);
    q12 = get_pixel(im, x1, y2, c);
    q22 = get_pixel(im, x2, y2, c);

    float R1 = ((x2 - x) / (x2 - x1)) * q11 + ((x - x1) / (x2 - x1)) * q21;
    float R2 = ((x2 - x) / (x2 - x1)) * q12 + ((x - x1) / (x2 - x1)) * q22;

    float P = ((y2 - y) / (y2 - y1)) * R1 + ((y - y1) / (y2 - y1)) * R2;
    return P;
}

image bilinear_resize(image im, int w, int h)
{
    // TODO
    image temp = make_image(w, h, im.c);
    float width_ratio = (float)im.w / w;
    float height_ratio = (float)im.h / h;

    float adjust_width = -0.5 + 0.5 * width_ratio;
    float adjust_height = -0.5 + 0.5 * height_ratio;
    for (int k = 0; k < im.c; k++)
    {
        for (int i = 0; i < w; i++)
        {
            float x_scale = (float)i * width_ratio + adjust_width;
            for (int j = 0; j < h; j++)
            {
                float y_scale = (float)j * height_ratio + adjust_height;
                float px = bilinear_interpolate(im, x_scale, y_scale, k);
                set_pixel(temp, i, j, k, px);
            }
        }
    }
    return temp;
}
