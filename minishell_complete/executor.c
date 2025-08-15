#include "minishell.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
extern char **environ;
static int run_simple(t_cmd *cmd)
{
	if (!cmd || !cmd->argv || !cmd->argv[0]) return 0;
	if (is_builtin(cmd->argv[0]))
	{
		return exec_builtin(cmd);
	}
	char *exe = find_executable(cmd->argv[0]);
	if (!exe) { fprintf(stderr, "minishell: %s: command not found\n", cmd->argv[0]); return 127; }
	pid_t pid = fork();
	if (pid == 0)
	{
		if (cmd->infile) {
			int fd = open(cmd->infile, O_RDONLY);
			if (fd<0) { perror("open"); exit(1); }
			dup2(fd, 0); close(fd);
		}
		if (cmd->outfile) {
			int flags = O_CREAT | O_WRONLY | (cmd->append ? O_APPEND : O_TRUNC);
			int fd = open(cmd->outfile, flags, 0644);
			if (fd<0) { perror("open"); exit(1); }
			dup2(fd, 1); close(fd);
		}
		execve(exe, cmd->argv, environ);
		perror("execve");
		exit(126);
	}
	else if (pid > 0)
	{
		int status;
		waitpid(pid, &status, 0);
		free(exe);
		if (WIFEXITED(status)) return WEXITSTATUS(status);
		return 1;
	}
	free(exe);
	return 1;
}
int exec_commands(t_cmd *head)
{
	t_cmd *cur = head;
	int last_status = 0;
	int pipefd[2];
	while (cur)
	{
		if (cur->is_pipe)
		{
			if (pipe(pipefd) < 0) { perror("pipe"); return 1; }
			pid_t pid = fork();
			if (pid == 0)
			{
				dup2(pipefd[1], 1);
				close(pipefd[0]); close(pipefd[1]);
				if (cur->infile) {
					int fd = open(cur->infile, O_RDONLY);
					if (fd<0) { perror("open"); exit(1); }
					dup2(fd,0); close(fd);
				}
				if (is_builtin(cur->argv[0])) exit(exec_builtin(cur));
				char *exe = find_executable(cur->argv[0]);
				if (!exe) { fprintf(stderr, "minishell: %s: command not found\n", cur->argv[0]); exit(127); }
				execve(exe, cur->argv, environ);
				perror("execve"); exit(126);
			}
			else
			{
				close(pipefd[1]);
				// set next's infile to /dev/fd/N
				char path[64]; sprintf(path, "/dev/fd/%d", pipefd[0]);
				cur->next->infile = strdup(path);
				close(pipefd[0]);
			}
		}
		else
		{
			last_status = run_simple(cur);
		}
		cur = cur->next;
	}
	return last_status;
}
