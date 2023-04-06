SRCS 	= $(wildcard *.c)

OBJS 	= $(SRCS:.c=.o)

CC 		= gcc

MFLAGS 	=  ./mlx/libmlx.a

AFLAGS 	=  -Wall -Wextra -Werror -I./mlx 

RM 		= rm -rf

NAME 	= cub3d

MAKE 	= make -C 

all 	:$(NAME)

$(NAME)	: $(OBJS)
	$(CC) $(OBJS) $(MFLAGS) $(CFLAGS) -framework OpenGL -framework AppKit -o $(NAME)

fclean 	: clean
	$(RM) ./*.a
	$(RM) $(NAME)

clean 	:
	$(RM) ./*.o

re 		: fclean all

.PHONY 	: all fclean clean re