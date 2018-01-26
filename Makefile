# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abassibe <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/01 12:45:46 by abassibe          #+#    #+#              #
#    Updated: 2018/01/26 04:58:25 by abassibe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = asm

SRCS =	asm.c \
		parsing.c \
		utils.c \
		pars_name_comment.c \
		pars_core.c \
		get_op.c \
		get_op2.c \
		get_op3.c \
		checker.c \
		checker2.c \
		kingdom_hearts.c \
		print_header.c \
		check_print.c \
		print_ld_live_st_add.c \
		print_sub.c \
		print_args.c

OBJS = $(SRCS:.c=.o)

SRCPATH = ./srcs_asm/

FLAGS = -Wall -Wextra -Werror -fsanitize=address

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
