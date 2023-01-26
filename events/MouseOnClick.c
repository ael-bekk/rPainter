#include "../Editor.h"

int    MouseOnClick(int button, int x, int y, void *param)
{
    (void)param;
    (void)button;
    (void)x;
    (void)y;
    int size = lst_img_size(img);
    if (button == 1)
        IS_MID_BOARD(x, WIN_WIDTH - screen_info.middle_x, y) && (screen_info.middle_OnClick = TRUE);
    if (button == 4 && screen_info.right_down_corner_y < ((size / ((screen_info.middle_x - 10) / 110)) + !!(size % ((screen_info.middle_x - 10) / 110))) * 110 - (WIN_HEIGHT - screen_info.middle_y))
        screen_info.right_down_corner_y += 20;
    if (button == 5 && screen_info.right_down_corner_y > 0)
        screen_info.right_down_corner_y -= 20;
    
    screen_info.bare_OnClick = (x > WIN_WIDTH - 10 && x < WIN_WIDTH && y  > screen_info.right_down_corner_y + screen_info.middle_y && y < screen_info.scroll_bare_size + screen_info.right_down_corner_y + screen_info.middle_y);


    int _size = WIN_WIDTH - screen_info.middle_x / 2 - 100;
    if (button == 1 && x >_size && x < _size + 200)
    {
        if (y > screen_info.middle_y + 45 && y < screen_info.middle_y + 65)
            rgb.r = (float)(x - _size) * (255.0 / 200.0),
            rgb.r_OnClick = TRUE;

        if (y > screen_info.middle_y + 135 && y < screen_info.middle_y + 155)
            rgb.g = (float)(x - _size) * (255.0 / 200.0),
            rgb.g_OnClick = TRUE;

        if (y > screen_info.middle_y + 215 && y < screen_info.middle_y + 235)
            rgb.b = (float)(x - _size) * (255.0 / 200.0),
            rgb.b_OnClick = TRUE;
        if (y > screen_info.middle_y + 305 && y < screen_info.middle_y + 326)
            rgb.shade = (float)(x - _size) * (511.0 / 200.0),
            rgb.shade_OnClick = TRUE;
    }
    // click on the big color
    _size = WIN_WIDTH - screen_info.middle_x / 2 - 100;
    if (button == 1 && x > _size && y > screen_info.middle_y + 400 && x < _size + 100 && y < screen_info.middle_y + 510 && !is_color_exist(full_color()))
        color_list[initial_colors_size] = full_color(), mouse_OnClick.color = color_list[initial_colors_size++];
    // click on the color in the right side
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
        int condition = (x > start_x && x < start_x + w && y > start_y - scrl && y < start_y + h - scrl);
        if (condition && button == 2)
        {
            for (int j = i; j < initial_colors_size - 1; j++)
                color_list[j] = color_list[j + 1];
            initial_colors_size--;
        }
        else if (condition)
        {
            rgb.r = (color_list[i] >> 16) & 0xFF;
            rgb.g = (color_list[i] >> 8) & 0xFF;
            rgb.b = color_list[i] & 0xFF;
            rgb.shade = 256;
            mouse_OnClick.color = color_list[i];
        }
        start_x += w + 10;
    }
    mouse_OnClick.event = (button == 1);
    mouse_OnClick.x = x;
    mouse_OnClick.y = y;

    // click on the color in the right side
    int end_x = WIN_WIDTH - screen_info.middle_x - 10;

    if (x >= 0 && x <= end_x && y >= 0 && y <= WIN_HEIGHT)
    {
        if (button == 5 && map.cell_size < 300)
            map.x -= round((float)((float)(x - map.x) / (float)map.cell_size) * 5),
            map.y -= round((float)((float)(y - map.y) / (float)map.cell_size) * 5),
            map.cell_size += 5;
        if (button == 4 && map.cell_size > 20)
            map.x += round((float)((float)(x - map.x) / (float)map.cell_size) * 5),
            map.y += round((float)((float)(y - map.y) / (float)map.cell_size) * 5),
            map.cell_size -= 5;
    }
    if (button == 1 && x >= 0 && x <= end_x && y >= 0 && y <= WIN_HEIGHT && !screen_info.middle_OnClick) {
        int brk = 1;
        screen_info.canvas_OnClick = TRUE;
        for (int i = 0; i < map.height && brk; i++)
            for (int j = 0; j < map.width && brk; j++) {
                int x_x = (mouse.size_of_the_brush - 1) / 2;
                if (x >= map.x + (j - x_x) * map.cell_size && x <= map.x + (j + x_x) * map.cell_size && y >= map.y + (i - x_x) * map.cell_size && y <= map.y + (i + x_x) * map.cell_size) {
                    if (f)
                        bucket_tool(j, i, map.cells[i][j].color);
                    else if (b)
                        brush_tool(j - x_x, i - x_x, mouse_OnClick.color);
                    brk = 0;
                }
            }
    }
    return (0);
}