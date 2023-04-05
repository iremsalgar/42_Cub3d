#include "cub3d.h"

void mlx_terminate(int *mlx_ptr)
{
    if (mlx_ptr)
        mlx_destroy_display(mlx_ptr);
    free(mlx_ptr);
}

int main(int ac, char **av)
{
    t_map map;
    t_cub3d cub;
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
    if(!parser(av[1], &map))
    {
        write(2, "Error\nParsing failed\n", 21);
        return (EXIT_FAILURE);
    }
    cub.mlx = &mlx;
    cub.map = &map;
    if(init_game(&mlx, &map) != EXIT_SUCCESS)
    {
        write(2, "Error\nInitialization failed\n", 28);
        return (EXIT_FAILURE);
    }
    mlx_key_hook(mlx.mlx_ptr, close_esc, &cub);
    if(!mlx_loop_hook(mlx.mlx_ptr, &rycstng_loop, &cub))
    {
        write(2, "Error\nLoop failed\n", 18);
        return (EXIT_FAILURE);
    }
    mlx_loop(mlx.mlx_ptr);
    //mlx_terminate(mlx.mlx_ptr);
    return (EXIT_SUCCESS);
}
