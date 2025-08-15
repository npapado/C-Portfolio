#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
typedef struct s_cmd {
	char **argv;
	char *infile;
	char *outfile;
	int  append;
	int  is_pipe;
	struct s_cmd *next;
} t_cmd;
char **split_path(void);
char *find_executable(char *cmd);
char *get_env_value(const char *name);
int	is_builtin(const char *cmd);
int	exec_builtin(t_cmd *cmd);
void	free_cmds(t_cmd *head);
t_cmd *parse_line(const char *line);
#endif
