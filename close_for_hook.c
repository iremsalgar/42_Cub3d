#include <cub3d.h>

void free_close_al(t_cub3d *cub3d)
{
    int i;
    
    i = -1;
    while (++i < 5)
        free(cub3d->map->texture[i]);
    //freele
}

void close_esc(int  key_data, void *arg)
{
    t_cub3d *cub3d;

    cub3d = (t_cub3d *)arg;
    if (key_data == KEY_ESC)
    {
        free_close_all(cub3d);
        mlx_close_window(cub3d->mlx->mlx_ptr);
    }
}
