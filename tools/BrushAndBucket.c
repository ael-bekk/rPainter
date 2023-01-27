#include "../inc/Editor.h"

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
    int w = MIN(WIN_WIDTH - screen_info.middle_x, (mouse.x - map.x) / map.cell_size + mouse.size_of_the_brush / 2 + 1);
    int h = MIN(WIN_HEIGHT, (mouse.y - map.y) / map.cell_size + mouse.size_of_the_brush / 2 + 1);

    draw_brush_border(&global_img, x * map.cell_size + map.x, y * map.cell_size + map.y, w * map.cell_size + map.x, h * map.cell_size + map.y, 0x000000 + 0xfffff, 1);

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