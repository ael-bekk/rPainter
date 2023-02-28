        #include "../inc/Editor.h"

int    MouseOnClick(int button, int x, int y, void *param)
{
    (void)param;
    
    mouse_OnClick.x = x;
    mouse_OnClick.y = y;
    switch(button) {

        case M_RIGHT_CLICK:
            mouse_OnClick.event = TRUE;
            IS_MID_BOARD(x, WIN_WIDTH - screen_info.middle_x, y) && (screen_info.middle_OnClick = TRUE);
            screen_info.bare_OnClick = (x > WIN_WIDTH - 10 && x < WIN_WIDTH && y  > screen_info.right_down_corner_y + screen_info.middle_y && y < screen_info.scroll_bare_size + screen_info.right_down_corner_y + screen_info.middle_y);
            if (!screen_info.swp)
            {
                mouse_OnClick.bol = 0;
                {
                    int _size = WIN_WIDTH - screen_info.middle_x / 2 - 100;
                    if (x >_size && x < _size + 200) {
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
                    if (x > _size && y > screen_info.middle_y + 400 && x < _size + 100 && y < screen_info.middle_y + 510) {
                        if (!is_color_exist(full_color()))
                            color_list[initial_colors_size++] = full_color();
                        mouse_OnClick.color = full_color();
                    }
                }

                {
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
                        if (x > start_x && x < start_x + w && y > start_y - scrl && y < start_y + h - scrl)
                        {
                            rgb.r = (color_list[i] >> 16) & 0xFF;
                            rgb.g = (color_list[i] >> 8) & 0xFF;
                            rgb.b = color_list[i] & 0xFF;
                            rgb.shade = 256;
                            mouse_OnClick.color = color_list[i];
                        }
                        start_x += w + 10;
                    }
                }
            }
            else
            {
                mouse_OnClick.bol = 1;
                t_imgs *tmp = img;
                int start_x = WIN_WIDTH - screen_info.middle_x + 10;
                int start_y = screen_info.middle_y + 10;
                if (tmp)
                    start_x += ((WIN_WIDTH - start_x) % (tmp->img->width + 10)) / 2;
                int scrl = screen_info.right_down_corner_y;
                while (tmp)
                {
                    if (start_x + tmp->img->width > WIN_WIDTH)
                    {
                        start_x = WIN_WIDTH - screen_info.middle_x + 10;
                        start_x += ((WIN_WIDTH - start_x) % (tmp->img->width + 10)) / 2;
                        if (scrl < tmp->img->height + 10) {
                            start_y += tmp->img->height + 10 - scrl;
                            scrl = 0;
                        } else
                            scrl -= tmp->img->height + 10;
                    }
                    if (OnHover(start_x, start_y, MIN(tmp->img->width + start_x, WIN_WIDTH), MIN(tmp->img->height + start_y - scrl, WIN_HEIGHT)))
                    {
                        mouse_OnClick.img = tmp->img;
                        break;
                    }
                    // for (int y = 0; y < tmp->img->height && start_y + y < WIN_HEIGHT; y++)
                    //     for (int x = 0; x < tmp->img->width && start_x + x < WIN_WIDTH; x++)
                    //         if (y >= scrl)
                    //             *get_pixel(&global_img, start_x + x, start_y + y - scrl) = *get_pixel(tmp->img, x, y);
                    start_x += tmp->img->width + 10;
                    tmp = tmp->next;
                }
            }
            {
                int start_x = WIN_WIDTH - screen_info.middle_x + 100;
                int start_y = 100;
                if (OnHover(start_x, start_y, start_x + screen_info.imgs.width, start_y + screen_info.imgs.height))
                    screen_info.swp = 1;
                start_x += 100 + screen_info.imgs.width;
                if (OnHover(start_x, start_y, start_x + screen_info.colors.width, start_y + screen_info.colors.height))
                    screen_info.swp = 0;
            }
            CanvasRightClick();
            break;

        case M_LEFT_CLICK:
            {
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
                    if (x > start_x && x < start_x + w && y > start_y - scrl && y < start_y + h - scrl)
                    {
                        for (int j = i; j < initial_colors_size - 1; j++)
                            color_list[j] = color_list[j + 1];
                        initial_colors_size--;
                    }
                    start_x += w + 10;
                }
            }
            break;

        case M_SCRL_UP:
            {
                int size = lst_img_size(img);
                if (screen_info.right_down_corner_y < ((size / ((screen_info.middle_x - 10) / 110)) + !!(size % ((screen_info.middle_x - 10) / 110))) * 110 - (WIN_HEIGHT - screen_info.middle_y))
                    screen_info.right_down_corner_y += 20;
            }
            CanvasScrollUp();
            break;

        case M_SCRL_DOWN:
            screen_info.right_down_corner_y -= 20 * (screen_info.right_down_corner_y > 0);
            CanvasScrollDown();
            break;

        case M_MID_CLICK:
        
            break;

        default:
            break;
    }
    return (0);
}