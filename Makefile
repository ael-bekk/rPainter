NAME	= Editor

SRCS	= main.c \
			inc/get_next_line/get_next_line.c inc/get_next_line/get_next_line_utils.c \
			inc/libft/free.c inc/libft/ft_split.c inc/libft/ft_strlen.c inc/libft/ft_strnstr.c inc/libft/ft_putstr_fd.c \
			inc/libft/ft_itoa.c inc/libft/ft_calloc.c inc/libft/ft_bzero.c inc/libft/ft_strlcat.c inc/libft/ft_memset.c \
			lib/rectangle.c \
			events/KeyOnRelease.c events/KeyPress.c events/MouseMove.c events/MouseOnClick.c events/MouseOnRelease.c events/events.c \
			colors/get_colors.c

			
FLGS	= gcc 

RM		= rm -f

all:	$(NAME) $(SRCS)

$(NAME):  	$(SRCS)
	@$(FLGS) -lmlx -framework OpenGL -framework AppKit $(SRCS) -o $(NAME) -fsanitize=address -g
	@echo "\033[0;32mEditor is ready"

clean:
	@$(RM) $(NAME)

fclean:		clean

re:			fclean all

.PHONY:		all clean fclean re