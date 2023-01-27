#include "inc/Editor.h"

int             color_list[1028] = {0xff4000, 0xff8000, 0xffbf00, 0xffff00, 0xbfff00, 0x80ff00,
                                0x40ff00, 0x00ff00, 0x00ff40, 0x00ff80, 0x00ffbf, 0x00ffff,
                                0x00bfff, 0x0080ff, 0x0066ff, 0x0040ff, 0x0000ff, 0x4000ff,
                                0x8000ff, 0xbf00ff, 0xff00ff, 0xff00bf, 0xff0080, 0xff0040,
                                0xff0000};
int             initial_colors_size = 25;

t_screen_info   screen_info;
t_rgb           rgb;
t_map           map;
t_keys          keys;
void            *mlx;
void            *win;
t_imgs          *img;
t_img           global_img;
int             img_count;
t_mouse         mouse;
t_mouse         mouse_OnClick;







void    display_map()
{
    // clear global_img
        draw_rect(&global_img, 0, 0, WIN_WIDTH - screen_info.middle_x, WIN_HEIGHT, 0x99aabb);

    // draw map
        for (int y = 0; y < map.height; y++)
            for (int x = 0; x < map.width; x++)
                if (map.cells[y][x].is_color)
                    draw_rect_bordered_in(x * map.cell_size + map.x - !!x * !keys.g, y * map.cell_size + map.y - !!y * !keys.g, (x + 1) * map.cell_size + map.x, (y + 1) * map.cell_size + map.y, map.cells[y][x].color, (x + 1) * map.cell_size + map.x, 0xcccccc, !keys.g);
                else if (map.cells[y][x].is_img)
                    draw_img(&global_img, x * map.cell_size + map.x - !!x * !keys.g, y * map.cell_size + map.y - !!y * !keys.g, map.cell_size, map.cell_size, map.cells[y][x].img);

    // draw brush border
        if (keys.b)
            brush_border();

    // clear up right corner
        draw_rect(&global_img, WIN_WIDTH - screen_info.middle_x, 0, WIN_WIDTH, screen_info.middle_y, 0xE9F4FF);

    // clear down right corner
        int color = 0;
        for (int y = screen_info.middle_y; y < WIN_HEIGHT; y++)
            for (int x = WIN_WIDTH - screen_info.middle_x; x < WIN_WIDTH; x++)
                *get_pixel(&global_img, x, y) = (rand() % 100) ? (color += (color < 1275000)) / 5000 : 0xffffff / (rand() % 10 + 1);


    // draw middle line (x)
        draw_rect(&global_img, WIN_WIDTH - screen_info.middle_x, 0, WIN_WIDTH - screen_info.middle_x + 1, WIN_HEIGHT, 0x000000);

    // draw middle line (x) (onclick)
        draw_rect(&global_img, WIN_WIDTH - screen_info.middle_x - (1 + screen_info.middle_OnClick * 2), 300, WIN_WIDTH - screen_info.middle_x + (1 + screen_info.middle_OnClick * 2), WIN_HEIGHT - 300, 0x54006F);

    // draw middle line (y)
        draw_rect(&global_img, WIN_WIDTH - screen_info.middle_x, screen_info.middle_y, WIN_WIDTH, screen_info.middle_y + 1, 0xaa0000);

    // display imgs in the right side
    // {
    //     t_imgs *tmp = img;
    //     int start_x = WIN_WIDTH - screen_info.middle_x + 10;
    //     int start_y = screen_info.middle_y + 10;
    //     if (tmp)
    //         start_x += ((WIN_WIDTH - start_x) % (tmp->img->width + 10)) / 2;
    //     int scrl = screen_info.right_down_corner_y;
    //     while (tmp)
    //     {
    //         if (start_x + tmp->img->width > WIN_WIDTH)
    //         {
    //             start_x = WIN_WIDTH - screen_info.middle_x + 10;
    //             start_x += ((WIN_WIDTH - start_x) % (tmp->img->width + 10)) / 2;
    //             if (scrl < tmp->img->height + 10) {
    //                 start_y += tmp->img->height + 10 - scrl;
    //                 scrl = 0;
    //             } else
    //                 scrl -= tmp->img->height + 10;
    //         }
    //         for (int y = 0; y < tmp->img->height && start_y + y < WIN_HEIGHT; y++)
    //             for (int x = 0; x < tmp->img->width && start_x + x < WIN_WIDTH; x++)
    //                 if (y >= scrl)
    //                     *get_pixel(&global_img, start_x + x, start_y + y - scrl) = *get_pixel(tmp->img, x, y);
    //         start_x += tmp->img->width + 10;
    //         tmp = tmp->next;
    //     }
    //     // draw the scroll bar
    //         draw_rect(&global_img, WIN_WIDTH - 5 - screen_info.bare_OnHover * 5, screen_info.right_down_corner_y + screen_info.middle_y, WIN_WIDTH, screen_info.scroll_bare_size + screen_info.right_down_corner_y + screen_info.middle_y, 0xff0000 + screen_info.bare_OnHover * 0x0000ff);
    // }

    // display a colors customized
    {
        int start_x = WIN_WIDTH - screen_info.middle_x + 10;
        int start_y = screen_info.middle_y + 50;
        int _size = WIN_WIDTH - screen_info.middle_x / 2 - 100;

        draw_rect_bordered(_size, start_y, _size + 200, start_y + 10, 255 << 16, _size + (float)rgb.r * (200.0 / 255.0), 0xffffff, 1); // red bar
        draw_rect_bordered(_size + (float)rgb.r * (200.0 / 255.0) - 5, start_y - 5, _size + (float)rgb.r * (200.0 / 255.0) + 5, start_y + 15, 0xffffff, _size + (float)rgb.r * (200.0 / 255.0) + 5, 255 << 16, 1); // red controller

        draw_rect_bordered(_size, start_y + 90, _size + 200, start_y + 100, 255 << 8, _size + (float)rgb.g * (200.0 / 255.0), 0xffffff, 1); // green bar
        draw_rect_bordered(_size + (float)rgb.g * (200.0 / 255.0) - 5, start_y + 85, _size + (float)rgb.g * (200.0 / 255.0) + 5, start_y + 105, 0xffffff, _size + (float)rgb.g * (200.0 / 255.0) + 5, 255 << 8, 1); // green controller

        draw_rect_bordered(_size, start_y + 170, _size + 200, start_y + 180, 255, _size + (float)rgb.b * (200.0 / 255.0), 0xffffff, 1); // blue bar
        draw_rect_bordered(_size + (float)rgb.b * (200.0 / 255.0) - 5, start_y + 165, _size + (float)rgb.b * (200.0 / 255.0) + 5, start_y + 185, 0xffffff, _size + (float)rgb.b * (200.0 / 255.0) + 5, 255, 1); // blue controller

        draw_rect_bordered_gradient(_size, start_y + 260, _size + 200, start_y + 270, base_color(), _size + 200, 0xffffff, 1); // shade bar
        draw_rect_bordered(_size + (float)rgb.shade * (200.0 / 511.0) - 5, start_y + 255, _size + (float)rgb.shade * (200.0 / 511.0) + 5, start_y + 275, 0xffffff, _size + (float)rgb.shade * (200.0 / 511.0) + 5, 0x000000, 1); // shade controller
        
        int Hover = OnHover(_size, start_y + 350, _size + 200, start_y + 460);
        int Click = OnClick(_size, start_y + 350, _size + 100, start_y + 460);
        draw_rect_bordered(_size, start_y + 350, _size + 100, start_y + 460, full_color(), _size + 100, 0xffffff * !Click, 2 + Hover); // shade bar
        draw_rect_bordered(_size + 100, start_y + 350, _size + 200, start_y + 460, mouse_OnClick.color, _size + 200, 0xffffff, 2 + Hover); // shade bar
    }

    // display colors in the right side
    {
        int start_x = WIN_WIDTH - screen_info.middle_x + 10;
        int start_y = screen_info.middle_y + 680;
        int scrl = 0;
        int w = 20, h = 20;
        for (int i = 0; i < initial_colors_size; i++)
        {
            if (start_x + w > WIN_WIDTH)
            {
                start_x = WIN_WIDTH - screen_info.middle_x + 10;
                if (scrl < h + 10) {
                    start_y += h + 10 - scrl;
                    scrl = 0;
                } else
                    scrl -= h + 10;
            }
            int Click = OnClick(start_x, start_y - scrl, MIN(start_x + w, WIN_WIDTH), MIN(start_y + h, WIN_HEIGHT)) * 2;
            int Hover = OnHover(start_x, start_y - scrl, MIN(start_x + w, WIN_WIDTH), MIN(start_y + h, WIN_HEIGHT)) * 3;
            draw_rect_bordered(start_x - Hover, start_y - scrl - Hover, MIN(start_x + w + Hover, WIN_WIDTH), MIN(start_y + h + Hover, WIN_HEIGHT), color_list[i], MIN(start_x + w + Hover, WIN_WIDTH), 0x999999, 1 + Click);
            start_x += w + 10;
        }
    }

    // display finale img
        mlx_clear_window(mlx, win);
        mlx_put_image_to_window(mlx, win, global_img.img, 0, 0);
}

int     CloseWin(void *param)
{
    (void)param;
    exit(0);
}

int is_color_exist(int color)
{
    for (int i = 0; i < initial_colors_size; i++)
        if (color_list[i] == color)
            return (1);
    return (0);
}



int	search_in_dir()
{
	DIR				*dir;
	struct dirent	*p;
    char            d[1024] = "img/";

	dir = opendir("img");
	if (!dir) return (0);

	while ((p = readdir(dir)))
        if (strstr(p->d_name, ".png") || strstr(p->d_name, ".xpm"))
        {
            strcat(d, p->d_name);
            if (!already_in_list(d))
                push_back(&img, new_img(mlx, strdup(d), 100, 100));
            d[4] = '\0';
        }
	closedir(dir);
    clear_list();
	return (0);
}

int	main()
{
    char	*line;

    // initialize mlx
        mlx = mlx_init();
    // initialize win
        win = mlx_new_window(mlx, WIN_WIDTH, WIN_HEIGHT, "Editor");

    // initialize global_img
    {
        global_img.width = WIN_WIDTH;
        global_img.height = WIN_HEIGHT;
        global_img.img = mlx_new_image(mlx, global_img.width, global_img.height);
        global_img.data = mlx_get_data_addr(global_img.img, &global_img.bpp, &global_img.size_line, &global_img.endian);
    }
    // random
        srand(time(0));
    
    // initialize screen_info
    {
        screen_info.middle_x = screen_info.new_middle_x = WIN_WIDTH / 4;
        screen_info.middle_OnClick = FALSE;
        screen_info.right_down_corner_OnScroll = FALSE;
        screen_info.right_down_corner_y = screen_info.new_right_down_corner_y = 0;
        screen_info.middle_y = 190;
        screen_info.scroll_x = 0;
        screen_info.scroll_y = 0;
        int size = lst_img_size(img);
        screen_info.scroll_bare_size = (WIN_HEIGHT - screen_info.middle_y) - ((size / ((screen_info.middle_x - 10) / 110)) + !!(size % ((screen_info.middle_x - 10) / 110))) * 110 + (WIN_HEIGHT - screen_info.middle_y) - 40;
        if (screen_info.scroll_bare_size > WIN_HEIGHT - screen_info.middle_y - screen_info.right_down_corner_y)
            screen_info.scroll_bare_size = WIN_HEIGHT - screen_info.middle_y - screen_info.right_down_corner_y - 10;
        screen_info.bare_OnClick = FALSE;
        screen_info.bare_OnHover = FALSE;
        screen_info.big_color_OnClick = FALSE;
        screen_info.big_color_OnHover = FALSE;
        screen_info.small_color_OnClick = FALSE;
        screen_info.small_color_OnHover = FALSE;
        screen_info.canvas_OnClick = FALSE;
    }

    // initialize rgb 
        rgb.r_OnClick = rgb.g_OnClick = rgb.b_OnClick = rgb.shade_OnClick = FALSE;
        rgb.r =  rgb.g = rgb.b = 100;
        rgb.shade = 255;

    // initialize mouse
        mouse.size_of_the_brush = 2;
        mouse.x = mouse.y = 0;
        mouse.img = NULL;
        mouse.color = 0;

    // initialize mouse_OnClick
        mouse_OnClick.event = FALSE;
        mouse_OnClick.x = mouse_OnClick.y = 0;
        mouse_OnClick.img = NULL;
        mouse_OnClick.color = 0;

    // inisialize map
    {
        map.x = +20;
        map.y = +20;
        map.width = 50;
        map.height = 20;
        map.cells = (t_cell**)malloc(sizeof(t_cell*) * map.height);
        for (int i = 0; i < map.height; i++)
        {
            map.cells[i] = (t_cell*)malloc(sizeof(t_cell) * map.width);
            for (int j = 0; j < map.width; j++)
            {
                map.cells[i][j].is_color = 1;
                map.cells[i][j].is_img = FALSE;
                map.cells[i][j].color = 0xffffff;
                map.cells[i][j].img = NULL;
            }
        }
        map.cell_size = 100;
    }
    keys.b = TRUE;
	display_map();  // display window
    

    mlx_hook(win, 2, 1L<<0, KeyPress, NULL);
    mlx_hook(win, 3, 1L<<1, KeyOnRelease, NULL);

    mlx_hook(win, 6, 1L<<6, MouseMove, NULL);
    mlx_hook(win, 4, 1L<<2, MouseOnClick, NULL);
    mlx_hook(win, 5, 1L<<3, MouseOnRelease, NULL);

    mlx_loop_hook(mlx, rendering, NULL);
    
    mlx_hook(win, 17, 1, CloseWin, NULL); 
    
    mlx_loop(mlx);
    return (0);
}