#include <sys/types.h>
#include <signal.h>
#include "21sh.h"

/*static void	child2(t_tree *node, char ***cmds)
{
	if (node->from_fd != -1 && node->to_fd != -1)
		dup2(node->from_fd, node->to_fd);
	else if (node->to_fd != -1)
		dup2(1, node->to_fd);
	*cmds = node->cmds;
}*/

void	child(t_tree *node, t_sh *shell, int *fd)
{
	char	**envi;

	if (node->token && node->parent->token->type == DCHEVB)
		manage_dchevb(node);
	else if (node->parent && node->parent->token->type == CHEVB)
	{
		envi = conv_env(shell->env);
		manage_chevb(node, shell->FD_IN, envi);
		if (envi)
			ft_strdelpp(&envi);
	}
	else if (node->parent && node->parent->token->type == DCHEVF)
		manage_dchevf(node, shell->FD_OUT);
	else if (node->parent && node->parent->token->type == CHEVF)
		manage_chevf(node, shell->FD_OUT);
	else if (node->parent && node->parent->token->type == FRED)
		manage_fred(node, shell->FD_OUT);
	if (shell->FD_PIPE != -1)
		run_with_pipe(shell, fd);
	//else
	//	child2(node, &cmds);
}

char		stop_binary(int sig)
{
	pid_t	child;

	child = child_pid();
	if (child == 0)
		exit(EXIT_SUCCESS);
	if (child != -1 && sig == SIGINT)
	{
		kill(child, sig);
		child = -1;
		ft_putchar('\n');
		return (1);
	}
	return (0);
}

void		run_with_pipe(t_sh *shell, int *fd)
{
	//if (node->from_fd != -1 && node->to_fd != -1)
	//	dup2(node->from_fd, node->to_fd);		
	//	dup2(fd[1], node->from_fd);
	close(fd[0]);	
	if (shell->FD_PIPE)
		dup2(shell->FD_PIPE, 0);
	if (!shell->right_side)
		dup2(fd[1], 1);
	else if (shell->FD_OUT != -1)
		dup2(shell->FD_OUT, 1);
}

int			open_file(t_tree *node)
{
	int	ret;

	ret = 0;
	if (node->token && node->token->type == CHEVB)
		return (open_chevb(node));
	else if (node->token && (node->token->type == CHEVF || \
		(node->token->type == FRED && ft_strcmp(node->right->cmds[0], "-"))))
		return (open_chevf(node));
	else if (node->token && node->token->type == DCHEVF)
		return (open_dchevf(node));
	else
		return (ret);
}

int			get_fd(t_sh *shell, int *fd)
{
	int	ret;

	ret = 0;
	if (shell->FD_PIPE != -1)
		if ((ret = pipe(fd)) == -1)
			ft_putstr("pipe failure !\n");
	return (ret);
}