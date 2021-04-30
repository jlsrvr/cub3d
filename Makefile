NAME		=	cub3d

CC			=	clang

IDIR		=	-I./headers -I./minilibx-linux

LIBS		=	-L./libft/ -L./minilibx-linux/ -lft -lmlx -lXext -lX11 -lm

OBJS		=	$(SRC:.c=.o)

SRC 		=	cub_main.c \
				cub_utils.c \
				engine/cub_engine.c \
				engine/engine_cleaners.c \
				engine/engine_utils.c \
				engine/engine_initialisers.c \
				engine/mouvement.c \
				engine/ray_rendering.c \
				engine/save.c \
				engine/screen_size.c \
				engine/sprites_ordering.c \
				engine/sprites_rendering.c \
				parser/colour_parser.c \
				parser/cub_parser.c \
				parser/map_parser.c \
				parser/parser_utils.c \
				parser/resolution_parser.c \
				parser/texture_parser.c \
				validator/cub_validator.c \
				validator/map_validator.c \
				validator/textures_validator.c \
				validator/validator_utils.c \

RM			=	rm -f

FLAGS		=	-Wall -Wextra -Werror

.c.o:
	$(CC) $(FLAGS) $(IDIR) -c $< -o $(<:.c=.o)

all:		$(NAME)

$(NAME):	make_lib make_mlx $(OBJS)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)
			@echo ".gitignore" > .gitignore
			@echo "minilibx-linux/test/mlx-test" >> .gitignore
			@echo $(NAME) >> .gitignore
			@find -type f -name "*.o" >> .gitignore
			@find -type f -name "*.a" >> .gitignore
			@sed -i -E 's/^\.\///' .gitignore

make_lib:
	@make libft.a -C ./libft/

make_mlx:
	@make -C ./minilibx-linux/

clean:
	$(RM) $(OBJS)
	@make clean -C ./libft/
	@make clean -C ./minilibx-linux/

fclean: 	clean
	$(RM) $(NAME)
	@make fclean -C ./libft/
	@make clean -C ./minilibx-linux/

re:			fclean all

.PHONY:	all clean fclean re
