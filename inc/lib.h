#ifndef __LIB_H__
#define __LIB_H__

#include "structs.h"

void            draw_rect(t_img *img, int x, int y, int width, int height, unsigned int color);
void            draw_rect_gradient(t_img *img, int x, int y, int width, int height, int color);
void            draw_border(t_img *img, int x, int y, int width, int height, int boarder, int boarder_size);
void            draw_rect_bordered(int x, int y, int w, int h, int color, int max_colored_x, int boarder, int boarder_size);
void            draw_rect_bordered_in(int x, int y, int w, int h, int color, int max_colored_x, int boarder, int boarder_size);
void            draw_rect_bordered_gradient(int x, int y, int w, int h, int color, int max_colored_x, int boarder, int boarder_size);

#endif