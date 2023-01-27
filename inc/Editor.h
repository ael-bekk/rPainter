#ifndef __EDITOR_H__
#define __EDITOR_H__

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <time.h>
# include <mlx.h>
# include <dirent.h>

# include "KeyMap.h"
# include "src.h"
# include "events.h"
# include "structs.h"
# include "tools.h"
# include "lib.h"

#pragma GCC optimize("O3")
#pragma GCC optimize("inline")
#pragma GCC optimize("omit-frame-pointer")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("Ofast")
#pragma GCC option("arch=native", "tune=native", "no-zero-upper")
#pragma GCC target("avx")
#pragma GCC target "bmi2"
#include <x86intrin.h>

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


extern t_screen_info screen_info;
extern t_rgb rgb;
extern t_map map;
extern t_keys keys;
extern void    *mlx;
extern void    *win;
extern t_imgs   *img;
extern t_img   global_img;
extern int     img_count;

extern t_mouse mouse;
extern t_mouse mouse_OnClick;

extern int     color_list[1028];
extern int     initial_colors_size;


unsigned int    *get_pixel(t_img *img, int x, int y);
void            path_img_to_img(t_img *img, char *path_img, int width, int height);

int             color_gradient(float width, float x, int color);
int             base_color();
int             full_color();

int             is_color_exist(int color);

int             rgb_setter(int x);
int             shade_setter(int x);


int	            search_in_dir();
void            display_map();




#endif // __EDITOR_H__