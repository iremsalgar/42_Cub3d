#include "cub3d.h"

int main(int ac, char **av)
{
    t_map map;
    t_cub3d all;
    t_mlx mlx;

    if(ac != 2)
    {
        write(2, "Error\nWrong number of arguments\n", 32);
        return (EXIT_FAILURE);
    }
    if (ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ".cub", 4))
    {
        write(2, "Error\nWrong file extension\n", 27);
        return (EXIT_FAILURE);
    }
    if(!parser(av[1], &all))
    {
        write(2, "Error\nParsing failed\n", 21);
        return (EXIT_FAILURE);
    }
    cub3d.mlx = &mlx;
    cub3d.map = &map;
    if(init_cub(&mlx, &map) != EXIT_SUCCESS)
    {
        write(2, "Error\nInitialization failed\n", 28);
        return (EXIT_FAILURE);
    }
    mlx_key_hook(mlx.win_ptr, close_esc, &cub3d);
    mlx_close_hook(mlx.win_ptr, free_close_all, &cub3d);
    if(!mlx_loop_hook(mlx.mlx_ptr, &rycstng_loop, &cub3d))
    {
        write(2, "Error\nLoop failed\n", 18);
        return (EXIT_FAILURE);
    }
    mlx_loop(mlx.mlx_ptr);
    mlx_terminate(mlx.mlx_ptr);
    return (EXIT_SUCCESS);
}
