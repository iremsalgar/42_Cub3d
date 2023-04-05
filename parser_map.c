#include "cub3d.h"

static int	is_open_wall(char *map[], int i)
{
	if (i == 0 || map[i + 1] == (void *)0)
	{
		if (ft_strchr(map[i], '0') != (void *)0 \
		|| ft_strchr(map[i], 'N') != (void *)0 || ft_strchr(map[i], 'S') != (void *)0 \
		|| ft_strchr(map[i], 'E') != (void *)0 || ft_strchr(map[i], 'W') != (void *)0)
			return (0);
	}
	if (map[i][0] != '1' || map[i][ft_strlen(map[i]) - 2] != '1')
		return (0);
	return (1);
}

int	has_player(char *line)
{
	if (ft_strchr(line, 'N') == 0 && ft_strchr(line, 'S') == 0 \
	&& ft_strchr(line, 'E') == 0 && ft_strchr(line, 'W') == 0)
		return (1);
	return (0);
}

int	line_has_valid_walls(
	char *line_to_check, int j, const char *original_line
	)
{
	if (line_to_check == (void *)0)
		return (0);
	if (j > ft_strlen(line_to_check) - 1)
		return (0);
	if (j != 0)
	{
		if (line_to_check[j - 1] != 'X' && line_to_check[j - 1] != '1')
			return (1);
	}
	if (j + 1 != ft_strlen(line_to_check) \
	&& j + 1 != ft_strlen(line_to_check) - 1)
	{
		if (line_to_check != original_line \
		&& (line_to_check[j] != 'X' && line_to_check[j] != '1'))
			return (1);
		if (line_to_check[j + 1] != 'X' && line_to_check[j + 1] != '1')
			return (1);
	}
	return (0);
}

static inline int	has_valid_char(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '0' || line[i] == '1' || line[i] == 'N' \
		|| line[i] == 'S' || line[i] == 'E' || line[i] == 'W' \
		|| line[i] == '\n')
		{
			i++;
			continue ;
		}
		return (1);
	}
	return (0);
}

int	has_valid_map(const char *scene_file_path)
{
	int		player_count;
	char	**map;
	int		i;

	player_count = 0;
	map = adjust_map(get_map((char *)scene_file_path));
	i = 0;
	while (map[i])
	{
		if (!has_valid_char(map[i]))
			return (free_map_return(map, 1));
		if ((map[i + 1] != (void *)0 && map[i][ft_strlen(map[i]) - 1] != '\n') \
		|| is_open_wall(map, i) \
		|| (map[i + 1] != (void *)0 && is_empty_line(map[i + 1])) \
		|| ft_strchr(map[i], ' ') != (void *)0)
			return (free_map_return(map, 1));
		if (has_player(map[i]))
			player_count++;
		i++;
	}
	if (!has_valid_walls(scene_file_path) \
	|| has_non_empty_lines_after_map(scene_file_path) || player_count != 1)
		return (free_map_return(map, 1));
	return (free_map_return(map, 0));
}
