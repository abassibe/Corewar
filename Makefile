# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abassibe <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/01 12:45:46 by abassibe          #+#    #+#              #
#    Updated: 2018/02/01 04:42:40 by abassibe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = asm

NAME2 = dasm

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
		check_and.c \
		check_ldi.c \
		check_sti.c \
		kingdom_hearts.c \
		print_header.c \
		check_print.c \
		print_ld_live_st_add.c \
		print_sub_zjmp_fork_lld.c \
		print_args.c \
		print_and.c \
		print_or.c \
		print_xor.c \
		print_ldi.c \
		print_lldi.c \
		print_sti.c \
		free.c

SRCS2 = dasm.c

OBJS = $(SRCS:.c=.o)

OBJS2 = $(SRCS2:.c=.o)

SRCPATH = ./srcs_asm/

SRCPATH2 = ./srcs_dasm/

FLAGS = -Wall -Wextra -Werror -fsanitize=address

all: $(NAME) $(NAME2)

$(NAME): $(OBJS)
	@make -C libft
	@gcc $(FLAGS) $(OBJS) libft/libft.a -o $(NAME)

$(NAME2): $(OBJS2)
	@gcc $(FLAGS) $(OBJS2) libft/libft.a -o $(NAME2)

%.o: $(SRCPATH)%.c
	@gcc $(FLAGS) -c $< -I includes

%.o: $(SRCPATH2)%.c
	@gcc $(FLAGS) -c $< -I includes

.PHONY: all clean fclean re

clean:
	@make -C libft clean
	@rm -rf $(OBJS) $(OBJS2)

fclean: clean
	@make -C libft fclean
	@rm -rf libft/libft.a $(NAME) $(NAME2)

re: fclean all
