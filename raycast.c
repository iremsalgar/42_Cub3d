#include "cub3d.h"

void rycstng_loop(void *data)
{
    static int    ray_iter;
    static t_raycast cast;
    t_cub3d *cub;
    t_mlx *mlx;

    cub = ((t_cub3d *)data)->map;
    mlx = ((t_cub3d *)data)->mlx;
    put_floor(mlx->img_ptr, cub->map->floor_color);
    ray_iter = 0;
    while (ray_iter < SCREENWIDTH)
    {
        ray_cal(&cast, cub, ray_iter);
        init_dda(&cast, cub);
        dda(&cast, cub);
        draw_wall(&cast, cub, ray_iter);
        ray_iter++;
    }
    check_move(&(cub->mlx->vector), mlx->);
}