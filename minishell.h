/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 20:24:48 by meserghi          #+#    #+#             */
/*   Updated: 2024/03/26 01:03:54 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

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
	char			*wrd;
	int				token;
	int				is_sp;
	struct s_list	*prv;
	struct s_list	*next;
}	t_list;

typedef struct s_mini
{
	char			**cmd;
	int				fd_in;
	int				fd_out;
	struct s_mini	*next;
}	t_mini;

// lib ...
t_list	*new_node(char *data, int token);
void	add_back(t_list **lst, t_list *new);
void	free_node(t_list *node);
void	clear_lst(t_list **lst);
t_list	*last_lst(t_list *lst);
void	print_lst(t_list *h);
t_mini	*create_node(void);
void	add_back_t_mini(t_mini **lst, t_mini *new);
void	cln_node(t_mini *node);
void	clear_t_mini(t_mini **lst);
void	free_arr(char **res);
void	print_t_mini(t_mini *data);
char	**ft_split(char const *s, char c);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strdup(char *s1);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(char *s);
char	*ft_strtrim(char *s1, char *set);
char	*ft_substr(char *s, size_t start, size_t len);

//parser
void	join_empty_wrd(t_list *i);
int		join_qoute(t_list **head);
int		checking_syntax(t_list **head);
void	open_file(t_list *i, t_mini *node);
t_mini	*add_cmd_to_lst(t_list *i);
t_mini	*last_update_lst(t_list *head);
void	delete_if_to_wrd_empty(t_list **head);
int		join_qoute(t_list **head);
void	add_split_lst(char **cmd, t_list **head, t_list **root);
t_mini	*parsing_part(char*line);
int		len_q(char *input, int c);
int		add_singl_double_q(t_list **head, char *input, int *i, int *pos);
int		add_token_lst(t_list **head, char *input, int *i, int *s);
t_list	*tokening(char *input);

//utils
int		is_red(t_list *c);
int		is_q(int c);
int		check_token(char c);
int		find_space(char *s);
int		len_cmd(t_list *head);
int		len(char **cmd);
int		part_heredoc(t_list *i, t_mini *node);
void	print_error(t_list **head, t_list *i);
int		split_cmd(t_list **head);
#endif