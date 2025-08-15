#include "minishell.h"
#include <stdio.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
extern char **environ;
void sigint_handler(int signo)
{
	(void)signo;
	write(1, "\n", 1);
}
int main(void)
{
	char *line;
	while (1)
	{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		line = readline("minishell$ ");
		if (!line) { write(1,"\n",1); break; }
		if (*line) add_history(line);
		t_cmd *cmds = parse_line(line);
		if (cmds)
		{
			extern int exec_commands(t_cmd *head);
			exec_commands(cmds);
			free_cmds(cmds);
		}
		free(line);
	}
	return 0;
}
