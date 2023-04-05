# include <stddef.h>
#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include "./mlx/mlx.h"
# include <string.h>

# define FOV 0.66
# define PI 3.14159265359
# define WALLHEIGHT 1
# define MOVESPEED 0.03
# define ROTSPEED 0.02
# define FLOOR 0
# define CEILING 1

# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_ESC 53
#define KEY_LEFT 123
#define KEY_RIGHT 124

# define ALLOC_ERROR "Error\nAllocation Error\n"
# define ARG_NULL_ERROR "Error\nArgument is NULL\n"
# define NON_READABLE_FILE_ERROR "Error\nFile is not existent / invalid\n"
# define INVALID_MAP_ERROR "Error\nInvalid Map in .cub file\n"
# define INVALID_IDENTIFIER_ERROR "Error\nInvalid Identifier in .cub file\n"
# define INVALID_COLOR_ERROR "Error\nInvalid Color in .cub file\n"
# define INVALID_MAP_ERROR "Error\nInvalid Map in .cub file\n"
# define INVALID_TEXTURE_PATH "Error\nInvalid Texture Path in .cub file\n"

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

typedef struct s_map  //sce_Des
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
    double plane[2]; // x, y planeX / planeY camera
} t_vector;

typedef struct s_mlx  //game
{
    int *mlx_ptr;       // mlx
    void *img_ptr; // image
    int *win_ptr; // window
    int *texture[4]; // 0 = north, 1 = south, 2 = west, 3 = east
    t_vector vector;
} t_mlx;

typedef struct s_cub3d
{
    t_map *map;
    t_mlx *mlx;
} t_cub3d;

typedef struct t_img
{
    void	*img_ptr;
    char	*addr;
    int		bits_per_pixel;
    int		line_length;
    int		endian;
}	t_img;

typedef struct s_raycast
{
    double camera_x;
    double ray_pos[2]; // x, y posX / posY
    int map_pos[2]; // x, y mapX / mapY
    double map_delta[2]; // x, y deltaDistX / deltaDistY
    double side_dist[2]; // x, y sideDistX / sideDistY playerPos + rayPos?
    int direction[2]; // x, y stepX / stepY
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
    double step; // step for texture calc step is 1.0 * texture.height / wallHeight
    int tex_pixel[2]; // x, y texX / texY
    int tex_pos; // texPos
} t_draw;

typedef struct s_square
{
    void *img;
    int start_pixel[2]; // x, y
    int len[2]; // x, y
    int color;
} t_square;

typedef struct s_texture
{
    void    *img;
    int     *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
    int     width;
    int     height;
    void    *mlx_ptr;
}               t_texture;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_list{
	char			*x;
	struct s_list	*next;
}t_list;

char	*get_next_line(int fd);
char	*get_line(char *line);
t_list	*ft_lstnew(void);
char	*ft_controller(char *str, const char c, t_list *y);
int		ft_chk(const char *a, int chker, int c);
char	*ft_strjoin(char *s1, const char *s2);
char	*ft_strdup(const char *s1);

char	*ft_cutter(char *str, char c, int i);

//functions
int     main(int ac, char **av);
int     key_event(int key_data);
int print_error_exit(char *error_msg, int error_code, char *error_file);

//close

void    mlx_delete_texture(int *texture_num);
void	free_close_all(void *arg);
int     close_esc(int  key_data, void *arg);
void	ft_free_map(char **map);

//init
int init_game(t_mlx *mlx, t_map *map);

//dda and raycasting

void    rycstng_loop(void *data);
void	init_wall_hit_calc(t_raycast *cast, t_mlx *game);
void	wall_hit_calc(t_raycast *cast, t_map *map);
void	wall_hit_calc_result(t_raycast *cast);
void    draw_wall(t_raycast *cast, t_mlx *game, int ray_iter);
void    mlx_put_pixel(t_img *img, int x, int y, int color);

//move and rotate

void	check_movement(t_vector *vectors, char **map, t_mlx *mlx_ptr, int flag);
void	move_forward_back(struct s_vector *vector, char **map, t_mlx *mlx_ptr, int flag);
void	move_left_right(t_vector *vectors, char **map, t_mlx *mlx_ptr, int flag);
static inline void	move(
	double new_player_y, double new_player_x, char **map, t_vector *vectors
	);

//rgba
int	rgba(int r, int g, int b, int a);

//parser

int	parser(
		const char *scene_file_path,
		t_map *scene_description
		);
int 	has_valid_map(const char *scene_file_path);
int 	has_player(char *line);
int 	has_valid_identifier(const char *scene_file_path);
int 	has_non_empty_lines_after_map(const char *scene_file_path);
int 	line_has_valid_walls(
char    *line_to_check, int j, const char *original_line);
static int	is_open_wall(char *map[], int i);
int	    is_in_map(const char *line);
int 	is_empty_line(const char *line);
char	**get_scene_file_content(
		const char *scene_file_path
);
char	**get_map(char *scene_file_path);
char	**adjust_map(char *map[]);

//wall

int	has_valid_walls(const char *scene_file_path);
static inline int	is_valid(char *map[], int i, int j);
int	is_valid_map_char(char ch);
int	is_wall(char ch);
//utils
int     ft_strlen(const char *s);
int     ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_putstr_fd(char *s, int fd);
void	*ft_free_split(char **split);
int	    ft_atoi(const char *str);
int	    ft_isspace(int c);
int	    ft_isdigit(int c);
int     ft_issign(int c);
void	*ft_calloc(size_t count, size_t size);
void    ft_bzero(void *s, size_t n); 
char	*ft_strstr(const char *haystack, const char *needle);
int     ft_get_line_count(char *path);
int     ft_isalnum(int c);
char	*ft_strchr(const char *s, int c);
int     ft_strcmp(const char *s1, const char *s2);
int     free_map_return(char *map[], int return_value);
int     print_error_return(char *error_message, int return_value);
#endif
