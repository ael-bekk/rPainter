#ifndef __EDITOR_H__
#define __EDITOR_H__

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <time.h>
# include "inc/libft/libft.h"
# include "inc/get_next_line/get_next_line.h"
# include <mlx.h>
# include <dirent.h>

# define TRUE 1
# define FALSE 0

# define MIN(a, b) (a < b ? a : b)
# define MAX(a, b) (a > b ? a : b)
# define ABS(a) (a < 0 ? -a : a)

# define PI 3.14159265359

# define RAD(a) (a * PI / 180)
# define DEG(a) (a * 180 / PI)


# define WIN_WIDTH 2200
# define WIN_HEIGHT 1300
# define WIN_NAME "Editor"
# define MAX_RIGHT_IMG 500


# define IS_MID_BOARD(x, X, y) (x > X - 15 && x < X + 15 && y > 300 && y < WIN_HEIGHT - 300)
# define CAN_MV_MID(V, X) (V && X > MAX_RIGHT_IMG && X < WIN_WIDTH - MAX_RIGHT_IMG)

typedef struct	s_img
{
    char    *path;
    void    *img;
    char    *data;
    int     bpp;
    int     size_line;
    int     endian;
    int     width;
    int     height;
}				t_img;

typedef struct	s_imgs
{
    int     still_in_dir;
    t_img   *img;
    struct s_imgs   *next;
}				t_imgs;

typedef struct	s_env
{
    void    *mlx;
    void    *win;
    t_img   *img;
}				t_env;

struct s_screen_info
{
    int     middle_OnClick;
    int     right_down_corner_OnScroll;
    int     right_down_corner_y;
    int     new_right_down_corner_y;
    int     middle_x;
    int     new_middle_x;
    int     middle_y;
    int     scroll_x;
    int     scroll_y;
    int     scroll_bare_size;
    int     bare_OnClick;
    int     bare_OnHover;
    
    int     big_color_OnClick;
    int     big_color_OnHover;
    int     small_color_OnClick;
    int     small_color_OnHover;
    int     canvas_OnClick;
}   screen_info;

typedef struct s_mouse
{
    int     size_of_the_brush;
    int     event;
    int     x;
    int     y;
    int     color;
    t_img   *img;
}   t_mouse;

struct s_rgb
{
    int     r;
    int     r_OnClick;
    int     g;
    int     g_OnClick;
    int     b;
    int     b_OnClick;
    int     shade;
    int     shade_OnClick;
}  rgb;

typedef struct s_cell
{
    int     is_color;
    int     is_img;
    int     color;
    t_img   *img;
}   t_cell;

struct s_map
{
    int x;
    int y;
    int     cell_size;
    int     width;
    int     height;
    t_cell     **cells;
}   map;

void    *mlx;
void    *win;
t_imgs   *img;
t_img   global_img;
int     img_count;

t_mouse mouse;
t_mouse mouse_OnClick;

static int     color_list[1028] = {0xff4000, 0xff8000, 0xffbf00, 0xffff00, 0xbfff00, 0x80ff00,
                            0x40ff00, 0x00ff00, 0x00ff40, 0x00ff80, 0x00ffbf, 0x00ffff,
                            0x00bfff, 0x0080ff, 0x0066ff, 0x0040ff, 0x0000ff, 0x4000ff,
                            0x8000ff, 0xbf00ff, 0xff00ff, 0xff00bf, 0xff0080, 0xff0040,
                            0xff0000};
int     initial_colors_size;

unsigned int    *get_pixel(t_img *img, int x, int y);
void            path_img_to_img(t_img *img, char *path_img, int width, int height);
void            color_to_img(t_img *img, unsigned int color, int width, int height);


void            draw_rect(t_img *img, int x, int y, int width, int height, unsigned int color);
void            draw_rect_gradient(t_img *img, int x, int y, int width, int height, int color);
void            draw_border(t_img *img, int x, int y, int width, int height, int boarder, int boarder_size);
void            draw_rect_bordered(int x, int y, int w, int h, int color, int max_colored_x, int boarder, int boarder_size);
void            draw_rect_bordered_in(int x, int y, int w, int h, int color, int max_colored_x, int boarder, int boarder_size);
void            draw_rect_bordered_gradient(int x, int y, int w, int h, int color, int max_colored_x, int boarder, int boarder_size);



t_img           *new_img(void *mlx, char *path_img, int width, int height);
void            push_back(t_imgs **head, t_img *img);
int             lst_img_size(t_imgs *tmp);
int             already_in_list(char *d);
void            clear_list();

int             color_gradient(float width, float x, int color);
int             base_color();
int             full_color();

int             OnHover(int x, int y, int w, int h);
int             OnClick(int x, int y, int w, int h);

void            draw_img(t_img *img, int x, int y, int w, int h, t_img *img_to_draw);

int             is_color_exist(int color);

int             CloseWin(void *param);
int             KeyPress(int key, void *param);
int             KeyOnRelease(int key, void *param);
int             MouseOnClick(int button, int x, int y, void *param);
int             MouseOnRelease(int button, int x, int y, void *param);
int             MouseMove(int x, int y, void *param);

int             rgb_setter(int x);
int             shade_setter(int x);


int	            search_in_dir();
int             rendering(void *param);
void            display_map();


void            draw_brush_rect(t_img *img, int x, int y, int width, int height);
void            draw_brush_border(t_img *img, int x, int y, int width, int height, int boarder, int boarder_size);
void            brush_border();
void            bucket_tool(int x, int y, int color);
void            brush_tool(int x, int y, int color);

int g;
int f;
int b;

#endif // __EDITOR_H__