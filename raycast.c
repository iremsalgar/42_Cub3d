#include "cub3d.h"

void	put_square(t_square *square)
{
	int	iter[2];

	iter[y] = 0;
	while (iter[y] < square->len[y]
		&& iter[y] + square->start_pixel[y] < (int)square->img->height)
	{
		iter[x] = 0;
		while (iter[x] < square->len[x]
			&& iter[x] + square->start_pixel[x] < (int)square->img->width)
		{
			mlx_put_pixel(square->img, square->start_pixel[x] + iter[x],
				square->start_pixel[y] + iter[y], square->color);
			iter[x]++;
		}
		iter[y]++;
	}
}

static inline void put_floor(void *img_ptr, t_map *map)
{
    t_square	square;

	square.img = img_ptr;
	square.len[x] = SCREENWIDTH;
	square.len[y] = SCREENHEIGHT / 2;
	square.start_pixel[x] = 0;
	square.start_pixel[y] = 0;
	square.color = map->floor_color;
	put_square(&square);
	square.start_pixel[y] = SCREENHEIGHT / 2;
	square.color = map->floor_color;
	put_square(&square);
}

static inline void	ray_calc(t_raycast *cast, t_mlx *game, int ray_iter)
{
	cast->camera_x = (ray_iter * 2 / (double)SCREENWIDTH) - 1;
	cast->ray_pos[x] = game->vector.player_dir[x]
		+ (game->vector.plane[x] * cast->camera_x);
	cast->ray_pos[y] = game->vector.player_dir[y]
		+ (game->vector.plane[y] * cast->camera_x);
	cast->map_pos[x] = (int)game->vector.player_pos[x];
	cast->map_pos[y] = (int)game->vector.player_pos[y];
	if (cast->ray_pos[x] == 0)
		cast->map_delta[x] = INFINITY;
	else
		cast->map_delta[x] = fabs(1 / cast->ray_pos[x]);
	if (cast->ray_pos[y] == 0)
		cast->map_delta[y] = INFINITY;
	else
		cast->map_delta[y] = fabs(1 / cast->ray_pos[y]);
}

void rycstng_loop(void *data)
{
    static int    ray_iter;
    static t_raycast cast;
    t_map *map;
    t_mlx *mlx;
	t_cub3d *cub;

	cub.mlx = &mlx;
    cub.map = &map;
    map = ((t_cub3d *)data)->map;
    mlx = ((t_cub3d *)data)->mlx;
    put_floor(mlx->img_ptr, map);
    ray_iter = 0;
    while (ray_iter < SCREENWIDTH)
    {
        ray_calc(&cast, mlx, ray_iter);
        init_wall_hit_calc(&cast, mlx);
        wall_hit_calc(&cast, map);
        draw_wall(&cast, mlx, ray_iter);
        ray_iter++;
    }
    mlx_key_hook(mlx->mlx_ptr, key_event, &cub);
}