#include "cub3d.h"

static inline void	rotate_left(
	t_vector *vectors,
	const double *old_player_dir, const double *old_camera_plane
	)
{
	vectors->player_dir[x] = vectors->player_dir[x] \
	* cos(-ROTSPEED) - vectors->player_dir[y] * sin(-ROTSPEED);
	vectors->player_dir[y] = old_player_dir[x] * sin(-ROTSPEED) \
	+ vectors->player_dir[y] * cos(-ROTSPEED);
	vectors->plane[x] = vectors->plane[x] \
	* cos(-ROTSPEED) - vectors->plane[y] * sin(-ROTSPEED);
	vectors->plane[y] = old_camera_plane[x] * sin(-ROTSPEED) \
	+ vectors->plane[y] * cos(-ROTSPEED);
}

static inline void	rotate_right(
	t_vector *vectors,
	const double *old_player_dir, const double *old_camera_plane
	)
{
	vectors->player_dir[x] = vectors->player_dir[x] * cos(ROTSPEED) \
	- vectors->player_dir[x] * sin(ROTSPEED);
	vectors->player_dir[y] = old_player_dir[x] * sin(ROTSPEED) \
	+ vectors->player_dir[y] * cos(ROTSPEED);
	vectors->plane[x] = vectors->plane[x] \
	* cos(ROTSPEED) - vectors->plane[y] * sin(ROTSPEED);
	vectors->plane[y] = old_camera_plane[x] * sin(ROTSPEED) \
	+ vectors->plane[y] * cos(ROTSPEED);
}

void	check_rotate(t_vector *vectors, t_mlx *mlx_ptr)
{
	double	old_player_dir[1];
	double	old_camera_plane[1];

	old_player_dir[x] = vectors->player_dir[x];
	old_camera_plane[x] = vectors->plane[x];
	rotate_left(vectors, old_player_dir, old_camera_plane);
	rotate_right(vectors, old_player_dir, old_camera_plane);
}