#include "../Editor.h"

// draw rectangle
void    draw_rect(t_img *img, int x, int y, int width, int height, unsigned int color) {

    for (int _y = y; _y < height && _y < WIN_HEIGHT; _y++)
        for (int _x = x; _x < width && _x < WIN_WIDTH; _x++)
            if (_x >= 0 && _y >= 0)
                *get_pixel(img, _x, _y) = color;
}

// draw rectangle gradient
void    draw_rect_gradient(t_img *img, int x, int y, int width, int height, int color) {

    for (int _y = y; _y < height; _y++)
        for (int _x = x; _x < width; _x++)
            *get_pixel(img, _x, _y) = color_gradient(width - x, _x - x, color);
}

// draw boarder
void    draw_border(t_img *img, int x, int y, int width, int height, int boarder, int boarder_size) {

    draw_rect(img, x, y - boarder_size, width, y, boarder); // up boarder
    draw_rect(img, x, height, width, height + boarder_size, boarder); // down boarder
    draw_rect(img, x - boarder_size, y - boarder_size, x, height + boarder_size, boarder); // left boarder
    draw_rect(img, width, y - boarder_size, width + boarder_size, height + boarder_size, boarder); // right boarder
}

// draw a rectangle with a boarder
void    draw_rect_bordered(int x, int y, int w, int h, int color, int max_colored_x, int boarder, int boarder_size) {

    draw_rect(&global_img, x, y, max_colored_x, h, color); // inside

    draw_border(&global_img, x, y, w, h, boarder, boarder_size);
    // draw_rect(&global_img, x, y - boarder_size, w, y, boarder); // up boarder
    // draw_rect(&global_img, x, h, w, h + boarder_size, boarder); // down boarder
    // draw_rect(&global_img, x - boarder_size, y - boarder_size, x, h + boarder_size, boarder); // left boarder
    // draw_rect(&global_img, w, y - boarder_size, w + boarder_size, h + boarder_size, boarder); // right boarder
}

// draw a rectangle with a boarder inside
void    draw_rect_bordered_in(int x, int y, int w, int h, int color, int max_colored_x, int boarder, int boarder_size) {

    draw_rect(&global_img, x, y, max_colored_x, h, color); // inside

    draw_border(&global_img, x, y, w, h, boarder, boarder_size);
    // draw_rect(&global_img, x, y, w, y + boarder_size, boarder); // up boarder
    // draw_rect(&global_img, x, h - boarder_size, w, h, boarder); // down boarder
    // draw_rect(&global_img, x, y - boarder_size, x + boarder_size, h + boarder_size, boarder); // left boarder
    // draw_rect(&global_img, w - boarder_size, y - boarder_size, w, h + boarder_size, boarder); // right boarder
}

// draw a rectangle with a boarder gradient
void    draw_rect_bordered_gradient(int x, int y, int w, int h, int color, int max_colored_x, int boarder, int boarder_size) {

    draw_rect_gradient(&global_img, x, y, max_colored_x, h, color); // inside

    draw_border(&global_img, x, y, w, h, boarder, boarder_size);
    // draw_rect(&global_img, x, y - boarder_size, w, y, boarder); // up boarder
    // draw_rect(&global_img, x, h, w, h + boarder_size, boarder); // down boarder
    // draw_rect(&global_img, x - boarder_size, y - boarder_size, x, h + boarder_size, boarder); // left boarder
    // draw_rect(&global_img, w, y - boarder_size, w + boarder_size, h + boarder_size, boarder); // right boarder
}