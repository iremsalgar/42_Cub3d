/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkayan <bkayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 00:45:19 by bkayan            #+#    #+#             */
/*   Updated: 2023/04/17 04:57:26 by bkayan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_mlx	*wind;
	t_data	*data;

	if (ac != 2)
	{
		write(2, "Error\nWrong number of arguments\n", 32);
		return (EXIT_FAILURE);
	}
	wind = ft_calloc(sizeof(t_mlx), 1);
	data = ft_calloc(sizeof(t_data), 1);
	ft_all_check_and_read_map(data, av[1]);
	wind->data = data;
	wind->map = data->map;
	wind->mlx = mlx_init();
	wind->window = mlx_new_window(wind->mlx, WINDOW_WIDTH,
			WINDOW_HEIGHT, "Cub3D");
	images_to_xpm(wind);
	get_player_position(wind);
	projecting_rays(wind);
	mlx_hook(wind->window, 2, 0, get_keys, wind);
	mlx_hook(wind->window, 17, 0, destroy_window, wind);
	mlx_loop(wind);
	return (EXIT_SUCCESS);
}
