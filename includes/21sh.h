#ifndef TOSH_H
# define TOSH_H

# include <limits.h>
# include <termios.h>
# include "../libft/libft.h"

# define NEXT(elem) elem = elem->next

# define UP_ARROW 4283163
# define DOWN_ARROW 4348699
# define LEFT_ARROW 4479771
# define RIGHT_ARROW 4414235
# define HOME 4741915
# define END 4610843
# define MAJ_LEFT 74982532143899
# define MAJ_RIGTH 73883020516123
# define MAJ_UP 71683997260571
# define MAJ_DOWN 72783508888347
# define CTRL_MAJ_LEFT 74999712013083
# define CTRL_MAJ_RIGTH 73900200385307
# define CTRL_P 16
# define CTRL_R 18
# define DELETE 127
# define ENTER 10
# define EOT 4


typedef struct termios	t_termios;
typedef struct dirent	t_dirent;
typedef struct stat		t_stat;


typedef enum
{
	NONE,
	ENDOF,
	PIPE,
	CHEVB,
	DCHEVB,
	CHEVF,
	DCHEVF,
	AND,
	OR,
	SCL,
	NUM,
	WORD,
	TEXT,
	FD,
	FRED,
	BRED,
	LPAR,
	RPAR,
	QT,
	DQT,
	BQT,
	LBKT,
	RBKT,
	LBRC,
	RBRC
} e_token;

typedef enum
{
	BASIC_SHELL,
	ADVANCE_SHELL,
	BRACKET_ERROR,
	COMMAND_RUN,	
} e_state;

typedef struct		s_env
{
	char			*var_name;
	char			*var_content;
	char			*all;
	struct s_env	*next;
}					t_env;

typedef struct		s_cd
{
	char			is_P;
	char			is_L;
	char			is_oldpwd;
}					t_cd;

typedef	struct		s_lexer
{
	char			*line;
	int				red;
	char			string_operator;
}					t_lexer;

typedef	struct		s_token
{
	char			*value;
	e_token			type;
}					t_token;

typedef struct		s_tree
{
	//char			**cmd;
	int				from_fd;
	int				to_fd;
	t_token			*token;
	t_list			*tokens;
	struct s_tree	*left;
	struct s_tree	*right;
	e_token			parent_type;
}					t_tree;

typedef struct		s_pos
{
	int				x;
	int				y;
}					t_pos;

typedef struct		s_term_pos
{
	t_pos			max_window;
	t_pos			cursor;
	t_pos			first;
	t_pos			last;
}					t_term_pos;

typedef	struct		s_sh
{
	t_env			*env;
	t_lexer		*lexer;
	t_token		*current_token;

	char			*prompt;
	char			command[ARG_MAX];
	char			*total_command;
	char			*op;
	int				j;

	e_state			state;
	t_termios		old;
	t_term_pos		pos;

	char			**history;
	char			*history_mem;
	int				history_pos;

	int				ref_pos;
	char			*saved;
}					t_sh;

/* -------------- Builtins --------------- */

void				cd(char **av, t_env *env, t_sh *shell);
void				exit_command(char **av, t_sh *shell);

/* --------------- Others ---------------- */

int					ft_putcharint(int c);
int					get_current_pos_in_command(t_sh *shell);
void				copy_data(t_sh *shell, unsigned long c, int current);
void				clean_selected(t_sh *shell);
void				init_termcap(t_sh *shell, t_env *env);
void				signals_set(void);
void				errexit(char *content, char *reason);
void				shell_loop(t_sh *shell);
void				print_env(t_env *env);
void				left_arrow(t_sh *shell);
void				right_arrow(t_sh *shell);
void				maj_up_arrow(t_sh *shell);
void				maj_down_arrow(t_sh *shell);
void				maj_left_arrow(t_sh *shell);
void				maj_right_arrow(t_sh *shell);
void				sig_hand(int sig);
void				do_termcap(char *key);
void				search_mode(t_sh *shell);
void				save_history(t_sh *shell);
void				browse_history(t_sh *shell, unsigned long arrow);
void				add_line(t_sh *shell, char *toadd);
void				move_to(int x, int y);
void				past_data(t_sh *shell);
void				delete_char(char *command, int *j, t_sh *shell);
void				get_cursor(t_sh *shell);
void				print_prompt(e_state state, char *op);
void				treat_second_prompt(char *string, char **op, e_state *state);
void				go_core(char *command, t_env **env, t_sh *shell);
void				manage_redirection(t_tree **tree);
void				load_history(t_sh *shell, t_env *env);
void				set_env(char **av, t_env **env);
void				unset_env(char **av, t_env **env);
void				del_env(t_env *todel);
void				change_prompt(char *path, t_env *env, char **new_prompt, t_cd *opt);
void				clear_line(t_sh *shell);
void				get_tree_rec(t_tree **tree, char *left, char *right);
char				add_char(char *command, int *j, t_sh *shell, char c);
char				check_alpha(char *str);
char				go_to_c(char **str, char c);
char				cd_path_validity(char *path);
char				is_absolute(char **av, t_env *env);
char				is_binary(char *path);
char				del_all_env(t_env **list);
char				env_command(char **av, t_env *env);
char				check_new_open(char *str, char *op, int *j);
char				shell_loop2(char **command, char **last, e_state *state, char **op);
char				stop_binary(int sig);
char				check_new_open(char *str, char *op, int *j);
char				check_quot(char *str, char *op, int *i, int *j);
char				check_quot_brackets2(char *str, char *op, int i, int *j);
char				*clear_quot(char *str);
char				*check_quot_brackets(char *str, e_state *state);
char				*get_with_tilde(char *path, t_env *env);
char				*remove_useless_space(char *str);
char				*find_env(t_env *env, char *name);
char				*get_line(t_sh *shell, unsigned long buff, e_state *state, char *op);
char				**conv_env(t_env *env);
char				**trim_input(char *cmd);
char				**split_quot_cmd(char *cmd);
t_env				*new_env(char *str);
t_env				*get_env(char **env);
t_tree			*commands_line_rules(t_sh *sh);
int					is_string_op(int c);
t_token			*get_next_token(t_lexer *lexer);
t_tree			*redirection_rules(t_sh *sh, t_tree *left);
t_tree			*create_node(t_tree *left, t_token *token, t_list *tokens, t_tree *right);
void				eat(t_sh *sh, e_token token);
t_token			*text_rules(t_sh *sh);
void				init(t_sh *sh);
char				**list_to_tabstr(t_list *list);
void				operators(t_tree *node, int *fd_in, t_env **env, t_sh *shell);
char				exec_cmds(char **cmd, t_env **env, t_sh *shell);
char				run_binary(char *path, char **av, t_env *env);
char				get_path(char **cmd, t_env *env);

#endif