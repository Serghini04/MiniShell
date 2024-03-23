# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/16 20:26:08 by meserghi          #+#    #+#              #
#    Updated: 2024/03/23 02:42:19 by meserghi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

lib = lib/ft_strdup.c lib/ft_strjoin.c lib/ft_strlen.c lib/ft_strtrim.c\
	lib/ft_substr.c lib/all_list.c lib/ft_split.c

parser = parser/parsing_part.c parser/tokening.c parser/last_update_lst.c

utils = utils/print_error.c utils/is_token.c

FILE = ${lib} ${parser} ${utils} minishell.c

FILE_OBJ = ${FILE:.c=.o}

FLAGS = -Wall -Wextra -Werror

NAME = minishell

all : ${NAME}

${NAME} : ${FILE_OBJ}
	cc ${FLAGS} -lreadline ${FILE_OBJ} -o ${NAME}

%.o : %.c minishell.h
	cc ${FLAGS} -c $< -o $@

clean :
	rm -f ${FILE_OBJ}

fclean : clean
	rm -f ${NAME}

re : fclean all