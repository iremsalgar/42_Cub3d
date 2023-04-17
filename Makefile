
SRCS 	=	./parse/all_check_and_read_map.c \
			./parse/check.c  ./parse/check2.c\
			./parse/check3.c  ./parse/check4.c\
			./parse/check5.c  ./parse/clear.c\
			./parse/ft_find.c ./parse/get_next_line.c\
			./parse/get_next_line_utils.c \
			./src/close_for_hook.c ./src/direction.c\
			./src/for_image.c ./src/move.c\
			./src/player_pos.c ./src/ray_utills.c\
			./src/raycast.c ./src/texture.c\
			./utils/cub3d_utils.c ./utils/cub3d_utils2.c\
			./utils/cub3d_utils3.c ./main.c\


OBJS 	= $(SRCS:.c=.o)

CC 		= gcc

MFLAGS 	=  ./mlx/libmlx.a

AFLAGS 	=  -Wall -Wextra -Werror -I./mlx

RM 		= rm -rf

NAME 	= cub3d

MAKE 	= make -C 


all 	:$(NAME) 

mlx	:
	make -C ./mlx

$(NAME)	: mlx $(OBJS)
	@$(CC) $(OBJS) $(MFLAGS) $(CFLAGS) -framework OpenGL -framework AppKit -o $(NAME)

fclean 	: clean
	@$(RM) ./*.a
	@$(RM) $(NAME)

clean 	:
	@$(RM) ./*.o ./src/*.o ./parse/*.o ./utils/*.o ./mlx/*.o ./mlx/*.a

re 		: fclean all

.PHONY 	: all fclean clean re mlx