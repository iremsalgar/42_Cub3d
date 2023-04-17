/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkayan <bkayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 00:42:35 by bkayan            #+#    #+#             */
/*   Updated: 2023/04/17 04:38:00 by bkayan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_possiblty_tex(char *line )
{
	if (!ft_strncmp(line, "SO ", 3) || !ft_strncmp(line, "NO ", 3)
		|| !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3))
		return (1);
	return (0);
}

char	*get_path_check(char *line, char *ser)
{
	char	*path;
	char	*tmp;
	int		fd;

	tmp = line;
	path = ft_strtrim(line, ser);
	free(tmp);
	line = ft_strtrim(path, " ");
	free(path);
	fd = open(line, O_RDONLY);
	if (fd == -1)
	{
		printf("ERROR: Could not open texture");
		exit(0);
	}
	close(fd);
	return (line);
}

void	texture_value(t_data *data, char *line, int nbr)
{
	while (nbr < 4)
	{
		if (!ft_strncmp(line, "SO ", 3) && data->south_path == NULL)
			data->south_path = get_path_check(line, "SO");
		else if (!ft_strncmp(line, "NO ", 3) && data->north_path == NULL)
			data->north_path = get_path_check(line, "NO");
		else if (!ft_strncmp(line, "WE ", 3) && data->west_path == NULL)
			data->west_path = get_path_check(line, "WE");
		else if (!ft_strncmp(line, "EA ", 3) && data->east_path == NULL)
			data->east_path = get_path_check(line, "EA");
		else
		{
			return ;
		}
		nbr++;
	}
}

void	ft_check_text(t_data *data, char *line, int n_tex, t_index *index)
{
	char	*ptr;

	ptr = ft_strtrim(line, " ");
	if (check_possiblty_tex(ptr) && (data->south_path == NULL
			|| data->north_path == NULL || data->west_path == NULL
			|| data->east_path == NULL))
		texture_value(data, ptr, n_tex);
	else if (!ft_strncmp(ptr, "F ", 2) || !ft_strncmp(ptr, "C ", 2))
		get_color_values(data, ptr, index);
}
