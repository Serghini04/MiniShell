/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 20:24:48 by meserghi          #+#    #+#             */
/*   Updated: 2024/04/09 23:32:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
#include <sys/errno.h>
# include <string.h>
#include <sys/wait.h>
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
	char			*cmd_path;
	int				flag;
	char			**env;
	int				fd_in;
	int				fd_out;
	struct s_mini	*next;
}	t_mini;

typedef struct	s_free
{
	t_list	**head;
	t_mini	**mini;
	char	*res;
}	t_free;


// lib ...
t_list	*new_node(char *data, int token);
void	add_back(t_list **lst, t_list *new);
void	free_node(t_list *node);
void	clear_lst(t_list **lst);
t_list	*last_lst(t_list *lst);
void	print_lst(t_list *h);
int		ft_isspace(int c);
t_mini	*create_node(void);
void	add_back_t_mini(t_mini **lst, t_mini *new);
void	cln_node(t_mini *node);
void	clear_t_mini(t_mini **lst);
void	free_arr(char **res);
char	*ft_strchr(const char *s, int c);
void	print_t_mini(t_mini *data);
char	**ft_split(char const *s, char c);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strdup(char *s1);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(char *s);
char	*ft_strtrim(char *s1, char *set);
char	*ft_substr(char *s, size_t start, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

//parser
t_list	*tokening(char *input);
char	*rm_all_split(char *s1);
t_mini	*parsing_part(char*line);
void	join_empty_wrd(t_list *i);
int		join_qoute(t_list **head);
int		join_qoute(t_list **head);
int		len_q(char *input, int c);
t_mini	*add_cmd_to_lst(t_list *i);
void	close_if_open(int fd, int nb);
int		remove_dollar_sign(t_list **head);
int		checking_syntax(t_list **head);
t_mini	*last_update_lst(t_list *head);
void	open_file(t_list *i, t_mini *node);
void	delete_if_empty_wrd(t_list **head);
char	*split_wrd_and_join(char *s1, char *s2);
void	skip_or_delete(t_list	**head, t_list **i);
void	add_split_lst(char **cmd, t_list **head, t_list **root);
int		add_token_lst(t_list **head, char *input, int *i, int *s);
int		add_singl_double_q(t_list **head, char *input, int *i, int *pos);

//utils
int		is_red(t_list *c);
int		is_q(int c);
int		check_token(char c);
int		find_space(char *s);
int		len_cmd(t_list *head);
int		len(char **cmd);
void	ft_putstr_fd(char *s, int fd);
int		part_heredoc(t_list *i, t_mini *node);
void	print_error(t_list **head, t_list *i);
int		split_cmd(t_list **head);
void	main_process(t_mini	**data, char **env);
void	duping_fd(t_mini *data, int *t_fd);

#endif