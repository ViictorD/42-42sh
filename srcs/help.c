#include "tosh.h"

void		first_step(char *name)
{
	ft_putchar('\n');
	ft_putstr(C_RED);
	do_termcap("us");
	ft_putstr("Using of ");
	ft_putstr(name);
	ft_putendl(" command:");
	ft_putstr(C_RESET);
	ft_putstr(C_ITA);
	ft_putchar('\n');
}

static void	help_unsetenv(void)
{
	first_step("unsetenv");
	ft_putendl("\t- setenv name ...\n");
	ft_putendl("\tname : Environment variable name.\n");
	ft_putstr(C_RESET);
}

static void	help_exit(void)
{
	first_step("exit");
	ft_putendl("\t- exit [value]\n");
	ft_putendl("\tvalue : Return value for parent process.\n");
	ft_putstr(C_RESET);
}

static void	help_help(void)
{
	first_step("help");
	ft_putendl("\t- help cd.");
	ft_putendl("\t- help echo.");
	ft_putendl("\t- help env.");
	ft_putendl("\t- help hash.");
	ft_putendl("\t- help setenv.");
	ft_putendl("\t- help unsetenv.");
	ft_putendl("\t- help exit.\n");
	ft_putstr(C_RESET);
}

void		help_command(char **cmd)
{
	int		i;

	if (!*(cmd + 1))
		help_help();
	else
	{
		i = 0;
		while (cmd[++i])
		{
			if (!ft_strcmp(cmd[i], "exit"))
				help_exit();
			else if (!ft_strcmp(cmd[i], "cd"))
				help_cd();
			else if (!ft_strcmp(cmd[i], "setenv"))
				help_setenv();
			else if (!ft_strcmp(cmd[i], "unsetenv"))
				help_unsetenv();
			else if (!ft_strcmp(cmd[i], "env"))
				help_env();
			else if (!ft_strcmp(cmd[i], "echo"))
				help_echo();
			else if (!ft_strcmp(cmd[i], "hash"))
				help_hash();
		}
	}
}