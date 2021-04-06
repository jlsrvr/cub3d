# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jrivoire <jrivoire@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/15 15:24:55 by jrivoire          #+#    #+#              #
#    Updated: 2021/04/06 17:46:04 by jrivoire         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	libft.a

CC				=	gcc

OBJS			=	$(SRCS:.c=.o)

IDIR			=	headers/

SRCS			= 	char/ft_isalnum.c \
					char/ft_isalpha.c \
					char/ft_isascii.c \
					char/ft_isdigit.c \
					char/ft_isprint.c \
					char/ft_isspace.c \
					char/ft_tolower.c \
					char/ft_toupper.c \
					display/ft_putchar_fd.c \
					display/ft_putendl_fd.c \
					display/ft_putnbr_fd.c \
					display/ft_putstr_fd.c \
					file/get_next_line.c \
					integer/ft_itoa.c \
					integer/ft_uitoa_base.c \
					list/ft_lstadd_back.c \
					list/ft_lstadd_front.c \
					list/ft_lstclear.c \
					list/ft_lstdelone.c \
					list/ft_lstiter.c \
					list/ft_lstlast.c \
					list/ft_lstmap.c \
					list/ft_lstnew.c \
					list/ft_lstsize.c \
					memory/ft_bzero.c \
					memory/ft_calloc.c \
					memory/ft_memccpy.c \
					memory/ft_memchr.c \
					memory/ft_memcmp.c \
					memory/ft_memcpy.c \
					memory/ft_memmove.c \
					memory/ft_memset.c \
					string/ft_atoi.c \
					string/ft_split.c \
					string/ft_strchr.c \
					string/ft_strdup.c \
					string/ft_strjoin.c \
					string/ft_strlcat.c \
					string/ft_strlcpy.c \
					string/ft_strlen.c \
					string/ft_strmapi.c \
					string/ft_strncmp.c \
					string/ft_strnstr.c \
					string/ft_strrchr.c \
					string/ft_strtrim.c \
					string/ft_substr.c

RM				=	rm -f

FLAGS			=	-Wall -Wextra -Werror

.c.o:
	$(CC) $(FLAGS) -I$(IDIR) -c $< -o $(<:.c=.o)

$(NAME):	$(OBJS)
	ar rcs $(NAME) $(OBJS)

all:		$(NAME)

clean:
	$(RM) $(OBJS)

fclean: 	clean
	$(RM) $(NAME)

re:			fclean all

.PHONY:	all clean fclean re
