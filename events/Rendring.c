#include "../inc/Editor.h"

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