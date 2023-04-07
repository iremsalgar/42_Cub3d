#include "cub3d.h"

int main(int ac, char **av)
{
    t_map map;
    t_cub3d *cub;
    t_mlx mlx;
    t_data *data;

    if(ac != 2)
    {
        write(2, "Error\nWrong number of arguments\n", 32);
        return (EXIT_FAILURE);
    }
    ft_all_check_and_read_map(data, av[1]);
    perror("Error4");
    cub = ft_calloc(sizeof(t_cub3d),1);
    cub->mlx = &mlx;
    cub->map = &map;
    if(init_game(&mlx, &map) != EXIT_SUCCESS)
    {
        write(2, "Error\nInitialization failed\n", 28);
        return (EXIT_FAILURE);
    }
    perror("Error2");
    mlx_key_hook(mlx.mlx_ptr, close_esc, &cub);
    mlx_loop_hook(mlx.mlx_ptr, ray_loop, &cub);
    perror("Error3");
    mlx_loop(mlx.mlx_ptr);
    return (EXIT_SUCCESS);
}
