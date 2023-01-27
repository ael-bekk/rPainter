#include "../inc/Editor.h"

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

// fill img with color
void    color_to_img(t_img *img, unsigned int color, int width, int height)
{
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
            *get_pixel(img, x, y) = color;
}

// draw img to img
void    draw_img(t_img *img, int x, int y, int w, int h, t_img *img_to_draw) {

    for (int _y = y; _y < y + h; _y++)
        for (int _x = x; _x < x + w; _x++)
            if (_x >= 0 && _x < WIN_WIDTH && _y >= 0 && _y < WIN_HEIGHT)
                *get_pixel(img, _x, _y) = *get_pixel(img_to_draw, (_x - x) * img_to_draw->width / w, (_y - y) * img_to_draw->height / h);
}