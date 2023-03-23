#include <cub3d.h>

static inline void init_dir_we_ea(int first_direction, t_vector *vector)
{
    if(first_direction == WEST)
    {
        vector->player_dir[x] = -1;
        vector->player_dir[y] = 0;
        vector->plane[x] = 0;
        vector->plane[y] = FOV * -1;
    }
    else if(first_direction == EAST)
    {
        vector->player_dir[x] = 1;
        vector->player_dir[y] = 0;
        vector->plane[x] = 0;
        vector->plane[y] = FOV;
    }
}

static inline bool init_dir_no_so(int  first_direction, t_vector *vector)
{
    if(first_direction == NORTH)
    {
        vector->player_dir[x] = -1;
        vector->player_dir[y] = 0;
        vector->plane[x] = 0;
        vector->plane[y] = 0.66;
        return (true);
    }
    else if(first_direction == SOUTH)
    {
        vector->player_dir[x] = 1;
        vector->player_dir[y] = 0;
        vector->plane[x] = 0;
        vector->plane[y] = -0.66;
        return (true);
    }
    return (false);
}

int init_game(t_mlx *mlx, t_map *map)
{
    mlx->vector.player_pos[x] = map->player.pos[x] + 0.5;
    mlx->vector.player_pos[y] = map->player.pos[y] + 0.5;
    if(init_dir_no_so(map->player.direction, &(mlx->vector)))
        init_dir_we_ea(map->player.direction, &(mlx->vector));
    mlx->texture[NORTH] =  mlx_load_texture(mlx->mlx_ptr, map->texture[NORTH]);
    mlx->texture[SOUTH] =  mlx_load_texture(mlx->mlx_ptr, map->texture[SOUTH]);
    mlx->texture[WEST] =  mlx_load_texture(mlx->mlx_ptr, map->texture[WEST]);
    mlx->texture[EAST] =  mlx_load_texture(mlx->mlx_ptr, map->texture[EAST]);
    if(!mlx->texture[NORTH] || !mlx->texture[SOUTH] || !mlx->texture[WEST] || !mlx->texture[EAST])
    {
        write(2, "Error\nTexture loading failed\n", 29);
        return (EXIT_FAILURE);
    }
    mlx->mlx_ptr = mlx_init(SCREENWIDTH, SCREENHEIGHT, "ORDEK", false);
    if(!mlx->img_ptr)
    {
        write(2, "Error\nImage initialization failed\n", 34);
        return (EXIT_FAILURE);
    }
    mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, SCREENWIDTH, SCREENHEIGHT);
    if(!mlx->img_ptr)
    {
        write(2, "Error\nImage initialization failed\n", 34);
        return (EXIT_FAILURE);
    }
    if(mlx_image_to_window(mlx->mlx_ptr, mlx->img_ptr, 0, 0) != EXIT_SUCCESS)
    {
        write(2, "Error\nImage to window failed\n", 29);
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}