# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abassibe <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/01 12:45:46 by abassibe          #+#    #+#              #
#    Updated: 2018/01/16 02:14:02 by abassibe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Corewar

SRCS =	asm.c \
		parsing.c \
		utils.c \
		pars_name_comment.c

OBJS = $(SRCS:.c=.o)

SRCPATH = ./srcs_asm/

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	@make -C libft
	@gcc $(FLAGS) $(OBJS) libft/libft.a -o $(NAME)

%.o: $(SRCPATH)%.c
	@gcc $(FLAGS) -c $< -I includes

.PHONY: all clean fclean re

clean:
	@make -C libft clean
	@rm -rf $(OBJS)

fclean: clean
	@make -C libft fclean
	@rm -rf libft/libft.a $(NAME)

re: fclean all
