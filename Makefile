# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/16 20:26:08 by meserghi          #+#    #+#              #
#    Updated: 2024/06/02 18:13:18 by hidriouc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

lib = lib/ft_strdup.c lib/str_join.c lib/ft_strlen.c lib/ft_strtrim.c lib/ft_atoi.c\
	lib/ft_substr.c lib/all_list.c lib/ft_split.c lib/all_new_list.c lib/ft_strcmp.c\
	lib/free_arr.c lib/ft_isspace.c lib/ft_strchr.c lib/ft_strnstr.c lib/ft_putstr_fd.c\
	lib/ft_lstadd_back.c lib/ft_lstnew.c lib/ft_lstlast.c lib/ft_strncmp.c lib/ft_itoa.c\
	lib/ft_lstsize.c lib/ft_strjoin.c lib/ft_strstr.c lib/my_split.c lib/ft_isdigit.c\
	lib/clear.c

parser = parser/parsing_part.c parser/tokening.c parser/last_update_lst.c\
	parser/checking_syntax.c parser/join_qoute.c parser/join_qoute_part_two.c\
	parser/expanding.c parser/expanding_part2.c parser/my_getenv.c

utils = utils/print_error.c utils/is_token.c utils/parsing_utils.c utils/split_cmd.c\
		utils/execution.c utils/expanding_utils.c utils/duping_fd.c \
		utils/creat_myenv.c utils/creat_tabenv.c  utils/statut.c \
		utils/ft_creat_pross.c

buliltins = builtins/ft_cd.c builtins/ft_env.c  builtins/ft_echo.c builtins/ft_exit.c\
		builtins/ft_unset.c  builtins/ft_export.c builtins/manag_builtins.c builtins/ft_pwd.c

wildcard = wildcard/wildcard.c wildcard/get_name_var.c wildcard/get_dir.c\
		   wildcard/free_t_env.c wildcard/delete_not_need.c

GREEN = \033[1;32m
RED = \033[1;31m
BLUE = \033[1;34m
YELL = \033[0;33m
STOP_C = \033[0m

FILE = ${lib} ${parser} ${utils}  ${wildcard} ${buliltins} minishell.c

FILE_OBJ = ${FILE:.c=.o}

FLAGS = -Wall -Wextra -Werror #-fsanitize=address -g

NAME = minishell

READLINE_L = $(shell brew --prefix readline)/lib

READLINE_I = $(shell brew --prefix readline)/include

all : ${NAME}
	@echo "${GREEN}minishell has been built ...${STOP_C}"

%.o : %.c minishell.h
	@cc ${FLAGS} -I ${READLINE_I} -c  $< -o $@
	@echo "${BLUE}$@ has been built${NC}"

${NAME} : ${FILE_OBJ}
	cc ${FLAGS} ${FILE_OBJ} -o ${NAME} -L ${READLINE_L} -lreadline

clean :
	@rm -f ${FILE_OBJ}
	@echo "${RED}Cleaned object files${STOP_C}"

fclean : clean
	@rm -f ${NAME}
	@echo "${RED}Fully cleaned${STOP_C}"

re : fclean all
	
