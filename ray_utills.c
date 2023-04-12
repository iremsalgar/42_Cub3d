#include    "cub3d.h"

double	calculate_distance(double y_player, double x_player, double y_wall, double x_wall)
{
	return (sqrt(((x_player - x_wall) * (x_player - x_wall)) + ((y_player - y_wall) * (y_player - y_wall))));
}

double	fix_fisheye(t_mlx *mlx, double angle)
{
	mlx->corrected_distance = mlx->distance * cos((angle - mlx->field_of_view) * (M_PI / 180));
	return (mlx->corrected_distance);
}

void	my_mlx_pixel_put(t_my_mlx *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int *)dst = color ;
}