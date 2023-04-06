#include "cub3d.h"

static inline void	texture_calc( t_draw *tex, t_raycast *cast, t_mlx *game)
{
	tex->wall_height = (int)(SCREENHEIGHT * WALLHEIGHT) / cast->wall_dist;
	tex->draw_start = (SCREENHEIGHT * WALLHEIGHT / 2) - (tex->wall_height / 2);
	if (tex->draw_start < 0)
		tex->draw_start = 0;
	tex->draw_end = (SCREENHEIGHT * WALLHEIGHT / 2) + (tex->wall_height / 2);
	if (tex->draw_end >= (SCREENHEIGHT * WALLHEIGHT))
		tex->draw_end = SCREENHEIGHT * WALLHEIGHT - 1;
	if (cast->border == NO_SO)
		tex->hit_wall = game->vector.player_pos[y]
			+ (cast->wall_dist * cast->ray_pos[y]);
	else
		tex->hit_wall = game->vector.player_pos[x]
			+ (cast->wall_dist * cast->ray_pos[x]);
	tex->hit_wall -= floor(tex->hit_wall);
	tex->tex_pixel[x] = (int)(tex->hit_wall
			* (double)game->texture[cast->wall_dir]->width);
	if ((cast->border == NO_SO && cast->ray_pos[x] > 0)
		|| (cast->border == WE_EA && cast->ray_pos[y] < 0))
		tex->tex_pixel[x] = game->texture[cast->wall_dir]->width
			- tex->tex_pixel[x] - 1;
	tex->step = ((double)game->texture[cast->wall_dir]->height)
		/ tex->wall_height;
	tex->tex_pos = (tex->draw_start - (SCREENHEIGHT * WALLHEIGHT / 2)
			+ (tex->wall_height / 2)) * tex->step;
}

static int tex_rgba(t_draw *tex, t_texture *tex_img)
{
    int color;

    color = *(int*)(tex_img->addr + (tex->tex_pixel[y] * tex_img->line_length
        + tex->tex_pixel[x] * (tex_img->bits_per_pixel / 8)));
    return (color);
}

void draw_wall(t_raycast *cast, t_mlx *game, int ray_iter)
{
    t_draw	tex;

	texture_calc(&tex, cast, game); 
	while (tex.draw_start < tex.draw_end)
	{
		tex.tex_pixel[x] = (int)tex.tex_pos;
        mlx_pixel_put(game->img_ptr, game->win_ptr, tex.draw_start, tex.draw_end,
			tex_rgba(&tex, game->texture[cast->wall_dir]));
		tex.tex_pos += tex.step;
		tex.draw_start++;
	}
}