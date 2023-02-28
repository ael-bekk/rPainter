#ifndef __STRUCTS_H__
#define __STRUCTS_H__

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

typedef struct s_screen_info
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
    t_img   imgs;
    t_img   colors;
    int     swp;
}   t_screen_info;

typedef struct s_mouse
{
    int     bol;
    int     size_of_the_brush;
    int     event;
    int     x;
    int     y;
    int     color;
    t_img   *img;
}   t_mouse;

typedef struct s_rgb
{
    int     r;
    int     r_OnClick;
    int     g;
    int     g_OnClick;
    int     b;
    int     b_OnClick;
    int     shade;
    int     shade_OnClick;
}  t_rgb;

typedef struct s_cell
{
    int     is_color;
    int     is_img;
    int     color;
    t_img   *img;
}   t_cell;

typedef struct s_map
{
    int x;
    int y;
    int     cell_size;
    int     width;
    int     height;
    t_cell     **cells;
}   t_map;

typedef struct s_keys
{
    int g;
    int f;
    int b;
    int cntrl;
} t_keys;

#endif