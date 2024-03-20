# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/16 20:26:08 by meserghi          #+#    #+#              #
#    Updated: 2024/03/19 20:31:54 by meserghi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

lib = lib/ft_strdup.c lib/ft_strjoin.c lib/ft_strlen.c lib/ft_strtrim.c\
	lib/ft_substr.c lib/all_list.c

utils = parser_utils/parsing_part.c

FILE = ${lib} ${utils} minishell.c

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