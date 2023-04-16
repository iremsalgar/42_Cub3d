SRCS 	= $(wildcard ./src/*.c ./parse/*.c ./*.c ./utils/*.c)

OBJS 	= $(SRCS:.c=.o)

CC 		= gcc

MFLAGS 	=  ./mlx/libmlx.a

AFLAGS 	=  -Wall -Wextra -Werror -g -I./mlx

RM 		= rm -rf

NAME 	= cub3d

MAKE 	= make -C 

all 	:$(NAME)

$(NAME)	: $(OBJS)
	@($(CC) $(OBJS) $(MFLAGS) $(CFLAGS) -framework OpenGL -framework AppKit -o $(NAME))

fclean 	: clean
	@$(RM) ./*.a
	@$(RM) $(NAME)

clean 	:
	@$(RM) ./*.o ./src/*.o ./parse/*.o ./utils/*.o

re 		: fclean all

.PHONY 	: all fclean clean re