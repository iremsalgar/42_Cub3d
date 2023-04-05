#include "cub3d.h"

//HATALI

void mlx_delete_texture(int *texture_num)
{
    t_mlx *tmp;
    int i;
    i = texture_num;
    if (tmp->texture[i])
        mlx_destroy_image(tmp->mlx_ptr, tmp->img_ptr);
    free(tmp->texture[i]);
}

void	free_close_all(void *arg)
{
	t_cub3d	*cub3d;

	cub3d = (t_cub3d *)arg;
	ft_free_split(cub3d->map->map_content);
	free(cub3d->map->texture[0]);
	free(cub3d->map->texture[1]);
	free(cub3d->map->texture[2]);
	free(cub3d->map->texture[3]);
	mlx_delete_image(cub3d->mlx->mlx_ptr, cub3d->mlx->img_ptr);
	mlx_delete_texture(cub3d->mlx->texture[NORTH]);
	mlx_delete_texture(cub3d->mlx->texture[SOUTH]);
	mlx_delete_texture(cub3d->mlx->texture[WEST]);
	mlx_delete_texture(cub3d->mlx->texture[EAST]);
}

//mlx delete image

void mlx_delete_image(t_mlx *mlx, t_img *img)
{
    if (img->img_ptr)
        mlx_destroy_image(mlx->mlx_ptr, img->img_ptr);
    free(img);
}

/*
void free_at_window_close(t_cub3d *cub3d)
{
    int i;
    
    i = -1;
    while (++i < 5)
        free(cub3d->map->texture[i]);
    free(cub3d->map->map_content);
    free(cub3d->map);
    free(cub3d->mlx->mlx_ptr);
    free(cub3d->mlx->win_ptr);
    free(cub3d->mlx->img_ptr);
    free(cub3d->mlx);
    free(cub3d);
}*/

int key_event(int key_data)
{
    t_cub3d *cub3d;
    t_vector *vector;

    if(key_data == KEY_A)
        move_left_right(vector, cub3d->map->map_content, cub3d->mlx, 2);
    if(key_data == KEY_D)
        move_left_right(vector, cub3d->map->map_content, cub3d->mlx, 1);
    if(key_data == KEY_W)
        move_forward_back(vector, cub3d->map->map_content, cub3d->mlx, 3);
    if(key_data == KEY_S)
        move_forward_back(vector, cub3d->map->map_content, cub3d->mlx, 4);
}

int close_esc(int  key_data, void *arg)
{
    t_cub3d *cub3d;

    cub3d = (t_cub3d *)arg;
    if (key_data == KEY_ESC)
    {
        free_close_all(cub3d);
        mlx_close_window(cub3d->mlx->mlx_ptr);
    }
    return (0);
}

int	rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}