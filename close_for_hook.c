#include <cub3d.h>

void free_close_all(void *all)
{
    t_cub3d *cub3d;
    int i;

    i = 0;
    while (i < 5)
    {
        if (cub3d->mlx->texture[i])
            mlx_destroy_image(cub3d->mlx->mlx_ptr, cub3d->mlx->texture[i]);
        i++;
    }
    mlx_delete_image(cub3d->mlx->mlx_ptr, cub3d->mlx->img_ptr);
    mlx_delete_texture(cub3d->mlx->texture[NORTH]);
    mlx_delete_texture(cub3d->mlx->texture[SOUTH]);
    mlx_delete_texture(cub3d->mlx->texture[WEST]);
    mlx_delete_texture(cub3d->mlx->texture[EAST]);
}

void close_esc(mlx_key_data_t key_data, void *arg)
{
    t_cub3d *cub3d;

    cub3d = (t_cub3d *)arg;
    if (key_data.keycode == KEY_ESC)
    {
        free_close_all(cub3d);
        mlx_close_window(cub3d->mlx->mlx_ptr);
    }
}