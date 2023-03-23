#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include "./mlx/mlx.h"

# define ALLOC_ERROR "Error\nAllocation Error\n"
# define ARG_NULL_ERROR "Error\nArgument is NULL\n"
# define NON_READABLE_FILE_ERROR "Error\nFile is not existent / invalid\n"
# define INVALID_MAP_ERROR "Error\nInvalid Map in .cub file\n"
# define INVALID_IDENTIFIER_ERROR "Error\nInvalid Identifier in .cub file\n"
# define INVALID_COLOR_ERROR "Error\nInvalid Color in .cub file\n"
# define INVALID_MAP_ERROR "Error\nInvalid Map in .cub file\n"
# define INVALID_TEXTURE_PATH "Error\nInvalid Texture Path in .cub file\n"

# define FOV 0.66
# define PI 3.14159265359
# define WALLHEIGHT 1
# define MOVESPEED 0.03
# define ROTSPEED 0.02

# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_ESC 53


enum e_direction
{
    NORTH = 0,
    SOUTH = 1,
    WEST  = 2,
    EAST = 3
};

enum e_screensize
{
	SCREENWIDTH = 1920,
	SCREENHEIGHT = 1080
};

enum e_grid
{
    x = 0,
    y = 1
};

enum e_borders
{
	NO_SO = 0, 
	WE_EA = 1
};

typedef struct s_player
{
    int pos[2];
    enum e_direction direction;
} t_player;

typedef struct s_map
{
    char *texture[4];
    char **map_content;
    int floor_color;
    int sky_color;
    t_player player;
} t_map;

typedef struct s_vector
{
    double player_pos[2]; // x, y posX / posY
    double player_dir[2]; // x, y dirX / dirY
    double plane[2]; // x, y planeX / planeY
} t_vector;

typedef struct s_mlx
{
    mlx_t *mlx_ptr;       // mlx
    mlx_image_t *img_ptr; // image
    mlx_texture_t *texture[4]; // 0 = north, 1 = south, 2 = west, 3 = east
    t_vector vector;
} t_mlx;

typedef struct s_cub3d
{
    t_map *map;
    t_mlx *mlx;
} t_cub3d;

typedef struct s_raycast
{
    double camera_x;
    double ray_pos[2]; // x, y posX / posY
    int map_pos[2]; // x, y mapX / mapY
    double map_delta[2]; // x, y deltaDistX / deltaDistY
    double side_dist[2]; // x, y sideDistX / sideDistY
    int step[2]; // x, y stepX / stepY
    int border; // 0 = NO_SO, 1 = WE_EA
    int pot_wall_dir[2]; // x, y potantial wallX / wallY
    int wall_dir; // 0 = north, 1 = south, 2 = west, 3 = east
    double wall_dist; // wallDist 
} t_raycast;

typedef struct s_draw
{
    int wall_height;
    int draw_start;
    int draw_end;
    double hit_wall;
    double step;
    int tex_pixel[2]; // x, y texX / texY
    int tex_pos; // texPos
} t_draw;

typedef struct s_square
{
    mlx_image_t *img;
    int start[2]; // x, y
    int len[2]; // x, y
    int color;
} t_square;

//fonctions
int main(int ac, char **av);
int ft_strlen(const char *s);
int ft_strncmp(const char *s1, const char *s2, size_t n);

//init
int init_game(t_mlx *mlx, t_map *map);
#endif