#include "../inc/Editor.h"

void    CanvasRightClick() {

    int x = mouse_OnClick.x;
    int y = mouse_OnClick.y;

    // click on the color in the left side
    int bound_x = WIN_WIDTH - screen_info.middle_x - 10;
    if (x >= 0 && x <= bound_x && y >= 0 && y <= WIN_HEIGHT && !screen_info.middle_OnClick)
    {
        if (!keys.cntrl) {
            int brk = 1;
            screen_info.canvas_OnClick = TRUE;
            for (int i = 0; i < map.height && brk; i++)
                for (int j = 0; j < map.width && brk; j++) {
                    int x_x = (mouse.size_of_the_brush - 1) / 2;
                    if (x >= map.x + j * map.cell_size && x <= map.x + (j + 1) * map.cell_size && y >= map.y + i * map.cell_size && y <= map.y + (i + 1) * map.cell_size) {
                        if (keys.f)
                            bucket_tool(j, i, map.cells[i][j].color);
                        else if (keys.b)
                            brush_tool(j - x_x, i - x_x, mouse_OnClick.color);
                        brk = 0;
                    }
                }
            }
    }
}

void    CanvasLeftClick() {

}

void    CanvasScrollUp() {

    int x = mouse_OnClick.x;
    int y = mouse_OnClick.y;

    // click on the color in the left side
    int bound_x = WIN_WIDTH - screen_info.middle_x - 10;
    if (x >= 0 && x <= bound_x && y >= 0 && y <= WIN_HEIGHT && !screen_info.middle_OnClick)
    {
        if (!keys.cntrl) {
            if (map.cell_size > 6)
                map.x += round((float)((float)(x - map.x) / (float)map.cell_size) * 5),
                map.y += round((float)((float)(y - map.y) / (float)map.cell_size) * 5),
                map.cell_size -= 5;
        }
        else
            mouse.size_of_the_brush += (mouse.size_of_the_brush < 20);
    }
}

void    CanvasScrollDown() {

    int x = mouse_OnClick.x;
    int y = mouse_OnClick.y;

    // click on the color in the right side
    int end_x = WIN_WIDTH - screen_info.middle_x - 10;

    if (x >= 0 && x <= end_x && y >= 0 && y <= WIN_HEIGHT && !screen_info.middle_OnClick)
    {
        if (!keys.cntrl) {
            if (map.cell_size < 300)
                map.x -= round((float)((float)(x - map.x) / (float)map.cell_size) * 5),
                map.y -= round((float)((float)(y - map.y) / (float)map.cell_size) * 5),
                map.cell_size += 5;
        }
        else
            mouse.size_of_the_brush -= (mouse.size_of_the_brush > 1);
    }
}

void    CanvasMidClick() {

}
