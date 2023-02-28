#ifndef __TOOLS_H__
#define __TOOLS_H__

// ------------------------ img_list.c ------------------------
t_img           *new_img(void *mlx, char *path_img, int width, int height);
void            push_back(t_imgs **head, t_img *img);
int             lst_img_size(t_imgs *tmp);
int             already_in_list(char *d);
void            clear_list();
void            color_to_img(t_img *img, unsigned int color, int width, int height);
void            draw_img(t_img *img, int x, int y, int w, int h, t_img *img_to_draw);

// ------------------------ BrushAndBucket.c ------------------------
void            draw_brush_rect(t_img *img, int x, int y, int width, int height);
void            draw_brush_border(t_img *img, int x, int y, int width, int height, int boarder, int boarder_size);
void            brush_border();
void            bucket_tool(int x, int y, int color, t_img *img);
void            brush_tool(int x, int y, int color);

#endif