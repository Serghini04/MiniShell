/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 20:24:48 by meserghi          #+#    #+#             */
/*   Updated: 2024/05/18 18:47:53 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/errno.h>
# include <string.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <sys/types.h>
# include <dirent.h>
# define MAX_FD 1024

enum e_token
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
};

typedef struct s_list
{
	char			*wrd;
	int				token;
	int				is_sp;
	struct s_list	*prv;
	struct s_list	*next;
}	t_list;

typedef struct s_env
{
	char			*content;
	struct s_env	*next;
}	t_env;


typedef struct s_fd
{
	int		pid;
	int		fdin;
	int		flag;
	int		fdout;
	int		p_fdin;
	int		p_fdout;
	int		t_fd[2];
}	t_fd;

typedef struct s_mini
{
	char			**cmd;
	char			*cmd_path;
	char			**tb_env;
	t_env			*head;
	char			**env;
	int				fd_in;
	int				fd_out;
	t_fd			fd;
	struct s_mini	*next;
}	t_mini;

typedef struct s_free
{
	t_list	**head;
	t_mini	**mini;
	char	*res;
}	t_free;


//python3 -c 'print("ls | " * 1000 , end = "ls")' | pbcopy
/// <""|<""  && <"s"|  a

// lib ...
char	*ft_itoa(int n);
int		ft_isspace(int c);
t_mini	*create_node(void);
size_t	ft_strlen(char *s);
void	print_lst(t_list *h);
char	*ft_strdup(char *s1);
void	free_arr(char **res);
t_list	*last_lst(t_list *lst);
void	cln_node(t_mini *node);
void	free_node(t_list *node);
void	clear_lst(t_list **lst);
t_env	*ft_lstlast(t_env *lst);
void	clear_t_mini(t_mini **lst);
void	delete_node(t_list *node);
t_env	*ft_lstnew(char *content);
char	*ft_strchr(char *s, int c);
void	print_t_mini(t_mini *data);
int		ft_strcmp(char *s1, char *s2);
char	**ft_split(char const *s, char c);
char	*str_join(char *s1, char *s2);
char	*ft_strtrim(char *s1, char *set);
t_list	*new_node(char *data, int token);
void	add_back(t_list **lst, t_list *new);
void	ft_lstadd_back(t_env **lst, t_env *new);
char	*ft_strstr(char *haystack, char *needle);
void	add_back_t_mini(t_mini **lst, t_mini *new);
char	*ft_substr(char *s, size_t start, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

//parser
int		is_var(int c);
int		next_doll(char *str);
t_env	*save_env(t_env *env);
t_list	*tokening(char *input);
int		expanding(t_list **head);
t_mini	*parsing_part(char*line);
int		len_q(char *input, int c);
void	join_empty_wrd(t_list *i);
int		join_qoute(t_list **head);
int		join_qoute(t_list **head);
t_mini	*add_cmd_to_lst(t_list *i);
char	*my_getenv(char	*name_var);
void	close_if_open(int fd, int nb);
int		checking_syntax(t_list **head);
t_mini	*last_update_lst(t_list *head);
int		wildcards_part(t_list **head);
int		remove_dollar_sign(t_list **head);
void	open_file(t_list *i, t_mini *node);
void	delete_if_empty_wrd(t_list **head);
char	*split_wrd_and_join(char *s1, char *s2);
void	skip_or_delete(t_list	**head, t_list **i);
void	add_split_lst(char **cmd, t_list **head, t_list **root);
int		add_token_lst(t_list **head, char *input, int *i, int *s);
int		add_singl_double_q(t_list **head, char *input, int *i, int *pos);
char	*save_exit_status(char *res);
int		ft_check_if_builtin(t_mini *data, t_fd	*fd,t_env *env);
// builtins

//utils
int		is_q(int c);
int		len(char **cmd);
void	if_failing(void);
int		is_red(t_list *c);
int		len_var(char *str);
void	ft_env(char **env);
int		check_token(char c);
void	ft_pwd(void);
int		find_space(char *s);
int		print_dollar(char c);
void	ft_tolower(char	*str);
int		len_cmd(t_list *head);
void	ft_echo(t_mini	*data);
int		split_cmd(t_list **head);
void	ft_putstr_fd(char *s, int fd);
char	**creat_tabenv(t_env	*head);
char	*ft_strjoin(char *s1, char *s2);
char	*replace_dollar_sing(char *str);
int		is_expand(int token, int heredoc);
void	duping_fd(t_mini *data, t_fd *t_fd);
int		part_heredoc(t_list *i, t_mini *node);
void	print_error(t_list **head, t_list *i);
void	creat_myenv(t_env	**head, char **env);
void	main_process(t_mini	*data, t_env *env);
void	ft_export(char *name, t_env **head);
char	*find_path(char *cmd, char **env);
void	ft_execute_buitl_in(t_mini *data, t_env *env);
int		ft_is_built_in(t_mini *data);
void	change_holder_(t_mini *data, t_env *env);
void	ft_unset(char *str, t_env	**head);
void	ft_cd(t_mini *data, t_env *env);

#endif