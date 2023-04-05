#include "cub3d.h"

static char	**get_scene_content(const char *scene_file_path)
{
	char	**map;
	int		fd;
	int		i;
	char	*line;

	fd = open(scene_file_path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	map = ft_calloc(ft_get_line_count((char *)scene_file_path) + 1, \
	sizeof(*map));
	if (map == NULL)
		return (NULL);
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		map[i] = ft_strdup(line);
		free(line);
		line = get_next_line(fd);
		i += 1;
	}
	close(fd);
	return (map);
}

static inline void	iterate_content(
	char **scene_content, int *i, bool *was_in_map
	)
{
	while (scene_content[*i])
	{
		while (scene_content[*i] && is_in_map(scene_content[*i]))
		{
			*was_in_map = true;
			*i += 1;
		}
		if (*was_in_map)
			break ;
		*i += 1;
	}
}

void	ft_free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i += 1;
	}
	free(map);
}

static inline int	ft_free_map_return(char **scene_content, int ret)
{
	ft_free_map(scene_content);
	return (ret);
}

int ft_print_error_exit(char *error_msg, int error_code, char *error_file)
{
	if (error_msg)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd(error_msg, 2);
		if (error_file)
		{
			ft_putstr_fd(" in file ", 2);
			ft_putstr_fd(error_file, 2);
		}
		ft_putstr_fd("\n", 2);
	}
	return (error_code);
}

int		has_non_empty_lines_after_map(const char *scene_file_path)
{
	char	**scene_content;
	int		i;
	int		j;
	bool	was_in_map;

	scene_content = get_scene_content(scene_file_path);
	if (scene_content == NULL)
		ft_print_error_exit(ALLOC_ERROR, -1, NULL);
	i = 0;
	was_in_map = 1;
	iterate_content(scene_content, &i, &was_in_map);
	while (was_in_map && scene_content[i])
	{
		j = 0;
		while (scene_content[i][j])
		{
			if (ft_isalnum(scene_content[i][j]))
				return (ft_free_map_return(scene_content, 0));
			j += 1;
		}
		i += 1;
	}
	return (ft_free_map_return(scene_content, 1));
}