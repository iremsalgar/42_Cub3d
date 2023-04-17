/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkayan <bkayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 00:42:28 by bkayan            #+#    #+#             */
/*   Updated: 2023/04/17 00:57:06 by bkayan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_check_file(t_data *data)
{
	int	fd;

	(void)data;
	fd = open("./texture/..", O_RDONLY, 777);
	if (fd < 0)
	{
		write(1, "Error: texture file not found\n", 30);
		ft_clear(data);
	}
}

int	ft_check_six(char **map)
{
	int	i;
	int	j;
	int	t;

	j = 0;
	t = 0;
	while (map[j] && map[j][0] != '1')
		j++;
	while (--j >= 0)
	{
		i = -1;
		while (map[j][++i])
		{
			if (map[j][i] == 'N' && map[j][i + 1] == 'O')
				t++;
			if (map[j][i] == 'S' && map[j][i + 1] == 'O')
				t++;
			if (map[j][i] == 'W' && map[j][i + 1] == 'E')
				t++;
			if (map[j][i] == 'E' && map[j][i + 1] == 'A')
				t++;
		}
	}
	if (t != 4)
		return (1);
	return (0);
}

void	ft_go_color(char *line, t_data *data, int i)
{
	int	j;
	int	nbr;
	int	t;

	j = 0;
	t = 0;
	while (line[++i])
	{
		if (line[i] == ',')
			t++;
		if (line[i] >= '0' && line[i] <= '9')
		{
			nbr = ft_atoi(line + i);
			if (nbr >= 256 || nbr < 0)
			{
				printf("Error!\n");
				ft_clear(data);
			}
		}
		else if (!(line[i] == ' ' || line[i] == '\n' || line[i] == ','))
		{
			printf("Error!\n");
			ft_clear(data);
		}
	}
	if (t != 2)
	{
		printf("Error!\n");
		ft_clear(data);
	}
}

void	ft_control_line(t_data *data, int j)
{
	int	i;
	int	k;

	k = 0;
	while (--j >= 0)
	{
		i = 0;
		while (data->map[j][i] && data->map[j][i] != '\n')
		{
			if (data->map[j][i] == 'F' || data->map[j][i] == 'C')
			{
				ft_go_color(data->map[j], data, i);
				break ;
			}
			else if (data->map[j][i] == 'N' || data->map[j][i] == 'S')
				break ;
			else if (data->map[j][i] == 'W' || data->map[j][i] == 'E')
				break ;
			else if (!(data->map[j][i] == '\n' || data->map[j][i] == ' '))
			{
				printf("Wrong\n");
				ft_clear(data);
			}
			i++;
		}
	}
	if (ft_check_six(data->map))
	{
		printf("Map Error!\n");
		ft_clear(data);
	}
}

void	ft_check_once_to_map(t_data *data)
{
	int	i;

	i = data->first_line;
	ft_control_line(data, i);
}
