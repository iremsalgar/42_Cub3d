#include "cub3d.h"

int	free_map_return(char *map[], int return_value)
{
	ft_free_split(map);
	return (return_value);
}

void	print_error_exit(char *error_message, int exit_code, void *to_free)
{
	free(to_free);
	ft_putstr_fd(error_message, STDERR_FILENO);
	exit(exit_code);
}

int	is_in_map(const char *line)
{
	if (is_empty_line(line))
		return (1);
	if (ft_strncmp(line, "NO", 2) == 0 || ft_strncmp(line, "SO", 2) == 0
		|| ft_strncmp(line, "EA", 2) == 0 || ft_strncmp(line, "WE", 2) == 0)
		return (1);
	if (ft_strncmp(line, "C", 1) == 0 || ft_strncmp(line, "F", 1) == 0)
		return (1);
	//null vardı değişti
	if (ft_strchr(line, '1') == 0 && ft_strchr(line, '0') == 0
		&& ft_strchr(line, 'N') == 0 && ft_strchr(line, 'S') == 0
		&& ft_strchr(line, 'E') == 0 && ft_strchr(line, 'W') == 0)
		return (1);
	return (0);
}
/*
bool	line_has_valid_walls(
			char *line_to_check, int j, const char *original_line
			);
*/
int	is_neighbor_to_wall_char(char *map[], int i, int j)
{
	if (i != 0 && !line_has_valid_walls(map[i - 1], j, map[i]))
		return (1);
	if (!line_has_valid_walls(map[i], j, map[i]))
		return (1);
	if (map[i + 1] != 0 && !line_has_valid_walls(map[i + 1], j, map[i]))
		return (1);
	return (0);
}