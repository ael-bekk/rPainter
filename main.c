#include "Editor.h"



// resize img (original to img)
void    path_img_to_img(t_img *img, char *path_img, int width, int height)
{
    t_img   _img;

    _img.img = mlx_xpm_file_to_image(mlx, path_img, &_img.width, &_img.height);
    _img.data = mlx_get_data_addr(_img.img, &_img.bpp, &_img.size_line, &_img.endian);

    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
            *get_pixel(img, x, y) = *get_pixel(&_img,
                                            (float)x / (float)width * (float)_img.width,
                                            (float)y / (float)height * (float)_img.height);
    mlx_destroy_image(mlx, _img.img);
}

// fill img with color
void    color_to_img(t_img *img, unsigned int color, int width, int height)
{
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
            *get_pixel(img, x, y) = color;
}

// create new img
t_img   *new_img(void *mlx, char *path_img, int width, int height)
{
    t_img   *img;

    img = (t_img *)malloc(sizeof(t_img));
    img->path = path_img;
    img->img = mlx_new_image(mlx, width, height);
    img->data = mlx_get_data_addr(img->img, &img->bpp, &img->size_line, &img->endian);
    path_img_to_img(img, path_img, width, height);
    img->width = width;
    img->height = height;
    return (img);
}

// push img to list of imgs
void    push_back(t_imgs **head, t_img *img)
{
    t_imgs  *new;
    t_imgs  *tmp;

    new = (t_imgs *)malloc(sizeof(t_imgs));
    new->img = img;
    new->still_in_dir = 1;
    new->next = NULL;
    if (*head == NULL)
    {
        *head = new;
        return ;
    }
    tmp = *head;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}

// size of list of imgs
int     lst_img_size(t_imgs *tmp)
{
    int     i;

    i = 0;
    while (tmp) i++, tmp = tmp->next;
    return (i);
}

// draw img
void    draw_img(t_img *img, int x, int y, int w, int h, t_img *img_to_draw) {

    for (int _y = y; _y < y + h; _y++)
        for (int _x = x; _x < x + w; _x++)
            if (_x >= 0 && _x < WIN_WIDTH && _y >= 0 && _y < WIN_HEIGHT)
                *get_pixel(img, _x, _y) = *get_pixel(img_to_draw, (_x - x) * img_to_draw->width / w, (_y - y) * img_to_draw->height / h);
}

void    draw_brush_rect(t_img *img, int x, int y, int width, int height) {


    for (int _y = MAX(y, 0); _y < MIN(height, WIN_HEIGHT); _y++)
        for (int _x = MAX(x, 0); _x < MIN(width, WIN_WIDTH); _x++)
            if ((_x - map.x - map.cell_size) / map.cell_size >= 0 && (_x - map.x) / map.cell_size < map.width && (_y - map.y - map.cell_size) / map.cell_size >= 0 && (_y - map.y) / map.cell_size < map.height)
            {
                int c = map.cells[(_y - map.y) / map.cell_size][(_x - map.x) / map.cell_size].color;
                *get_pixel(img, _x, _y) = 0xffffff * (((c >> 16) & 0xff) < 128 && ((c >> 8) & 0xff) < 128 && (c & 0xff) < 128);
            }
            else
                *get_pixel(img, _x, _y) = 0xffffff;
}

void    draw_brush_border(t_img *img, int x, int y, int width, int height, int boarder, int boarder_size) {

    draw_brush_rect(img, x, y - boarder_size, width, y); // up boarder
    draw_brush_rect(img, x, height, width, height + boarder_size); // down boarder
    draw_brush_rect(img, x - boarder_size, y - boarder_size, x, height + boarder_size); // left boarder
    draw_brush_rect(img, width, y - boarder_size, width + boarder_size, height + boarder_size); // right boarder
}


void    brush_border() {

    int x = (mouse.x - map.x) / map.cell_size - (mouse.size_of_the_brush - 1) / 2;
    int y = (mouse.y - map.y) / map.cell_size - (mouse.size_of_the_brush - 1) / 2;
    int w = MIN(WIN_WIDTH - screen_info.middle_x, (mouse.x - map.x) / map.cell_size + (mouse.size_of_the_brush - 1) / 2 + 1);
    int h = MIN(WIN_HEIGHT, (mouse.y - map.y) / map.cell_size + (mouse.size_of_the_brush - 1) / 2 + 1);

    draw_brush_border(&global_img, x * map.cell_size + map.x, y * map.cell_size + map.y, w * map.cell_size + map.x, h * map.cell_size + map.y, 0x000000 + 0xfffff, 1);

}

void    display_map()
{
    // clear global_img
        draw_rect(&global_img, 0, 0, WIN_WIDTH - screen_info.middle_x, WIN_HEIGHT, 0x99aabb);

    // draw map
        for (int y = 0; y < map.height; y++)
            for (int x = 0; x < map.width; x++)
                if (map.cells[y][x].is_color)
                    draw_rect_bordered_in(x * map.cell_size + map.x - !!x * !g, y * map.cell_size + map.y - !!y * !g, (x + 1) * map.cell_size + map.x, (y + 1) * map.cell_size + map.y, map.cells[y][x].color, (x + 1) * map.cell_size + map.x, 0xcccccc, !g);
                else if (map.cells[y][x].is_img)
                    draw_img(&global_img, x * map.cell_size + map.x - !!x * !g, y * map.cell_size + map.y - !!y * !g, map.cell_size, map.cell_size, map.cells[y][x].img);

    // draw brush border
        if (b)
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

void    bucket_tool(int x, int y, int color)
{
    if (x < 0 || x >= map.width || y < 0 || y >= map.height || map.cells[y][x].color != color || map.cells[y][x].color == mouse_OnClick.color)
        return ;

    map.cells[y][x].color = mouse_OnClick.color,
    map.cells[y][x].is_color = TRUE,
    map.cells[y][x].is_img = FALSE;
    bucket_tool(x + 1, y, color);
    bucket_tool(x - 1, y, color);
    bucket_tool(x, y + 1, color);
    bucket_tool(x, y - 1, color);
}

void    brush_tool(int x, int y, int color)
{
    for (int i = y; i < mouse.size_of_the_brush + y; i++)
        for (int j = x; j < mouse.size_of_the_brush + x; j++)
            if (i >= 0 && i < map.height && j >= 0 && j < map.width)
                map.cells[i][j].color = mouse_OnClick.color,
                map.cells[i][j].is_color = TRUE,
                map.cells[i][j].is_img = FALSE;
}

int already_in_list(char *d)
{
    t_imgs *tmp = img;
    while (tmp)
    {
        if (!strcmp(tmp->img->path, d))
            return (tmp->still_in_dir = 1);
        tmp = tmp->next;
    }
    return (0);
}

void clear_list()
{
    t_imgs *tmp = img;

    while (tmp && tmp->next)
    {
        if (!tmp->next->still_in_dir) {
            t_imgs *tmp2 = tmp->next;
            tmp->next = tmp->next->next;
            mlx_destroy_image(mlx, tmp2->img->img);
            free(tmp2->img->path);
            free(tmp2->img);
            free(tmp2);
        }
        else
            tmp->still_in_dir *= (tmp == img),
            tmp = tmp->next;
    }
    if (img && !img->still_in_dir) {
        t_imgs *tmp2 = tmp;
        img = img->next;
        mlx_destroy_image(mlx, tmp2->img->img);
        free(tmp2->img->path);
        free(tmp2->img);
        free(tmp2);
    }
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
                push_back(&img, new_img(mlx, strdup(d), 200, 200));
            d[4] = '\0';
        }
	closedir(dir);
    clear_list();
	return (0);
}

int rendering(void *param)
{
    (void)param;


    if (!(img_count++ % 10)) {
        
        if (CAN_MV_MID(screen_info.middle_OnClick, (screen_info.middle_x + screen_info.new_middle_x) / 2)) {
        
            int size = lst_img_size(img);
            screen_info.scroll_bare_size = (WIN_HEIGHT - screen_info.middle_y) - ((size / ((screen_info.middle_x - 10) / 110)) + !!(size % ((screen_info.middle_x - 10) / 110))) * 110 + (WIN_HEIGHT - screen_info.middle_y) - 40;
            if (screen_info.scroll_bare_size > WIN_HEIGHT - screen_info.middle_y - screen_info.right_down_corner_y)
                screen_info.scroll_bare_size = WIN_HEIGHT - screen_info.middle_y - screen_info.right_down_corner_y - 10;
            screen_info.right_down_corner_y -= 20 * (screen_info.right_down_corner_y >= 20);
            (screen_info.middle_x = (screen_info.middle_x + screen_info.new_middle_x) / 2);
        }
        display_map();
    }

    if (img_count > 1000)
    {
        // read imgs
                search_in_dir();
        // resize bare
        {
            int size = lst_img_size(img);
            screen_info.scroll_bare_size = (WIN_HEIGHT - screen_info.middle_y) - ((size / ((screen_info.middle_x - 10) / 110)) + !!(size % ((screen_info.middle_x - 10) / 110))) * 110 + (WIN_HEIGHT - screen_info.middle_y) - 40;
            if (screen_info.scroll_bare_size > WIN_HEIGHT - screen_info.middle_y - screen_info.right_down_corner_y)
                screen_info.scroll_bare_size = WIN_HEIGHT - screen_info.middle_y - screen_info.right_down_corner_y - 10;
        }
        img_count = 0;
    }
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
        mouse.size_of_the_brush = 3;
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

    b = TRUE;
    initial_colors_size = 25;
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