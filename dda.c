#include "cub3d.h"

//degisebilir
static inline void	x_direction(t_raycast *cast, t_mlx *game)
{
    if (cast->ray_pos[x] < 0)
    {
        cast->direction[x] = -1;
        cast->side_dist[x] = (game->vector.player_pos[x] - cast->map_pos[x])
            * cast->map_delta[x];
    }
    else
    {
        cast->direction[x] = 1;
        cast->side_dist[x] = (cast->map_pos[x] + 1.0 - game->vector.player_pos[x])
            * cast->map_delta[x];
    }
}

static inline void	y_direction(t_raycast *cast, t_mlx *game)
{
    if (cast->ray_pos[y] < 0)
    {
        cast->direction[y] = -1;
        cast->side_dist[y] = (game->vector.player_pos[y] - cast->map_pos[y])
            * cast->map_delta[y];
    }
    else
    {
        cast->direction[y] = 1;
        cast->side_dist[y] = (cast->map_pos[y] + 1.0 - game->vector.player_pos[y])
            * cast->map_delta[y];
    }
}

void	wall_hit_calc_result(t_raycast *cast)
{
	if (cast->border == NO_SO)
	{
		cast->wall_dist = cast->side_dist[x]
			- cast->map_delta[x];
		cast->wall_dir = cast->pot_wall_dir[x];
	}
	else
	{
		cast->wall_dist = cast->side_dist[y]
			- cast->map_delta[y];
		cast->wall_dir = cast->pot_wall_dir[y];
	}
}

void	wall_hit_calc(t_raycast *cast, t_map *map)
{
	while (true)
	{
		if (cast->side_dist[x] < cast->side_dist[y])
		{
			cast->side_dist[x] += cast->map_delta[x];
			cast->map_pos[x] += cast->direction[x];
			cast->border = NO_SO;
		}
		else
		{
			cast->side_dist[y] += cast->map_delta[y];
			cast->map_pos[y] += cast->direction[y];
			cast->border = WE_EA;
		}
		if (map->map_content[cast->map_pos[y]][cast->map_pos[x]] == '1')
			break ;
	}
	wall_hit_calc_result(cast);
}

void	init_wall_hit_calc(t_raycast *cast, t_mlx *game)
{
	x_direction(cast, game);
	y_direction(cast, game);
}