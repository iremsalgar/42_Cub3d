#include "cub3d.h"

int key_event(int key_data, void *arg)
{
    t_cub3d *cub3d;

    cub3d = (t_cub3d *)arg;
    t_vector *vector;
    t_mlx *mlx;

    if(key_data == KEY_A)
        move_left_right(vector, cub3d->map->map_content, cub3d->mlx, 2);
    if(key_data == KEY_D)
        move_left_right(vector, cub3d->map->map_content, cub3d->mlx, 1);
    if(key_data == KEY_W)
        move_forward_back(vector, cub3d->map->map_content, cub3d->mlx, 3);
    if(key_data == KEY_S)
        move_forward_back(vector, cub3d->map->map_content, cub3d->mlx, 4);
    if(key_data == KEY_LEFT || key_data == KEY_RIGHT)
        check_rotate(vector, mlx);
    return(0);
}

int close_esc(int  key_data, void *arg)
{
    t_cub3d *cub3d;

    cub3d = (t_cub3d *)arg;
    if (key_data == KEY_ESC)
    {
        //free and close window
        return(0);
    }
    return (0);
}

int	rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}