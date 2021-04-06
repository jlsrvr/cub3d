NAME		=	cub3d

CC			=	gcc

IDIR		=	headers

LIBS		=	-L../libft/ -lft

OBJS		=	$(SRC:.c=.o)

SRC 		=	translator.c

RM			=	rm -f

FLAGS		=	-Wall -Wextra -Werror

.c.o:
	$(CC) $(FLAGS) -I$(IDIR) -c $< -o $(<:.c=.o)

all:		$(NAME)

$(NAME):	make_lib $(OBJS)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)

make_lib:
	@make libft.a -C ../libft

clean:
	$(RM) $(OBJS)
	@make clean -C ../libft

fclean: 	clean
	$(RM) $(NAME)
	@make fclean -C ../libft

re:			fclean all

.PHONY:	all clean fclean re
