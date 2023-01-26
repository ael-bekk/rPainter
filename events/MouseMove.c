#include "../Editor.h"

int    MouseMove(int x, int y, void *param)
{
    (void)param;
    (void)x;
    (void)y;
    if (x < MAX_RIGHT_IMG)
        screen_info.new_middle_x = WIN_WIDTH - MAX_RIGHT_IMG;
    else if (x > WIN_WIDTH - MAX_RIGHT_IMG)
        screen_info.new_middle_x = MAX_RIGHT_IMG;
    else
        screen_info.new_middle_x = WIN_WIDTH - x;
    
    screen_info.bare_OnHover = (x > WIN_WIDTH - 10 && x < WIN_WIDTH && y  > screen_info.right_down_corner_y + screen_info.middle_y && y < screen_info.scroll_bare_size + screen_info.right_down_corner_y + screen_info.middle_y);
    
    int size = lst_img_size(img);

    if (screen_info.bare_OnClick) {

        if (y > screen_info.middle_y + screen_info.scroll_bare_size / 2 && y < WIN_HEIGHT - screen_info.scroll_bare_size / 2)
            screen_info.right_down_corner_y = y - screen_info.middle_y - screen_info.scroll_bare_size / 2;
        else if (y < screen_info.middle_y)
            screen_info.right_down_corner_y = 0;
        else if (y > WIN_HEIGHT)
            screen_info.right_down_corner_y = WIN_HEIGHT - screen_info.middle_y  - screen_info.scroll_bare_size - 30;
    }
    if (screen_info.canvas_OnClick)
        for (int i = 0; i < map.height; i++)
            for (int j = 0; j < map.width; j++)
                if (x >= MAX(map.x + j * map.cell_size, 0) && x <= MIN(map.x + (j + 1) * map.cell_size, WIN_WIDTH - screen_info.middle_x)
                    && y >= MAX(map.y + i * map.cell_size, 0) && y <= MIN(map.y + (i + 1) * map.cell_size, WIN_HEIGHT)) {
                    if (f)
                        bucket_tool(j, i, map.cells[i][j].color);
                    else if (b)
                        brush_tool(j - (mouse.size_of_the_brush - 1) / 2, i - (mouse.size_of_the_brush - 1) / 2, mouse_OnClick.color);
                    break;
                }
    if (rgb.r_OnClick)
        rgb.r = rgb_setter(x);
    if (rgb.g_OnClick)
        rgb.g = rgb_setter(x);
    if (rgb.b_OnClick)
        rgb.b = rgb_setter(x);
    if (rgb.shade_OnClick)
        rgb.shade = shade_setter(x);
    
    

    mouse.x = x;
    mouse.y = y;
    return (0);
}