#include "../inc/Editor.h"

// get the address of a pixel
unsigned int *get_pixel(t_img *img, int x, int y)
{
    return ((unsigned int *)(img->data + (y * img->size_line + x * (img->bpp / 8))));
}

// full color gradient
int color_gradient(float width, float x, int color) {

    int grade = x * (511.0 / width) - 256;

    int _r = ((color >> 16) & 0xff) + grade;
    int _g = ((color >> 8) & 0xff) + grade;
    int _b = (color & 0xff) + grade;
    _r < 0 && (_r = 0);
    _g < 0 && (_g = 0);
    _b < 0 && (_b = 0);
    _r > 255 && (_r = 255);
    _g > 255 && (_g = 255);
    _b > 255 && (_b = 255);
    return (_r << 16 | _g << 8 | _b);
}

int base_color() {

    int _r = rgb.r;
    int _g = rgb.g;
    int _b = rgb.b;
    _r < 0 && (_r = 0);
    _g < 0 && (_g = 0);
    _b < 0 && (_b = 0);
    _r > 255 && (_r = 255);
    _g > 255 && (_g = 255);
    _b > 255 && (_b = 255);
    return (_r << 16 | _g << 8 | _b);
}

int full_color() {

    int _r = rgb.r + rgb.shade - 256;
    int _g = rgb.g + rgb.shade - 256;
    int _b = rgb.b + rgb.shade - 256;
    _r < 0 && (_r = 0);
    _g < 0 && (_g = 0);
    _b < 0 && (_b = 0);
    _r > 255 && (_r = 255);
    _g > 255 && (_g = 255);
    _b > 255 && (_b = 255);
    return (_r << 16 | _g << 8 | _b);
}

int rgb_setter(int x)
{
    int _size = WIN_WIDTH - screen_info.middle_x / 2 - 100;
    if (x < _size)
        return 0;
    else if (x > _size + 200)
        return 255;
    else
        return (float)(x - _size) * 255.0 / 200.0;
}

int shade_setter(int x)
{
    int _size = WIN_WIDTH - screen_info.middle_x / 2 - 100;
    if (x < _size)
        return 0;
    else if (x > _size + 200)
        return 511;
    else
        return (float)(x - _size) * 511.0 / 200.0;
}