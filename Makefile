# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abassibe <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/01 12:45:46 by abassibe          #+#    #+#              #
#    Updated: 2018/02/06 03:07:26 by abassibe         ###   ########.fr        #
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

SRCS2 = dasm.c \
		utils.c \
		get_header.c \
		get_args.c \
		get_ld_st.c \
		get_add_sub.c \
		get_and_or_xor.c \
		get_live_zjmp_fork_lfork_aff.c \
		get_ldi_lldi.c \
		get_sti.c \
		get_lld.c

OBJS = $(SRCS:.c=.o)

OBJS2 = $(SRCS2:.c=.o)

SRCPATH = ./srcs_asm/

SRCPATH2 = ./srcs_dasm/

FLAGS = -Wall -Wextra -Werror

DIR_OBJ1 = objs/

DIR_OBJ2 = objs2/

all: $(NAME) $(NAME2)

$(NAME): $(addprefix objs/, $(OBJS))
	@make -C libft
	@gcc $(FLAGS) $^ libft/libft.a -o $(NAME)

$(NAME2): $(addprefix objs2/, $(OBJS2))
	@gcc $(FLAGS) $^ libft/libft.a -o $(NAME2)

$(DIR_OBJ1)%.o: $(SRCPATH)%.c
	@mkdir -p objs
	@gcc $(FLAGS) -c $< -o $@ -I includes

$(DIR_OBJ2)%.o: $(SRCPATH2)%.c
	@mkdir -p objs2
	@gcc $(FLAGS) -c $< -o $@ -I includes

.PHONY: all clean fclean re

clean:
	@make -C libft clean
	@rm -rf objs objs2

fclean: clean
	@make -C libft fclean
	@rm -rf libft/libft.a $(NAME) $(NAME2)

re: fclean
	@make
