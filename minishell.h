/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 20:24:48 by meserghi          #+#    #+#             */
/*   Updated: 2024/03/21 18:06:53 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef enum e_token
{
	t_word,
	t_pipe,
	t_signle_q,
	t_double_q,
	t_red_in,
	t_red_out,
	t_app,
	t_heredoc,
	t_last,
}	t_token;

typedef struct s_list
{
	char *wrd;
	int	token;
	struct s_list *prv;
	struct s_list *next;
}	t_list;

// lib ...
size_t	ft_strlen(char *s);
char	*ft_strdup(char *s1);
char	*ft_strtrim(char *s1, char *set);
char	*ft_strjoin(char *s1, char *s2);
t_list	*new_node(char *data, int toker);
void	clear_lst(t_list **lst);
void	add_back(t_list **lst, t_list *new);
char	*ft_substr(char *s, size_t start, size_t len);
void	print_lst(t_list *h);

// utils ...
t_list	*parsing_part(char *line);
t_list	*tokening(char *input);
void	print_error(t_list **head, t_list *i);
int		is_red(int c);
int		is_q(int c);
int		check_token(char c);
#endif