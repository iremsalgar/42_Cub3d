SRCS			= main.c close_for_hook.c cub3d_utils.c \
				  dda.c empty_map.c get_map_game.c \
				  init_game.c move.c parse_file.c \
				  parse_last_color_sky_floor.c \
				  parse_map.c parse_utils.c \
				  parse.c raycast.c rotate.c \
				  valid_identifiers.c wall.c \


OBJS			= $(SRCS:.c=.o)

CC				= gcc
RM				= rm -f
CFLAGS			= -O3 -Wall -Wextra -Werror -I.
LIBS			= -Lmlx -lmlx -framework OpenGL -framework AppKit -lm
MLX				= libmlx.dylib

NAME			= cub3D

all:			$(NAME)

$(NAME):		$(MLX) $(OBJS)
				gcc ${CFLAGS} -o ${NAME} ${OBJS} ${LIBS}

$(MLX):
				@$(MAKE) -C mlx
				@mv mlx/$(MLX) .

clean:
				@$(MAKE) -C mlx clean
				$(RM) $(OBJS) $(BONUS_OBJS)

fclean:			clean
				$(RM) $(NAME) $(MLX)

re:				fclean $(NAME)

.PHONY:			all clean fclean re