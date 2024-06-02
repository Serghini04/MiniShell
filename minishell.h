/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 20:24:48 by meserghi          #+#    #+#             */
/*   Updated: 2024/06/02 18:24:04 by hidriouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/errno.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <termios.h>
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
	int				exp_wildcard;
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
	pid_t	*pid;
	int		fdin;
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
	int				status;
	struct s_mini	*next;
}	t_mini;

typedef struct s_free
{
	t_list	**head;
	t_mini	**mini;
	char	*res;
}	t_free;

// lib ...
char		*ft_itoa(int n);
void		free_node(t_list *node);
int			ft_isdigit(char *str);
int			ft_atoi(const char *str);
int			ft_lstsize(t_mini	*lst);
void		clear_lst(t_list **lst);
t_env		*ft_lstlast(t_env *lst);
char		*ft_strdup(char *s1);
t_list		*last_lst(t_list *lst);
void		print_lst(t_list *h);
void		appell_clear(t_env **haed);
int			ft_isspace(int c);
t_mini		*create_node(void);
size_t		ft_strlen(char *s);
void		print_lst(t_list *h);
char		*ft_strdup(char *s1);
void		free_arr(char **res);
t_list		*last_lst(t_list *lst);
void		cln_node(t_mini *node);
void		free_node(t_list *node);
void		clear_lst(t_list **lst);
t_env		*ft_lstlast(t_env *lst);
void		clear_t_mini(t_mini **lst);
void		delete_node(t_list *node);
t_env		*ft_lstnew(char *content);
char		*ft_strchr(char *s, int c);
char		*ft_strjoin(char *s1, char *s2);
void		print_t_mini(t_mini *data);
int			ft_strcmp(char *s1, char *s2);
char		**my_split(char const *s);
char		*str_join(char *s1, char *s2);
char		*ft_strtrim(char *s1, char *set);
t_list		*new_node(char *data, int token);
char		**ft_split(char const *s, char c);
void		add_back(t_list **lst, t_list *new);
void		ft_lstadd_back(t_env **lst, t_env *new);
char		*ft_strstr(char *haystack, char *needle);
void		add_back_t_mini(t_mini **lst, t_mini *new);
char		*ft_substr(char *s, size_t start, size_t len);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);

//wildca	rd
void		ft_clearlist_env(t_env **head);
int			wildcards_part(t_list **head);
char		*replace_wildcards(char *line);
int			need_to_exp_wildards(char *str);
char		*get_name_part2(char *line, int *i);
int			check_node(t_list *h, int *need_split);
char		*get_name_wildcard(char *line, int i );
int			reverse_cmp(char *s1, char *s2, int len);
void		free_t_env(t_env **env, int free_content);
t_env		*delete_not_need(char *name_var, t_env **head);
t_env		*save_find_dir(char	*name_wildcard, t_env **head);
t_env		*delete_not_need_part2(char *name_var, t_env **head);
t_env		*delete_not_need_middle(char *name_var, t_env **head);
t_mini		*last_update_node(int *fd, t_mini **node, int *index);

//parser	
int			is_var(int c);
int			next_doll(char *str);
t_env		*save_env(t_env *env);
t_list		*tokening(char *input);
int			expanding(t_list **head);
t_mini		*parsing_part(char*line);
int			len_q(char *input, int c);
void		join_empty_wrd(t_list *i);
int			join_qoute(t_list **head);
int			join_qoute(t_list **head);
t_mini		*add_cmd_to_lst(t_list *i, int *hand_signal);
char		*my_getenv(char	*name_var);
void		close_if_open(int fd, int nb);
int			checking_syntax(t_list **head);
t_mini		*last_update_lst(t_list *head);
int			remove_dollar_sign(t_list **head);
void		ft_exit(t_mini *data, char *status, int flag);
void		open_file(t_list *i, t_mini *node);
void		delete_if_empty_wrd(t_list **head);
char		*split_wrd_and_join(char *s1, char *s2);
void		skip_or_delete(t_list	**head, t_list **i);
void		add_split_lst(char **cmd, t_list **head, t_list **root);
int			add_token_lst(t_list **head, char *input, int *i, int *s);
int			add_singl_double_q(t_list **head, char *input, int *i, int *pos);
char		*save_exit_status(char *res);
int			ft_check_if_builtin(t_mini *data, t_fd	*fd, t_env **env);

//utils
void		fn(int c);
int			is_q(int c);
int			len(char **cmd);
void		if_failing(void);
int			is_red(t_list *c);
int			len_var(char *str);
void		ft_env(char **env);
void		handl_sig(int sig);
int			check_token(char c);
void		ft_pwd(char **env);
int			find_space(char *s);
int			print_dollar(char c);
char		*ft_tolower(char	*str);
int			len_cmd(t_list *head);
void		ft_echo(t_mini	*data);
void		red_fd_parent(t_fd *fd);
int			is_dir_or_file(char *name);
int			split_cmd(t_list **head);
void		ft_putstr_fd(char *s, int fd);
char		**creat_tabenv(t_env	*head);
char		*ft_strjoin(char *s1, char *s2);
char		*replace_dollar_sing(char *str);
int			is_expand(int token, int heredoc);
void		check_malloc_sac(char **all_path);
int			duping_fd(t_mini *data, t_fd *t_fd);
int			part_heredoc(t_list *i, t_mini *node);
void		print_error(t_list **head, t_list *i);
void		creat_myenv(t_env	**head, char **env);
int			split_cmd(t_list **head);
void		ft_export(char *name, t_env **head);
char		*find_path(char *cmd, char **env);
void		ft_execute_buitl_in(t_mini *data, t_env **env, int flag);
void		return_status(int *tb, int nb_pids);
int			ft_is_built_in(t_mini *data);
void		ft_unset(char *str, t_env	**head);
long long	advance_atoi(const char *str);
int			ft_cd(t_mini *data, t_env *env);
int			ft_is_built_in(t_mini *data);
int			ft_check_if_builtin(t_mini *data, t_fd *fd, t_env **env);
void		ft_creat_pross(t_mini *ta, t_fd *fd, t_env **ev, struct termios *s);
int			ft_handel_prossid(t_mini *data, t_fd *fd, int i, t_env **lin_env);
void		main_process(t_mini	*data, t_env **lin_env, struct termios *term);

#endif
