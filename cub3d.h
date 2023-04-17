/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkayan <bkayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 00:45:13 by bkayan            #+#    #+#             */
/*   Updated: 2023/04/17 04:33:55 by bkayan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include "./mlx/mlx.h"
# include <string.h>

# define WALL_1 "./textures/wall_1.xpm"
# define WALL_2 "./textures/wall_2.xpm"
# define WALL_3 "./textures/wall_3.xpm"
# define WALL_4 "./textures/wall_4.xpm"

# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_ESC 53
# define KEY_LEFT 123
# define KEY_RIGHT 124

# define ALLOC_ERROR "Error\nAllocation Error\n"
# define ARG_NULL_ERROR "Error\nArgument is NULL\n"
# define NON_READABLE_FILE_ERROR "Error\nFile is not existent / invalid\n"
# define INVALID_MAP_ERROR "Error\nInvalid Map in .cub file\n"
# define INVALID_IDENTIFIER_ERROR "Error\nInvalid Identifier in .cub file\n"
# define INVALID_COLOR_ERROR "Error\nInvalid Color in .cub file\n"
# define INVALID_MAP_ERROR "Error\nInvalid Map in .cub file\n"
# define INVALID_TEXTURE_PATH "Error\nInvalid Texture Path in .cub file\n"

# define WINDOW_WIDTH 1080.0
# define WINDOW_HEIGHT 1080.0

# define TRUE 1

# define WALL_DIM 64.0
# define HALF_WALL 32.0

/*
	Represents the angular of our triangle
*/
# define THETA	64.0

/*
	Distance to move in pixels
*/
# define PX_MOVE	10.0

/*
	In ordre to rotate the player around 
*/
# define PX_ROTATION	10.0

typedef struct s_data {
	char	**map;
	int		first_line;
	int		last_line;
	int		max_long;
	int		map_weight;
	char	*north_path;
	char	*south_path;
	char	*west_path;
	char	*east_path;
	int		floor_color;
	int		ceiling_color;
}		t_data;

typedef struct s_index {
	int	n_derc;
	int	n_color;
	int	maze_index;
	int	new_line;
}	t_index;

typedef struct s_my_mlx
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;

	int		bpp_n;
	int		l_len_n;
	int		endian_n;

	int		bpp_s;
	int		l_len_s;
	int		endian_s;

	int		bpp_w;
	int		l_len_w;
	int		endian_w;

	int		bpp_e;
	int		l_len_e;
	int		endian_e;

	int		bpp_c;
	int		l_len_c;
	int		endian_c;

	char	*addr_n;
	char	*addr_s;
	char	*addr_w;
	char	*addr_e;
	char	*addr_c;
}	t_my_mlx;

typedef struct s_window
{
	void		*mlx;
	void		*window;
	char		**map;
	int			width;
	int			height;

	char		*n_img;
	char		*s_img;
	char		*e_img;
	char		*w_img;

	char		*n_xpm;
	char		*s_xpm;
	char		*e_xpm;
	char		*w_xpm;

	double		field_of_view;

	double		x_player;
	double		y_player;

	double		x_step;
	double		y_step;

	int			x_m;
	int			y_m;

	char		dir;

	double		distance;
	double		corrected_distance;

	int			ceilling;
	int			floor;

	double		where;

	double		dst_to_projection;
	double		projection_3d;
	double		flo_cei;
	char		*color;

	t_data		*data;
	t_my_mlx	my_mlx;
}	t_mlx;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_list{
	char			*x;
	struct s_list	*next;
}t_list;

//get_next_line
char	*get_next_line(int fd);
char	*get_line(char *line);
t_list	*ft_lstnew(void);
char	*ft_controller(char *str, const char c, t_list *y);
int		ft_chk(const char *a, int chker, int c);
char	*ft_strjoin(char *s1, const char *s2);
char	*ft_strdup(const char *s1);
char	*ft_cutter(char *str, char c, int i);

//functions
int		main(int ac, char **av);
void	images_to_xpm(t_mlx *wind);
void	get_player_position(t_mlx *wind);
void	set_field_of_view(t_mlx *wind, char in_map);
int		get_keys(int press, t_mlx *wind);

//close
int		destroy_window(t_mlx *wind);

//dda and raycasting
void	casting_3d(double distance, int height, t_mlx *mlx, char dir);
void	cast_rays(t_mlx *wind, double angle, int x);
void	draw(t_mlx *mlx, int i, char dir);
void	projecting_rays(t_mlx *wind);
double	calculate_distance(double y_player, double x_player,
			double y_wall, double x_wall);
double	fix_fisheye(t_mlx *mlx, double angle);
void	my_mlx_pixel_put(t_my_mlx *data, int x, int y, int color);

//move and rotate
void	rotate_right(t_mlx *wind);
void	rotate_left(t_mlx *wind);
void	move_forward(t_mlx *wind);
void	move_backword(t_mlx *wind);
void	move_right(t_mlx *wind);
void	move_left(t_mlx *wind);

//direciton
char	set_directions(double w_y, double w_x, t_mlx *wind);
char	check_south_west(double w_y, double w_x, t_mlx *wind);
char	check_south_east(double w_y, double w_x, t_mlx *wind);
char	check_north_west(double w_y, double w_x, t_mlx *wind);
char	check_north_east(double w_y, double w_x, t_mlx *wind);

//texture
char	*west_texture(t_mlx *mlx, int i);
char	*east_texture(t_mlx *mlx, int i);
char	*north_texture(t_mlx *mlx, int i);
char	*south_texture(t_mlx *mlx, int i);

//color
void	get_color_values(t_data *parsing, char *line, t_index *index);
int		ft_get_color(char *line, char *str);
int		check_verg(char *line);
int		stat_color(char s, int *vergul, int *nbr, int *rgb);

//parser
int		ft_check_cub(char *s);
void	ft_clear(t_data *data);
void	ft_check_map(t_data *data);
void	ft_check_wall(t_data *data, char *map);
void	ft_all_check_and_read_map(t_data *data, char *map);
void	ft_check_for_long(t_data *data);
void	ft_check_once_to_map(t_data *data);
void	ft_addjust2(t_data *data);
void	ft_check_file(t_data *data);
void	ft_find(t_data *data);
void	texture_value(t_data *data, char *line, int nbr);
void	ft_check_text(t_data *data, char *line, int n_tex, t_index *index);
int		check_possiblty_tex(char *line );
char	*get_path_check(char *line, char *ser);
void	ft_read_map(t_data *data, char *cubfile, t_index *index);
void	ft_check_have_map(t_data *data);

//utils
int		ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_putstr_fd(char *s, int fd);
int		ft_atoi(const char *str);
int		ft_isspace(int c);
int		ft_isdigit(int c);
int		ft_issign(int c);
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *s, size_t n);
int		ft_get_line_count(char *path);
int		ft_isalnum(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strtrim(char *s1, char const *set);

#endif
