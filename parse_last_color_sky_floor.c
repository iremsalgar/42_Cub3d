#include "cub3d.h"

int print_error_return(char *error_message, int return_value)
{
	ft_putstr_fd(error_message, STDERR_FILENO);
	return (return_value);
}

int	set_ceiling_color(
		t_map *scene_description,
		int r, int g, int b
)
{
	static bool	has_been_set = false;

	if (has_been_set)
		return (print_error_return(INVALID_IDENTIFIER_ERROR, 1));
	if ((r < 0 || r > 255) || (g < 0 || g > 255) || (b < 0 || b > 255))
		return (print_error_return(INVALID_COLOR_ERROR, 1));
	scene_description->sky_color = rgba(r, g, b, 0xFF);
	has_been_set = true;
	return (EXIT_SUCCESS);
}

int	set_floor_color(
		t_map *scene_description,
		int r, int g, int b
		)
{
	static bool	has_been_set = false;

	if (has_been_set)
		return (print_error_return(INVALID_IDENTIFIER_ERROR, 1));
	if ((r < 0 || r > 255) || (g < 0 || g > 255) || (b < 0 || b > 255))
		return (print_error_return(INVALID_COLOR_ERROR, 1));
	scene_description->floor_color = rgba(r, g, b, 0xFF);
	has_been_set = true;
	return (EXIT_SUCCESS);
}

bool	is_valid_color_description(char *desc)
{
	int	i;

	if (ft_chrcount(desc, ',') != 2)
		return (false);
	i = 0;
	while (desc[i] != '\0')
	{
		if (desc[i] == ',')
		{
			if (i == 0 || desc[i + 1] == '\0')
				return (false);
			if (!ft_isdigit(desc[i - 1]) && !ft_isalnum(desc[i + 1]))
				return (false);
		}
		else if (!ft_isdigit(desc[i]))
			return (false);
		i += 1;
	}
	return (true);
}

int	get_scene_description_from_content(
		char **scene_file_content,
		t_map *scene_description
)
{
	if (set_textures_and_colors_from_content(
			&scene_file_content, scene_description
		) != 0)
		return (print_error_return("Error\nInvalid Texture / Color\n", 1));
	if (set_map_from_content(
			scene_file_content, scene_description
		) != 0)
		return (print_error_return(INVALID_MAP_ERROR, 1));
	return (EXIT_SUCCESS);
}