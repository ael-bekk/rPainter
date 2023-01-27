NAME	= Editor

SRCS	= main.c \
			lib/rectangle.c \
			events/Randring.c events/KeyOnRelease.c events/KeyPress.c events/MouseMove.c events/MouseOnClick.c events/MouseOnRelease.c events/events.c \
			colors/get_colors.c \
			tools/img_list.c tools/BrushAndBucket.c \
			src/CanvasClick.c

			
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