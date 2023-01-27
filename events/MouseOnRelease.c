#include "../inc/Editor.h"

int    MouseOnRelease(int button, int x, int y, void *param)
{
    (void)param;
    (void)button;
    (void)x;
    (void)y;
    (button == 1) && (screen_info.middle_OnClick = FALSE);
    (button == 1) && (screen_info.bare_OnClick = FALSE);
    (button == 1) && (rgb.r_OnClick = FALSE);
    (button == 1) && (rgb.g_OnClick = FALSE);
    (button == 1) && (rgb.b_OnClick = FALSE);
    (button == 1) && (rgb.shade_OnClick = FALSE);
    (button == 1) && (mouse_OnClick.event = FALSE);
    (button == 1) && (screen_info.canvas_OnClick = FALSE);
    return (0);
}