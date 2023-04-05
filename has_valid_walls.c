#include "cub3d.h"

int	is_valid_map_char(char ch)
{
    if (ch == '0')
		return (0);
	if (ch == '1')
		return (0);
	if (ch == 'N' || ch == 'S' || ch == 'E' || ch == 'W')
		return (0);
	if (ch == '\n')
		return (0);
	if (ft_isspace(ch))
		return (1);
	return (1);
}
int	is_wall(char ch)
{
    return (ch == 1);
}

static char	**getmap(const char *scene_file_path)
{
	char	**map;
	char	*line;
	int		fd;
	int		i;

	fd = open(scene_file_path, O_RDONLY);
	if (fd == -1)
		return (0);
	map = ft_calloc(ft_get_line_count((char *)scene_file_path) + 1, \
	sizeof(*map));
	if (map == (void *)0)
		return (0);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (is_in_map(line))
		{
			map[i] = ft_strdup(line);
			i += 1;
		}
		free(line);
		line = get_next_line(fd);
	}
	return (map);
}

static inline int	is_valid_minus(char *map[], int i, int j)
{
	int	k;
	int	l;

	k = i;
	l = j;
	while (k >= 0 && l >= 0)
	{
		if (!is_valid_map_char(map[k][l]) || !is_valid_map_char(map[k][j]) \
		|| !is_valid_map_char(map[i][l]))
			return (1);
		if (is_wall(map[k][l]) || is_wall(map[k][j]) || is_wall(map[i][l]))
			break ;
		k -= 1;
		l -= 1;
	}
	return (0);
}

static inline int	is_valid_plus(char *map[], int i, int j)
{
	int	k;
	int	l;

	k = i;
	l = j;
	while (map[k] && map[k][l])
	{
		if (!is_valid_map_char(map[k][l]) || !is_valid_map_char(map[k][j]) \
		|| !is_valid_map_char(map[i][l]))
			return (1);
		if (is_wall(map[k][l]) || is_wall(map[k][j]) || is_wall(map[i][l]))
			break ;
		k += 1;
		l += 1;
	}
	return (0);
}

static inline int	is_valid(char *map[], int i, int j)
{
	if (map[i - 1])
	{
		if (ft_strlen(map[i - 1]) < j)
			return (1);
	}
	if (map[i + 1])
	{
		if (ft_strlen(map[i + 1]) < j)
			return (1);
	}
	return (is_valid_minus(map, i, j) && is_valid_plus(map, i, j));
}

int	has_valid_walls(const char *scene_file_path)
{
	char	**map;
	int		i;
	int		j;

	map = getmap((char *)scene_file_path);
	if (map == (void *)0)
		return (1);
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0' && !is_valid(map, i, j))
				return (free_map_return(map, 1));
			j += 1;
		}
		i += 1;
	}
	ft_free_split(map);
	return (0);
}