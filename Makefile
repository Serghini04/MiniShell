# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/16 20:26:08 by meserghi          #+#    #+#              #
#    Updated: 2024/04/24 20:58:27 by meserghi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# will be done.
# // expanding...
# //==> handel $?.
# //==> fix leaks.
# //==> check if all good.

# // protection function...
# // split with '\t'/./
# // done.

lib = lib/ft_strdup.c lib/str_join.c lib/ft_strlen.c lib/ft_strtrim.c\
	lib/ft_substr.c lib/all_list.c lib/ft_split.c lib/all_new_list.c lib/ft_strcmp.c\
	lib/free_arr.c lib/ft_isspace.c lib/ft_strchr.c lib/ft_strnstr.c lib/ft_putstr_fd.c

parser = parser/parsing_part.c parser/tokening.c parser/last_update_lst.c\
	parser/checking_syntax.c parser/join_qoute.c parser/join_qoute_part_two.c\
	parser/expanding.c

utils = utils/print_error.c utils/is_token.c utils/parsing_utils.c utils/split_cmd.c\
		utils/execution.c

GREEN = \033[1;32m
RED = \033[1;31m
BLUE = \033[1;34m
YELL = \033[0;33m
STOP_C = \033[0m

FILE = ${lib} ${parser} ${utils} minishell.c

FILE_OBJ = ${FILE:.c=.o}

FLAGS = -Wall -Wextra -Werror -fsanitize=address -g

NAME = minishell

all : ${NAME}
	@echo "${GREEN}minishell has been built ...${STOP_C}"

${NAME} : ${FILE_OBJ}
	cc ${FLAGS} ${FILE_OBJ} -lreadline -o ${NAME}

%.o : %.c minishell.h
	@cc ${FLAGS} -c $< -o $@
	@echo "${BLUE}$@ has been built${NC}"

clean :
	rm -f ${FILE_OBJ}
	@echo "${RED}Cleaned object files${STOP_C}"

fclean : clean
	rm -f ${NAME}
	@echo "${RED}Fully cleaned${STOP_C}"

re : fclean all


# Replace 'mehdi' with your branch name before executing.
push : fclean
	@git add .
	@read -p "Enter commit message: " msg_push; \
	git commit -m "$$msg_push";
	@git push origin mehdi
	@echo "${RED}Changes have been pushed${STOP_C}"
