# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mservais <mservais@student.s19.be >        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/12 17:29:50 by mservais          #+#    #+#              #
#    Updated: 2021/12/23 17:53:11 by mservais         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_FILES		= ft_atoi.c \
				ft_bzero.c \
				ft_calloc.c \
				ft_int_len.c \
				ft_isalnum.c \
				ft_isalpha.c \
				ft_isascii.c \
				ft_isdigit.c \
				ft_isnegative.c \
				ft_isprint.c \
				ft_itoa.c \
				ft_long_len.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_memcpy.c \
				ft_memmove.c \
				ft_memset.c \
				ft_min.c \
				ft_pad_space.c \
				ft_pad_zero.c \
				ft_putchar_fd.c \
				ft_putchar.c \
				ft_putendl_fd.c \
				ft_putnbr_base.c \
				ft_putnbr_fd.c \
				ft_putnbr.c \
				ft_putstr_fd.c \
				ft_split.c \
				ft_strchr.c \
				ft_strdup.c \
				ft_striteri.c \
				ft_strjoin.c \
				ft_strlcat.c \
				ft_strlcpy.c \
				ft_strlen.c \
				ft_strmapi.c \
				ft_strncmp.c \
				ft_strnstr.c \
				ft_strrchr.c \
				ft_strtrim.c \
				ft_substr.c \
				ft_tolower.c \
				ft_toupper.c	

SRC_FILES_BONUS	= ${SRC_FILES} \
				ft_lstnew.c \
				ft_lstadd_front.c \
				ft_lstsize.c \
				ft_lstlast.c \
				ft_lstadd_back.c \
				ft_lstdelone.c \
				ft_lstclear.c \
				ft_lstiter.c \
				ft_lstmap.c

OBJ_FILES		= $(SRC_FILES:.c=.o)

OBJ_FILES_BONUS	= $(SRC_FILES_BONUS:.c=.o)

NAME			= libft.a

CC				= gcc

CFLAGS			= -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ_FILES)
	@ar -rcs $@ $^

bonus: $(OBJ_FILES_BONUS)
	@ar -rcs $(NAME) $^

%.o: %.c
	@$(CC) -c $(CFLAGS) -o $@ $<

clean:
	@rm -f $(OBJ_FILES) $(OBJ_FILES_BONUS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
