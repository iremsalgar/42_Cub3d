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
    char    *texture[4];
    char    **map_content;
    int     floor_color;
    int     sky_color;
    t_player player;
} t_map;

typedef struct s_vector
{
    double player_pos[2]; // x, y posX / posY
    double player_dir[2]; // x, y dirX / dirY
    double plane[2]; // x, y planeX / planeY camera
} t_vector;

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

typedef struct s_mlx  //game
{
    void        *mlx_ptr;       // mlx
    void        *img_ptr; // image
    int         *win_ptr; // window
    t_texture   *texture[4]; // 0 = north, 1 = south, 2 = west, 3 = east
    t_vector    vector;
    int         width;
    int         height;
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
    t_mlx   *img;
    int start_pixel[2]; // x, y
    int len[2]; // x, y
    int color;
} t_square;

typedef struct s_data{
    char    **map;    
    int		first_line;
    int		last_line;
    int		max_long;
    int		map_weight;
} t_data;


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
int     main(int ac, char **av);
int     ray_loop(void *data);
int     key_event(int key_data, void *arg);

//close
int     close_esc(int  key_data, void *arg);

//init
int init_game(t_mlx *mlx, t_map *map);

//dda and raycasting

void    rycstng_loop(void *data);
void	init_wall_hit_calc(t_raycast *cast, t_mlx *game);
void	wall_hit_calc(t_raycast *cast, t_map *map);
void	wall_hit_calc_result(t_raycast *cast);
void    draw_wall(t_raycast *cast, t_mlx *game, int ray_iter);

//move and rotate
void	check_rotate(struct s_vector *vectors, t_mlx *mlx_ptr);
void	check_move(t_vector *vectors, char **map, t_mlx *mlx_ptr);
void	move_forward_back(struct s_vector *vector, char **map, t_mlx *mlx_ptr, int flag);
void	move_left_right(t_vector *vectors, char **map, t_mlx *mlx_ptr, int flag);
static inline void	move(
	double new_player_y, double new_player_x, char **map, t_vector *vectors
	);

//rgba
int	rgba(int r, int g, int b, int a);

//parser
int     ft_check_cub(char *s);
void    ft_clear(t_data *data);
void    ft_check_map(t_data *data);
void    ft_check_wall(t_data *data);
void    ft_all_check_and_read_map(t_data *data, char *map);
void    ft_check_for_long(t_data *data);
void    ft_check_once_to_map(t_data *data);
void    ft_addjust2(t_data *data);
void    ft_check_file(t_data *data);
void    ft_find(t_data *data);

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
char	*ft_append(char **dst, char *src);
int     ft_free(void *ptr);
int     ft_chrcount(const char *str, char ch);
char	*ft_strtrim(char const *s, char const *set);
int     ft_str_arr_len(char **arr);
#endif
