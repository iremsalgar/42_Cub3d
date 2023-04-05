#include    "cub3d.h"

static inline void	move(
	double new_player_y, double new_player_x, char **map, t_vector *vectors
	)
{
	if (map[(int)new_player_y][(int)new_player_x] != '1')
	{
		vectors->player_pos[y] = new_player_y;
		vectors->player_pos[x] = new_player_x;
	}
}

void	move_left_right(t_vector *vectors, char **map, t_mlx *mlx_ptr, int flag)
{
	if (flag == 1)	// D
	{
		move(vectors->player_pos[x],
			vectors->player_pos[x]
			- (vectors->player_dir[y] * MOVESPEED), map, vectors);
		move(vectors->player_pos[y]
			+ (vectors->player_dir[x] * MOVESPEED),
			vectors->player_pos[x], map, vectors);
	}
	if (flag == 2) //A	
	{
		move(vectors->player_pos[y],
			vectors->player_pos[x]
			+ (vectors->player_dir[y] * MOVESPEED), map, vectors);
		move(vectors->player_pos[x]
			- (vectors->player_dir[x] * MOVESPEED),
			vectors->player_pos[x], map, vectors);
	}
}


void	move_forward_back(struct s_vector *vector, char **map, t_mlx *mlx_ptr, int flag)
{
    if (flag == 3)
	{
        move(vector->player_pos[y],
            vector->player_pos[x]
            + (vector->player_dir[x] * MOVESPEED), map, vector);
        move(vector->player_pos[y]
            + (vector->player_dir[y] * MOVESPEED),
            vector->player_pos[x], map, vector);
    }
	if (flag == 4)
	{
		move(vector->player_pos[y],
			vector->player_pos[x]
			+ (vector->player_dir[y] * MOVESPEED), map, vector);
		move(vector->player_pos[y]
			- (vector->player_dir[x] * MOVESPEED),
			vector->player_pos[x], map, vector);
	}
}

void	check_move(t_vector *vectors, char **map, t_mlx *mlx_ptr)
{
	int flag;
	t_cub3d cub;
	t_mlx mlx;

	mlx_key_hook(mlx.mlx_ptr, key_event, &cub);
	if()
		move_left_right(vectors, map, mlx_ptr, flag);
	if(flag == 3 || flag == 4)
		move_forward_back(vectors, map, mlx_ptr, flag);
}