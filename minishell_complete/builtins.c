#include "minishell.h"
#include <string.h>
#include <stdio.h>
int is_builtin(const char *cmd)
{
	if (!cmd) return 0;
	return (strcmp(cmd, "echo")==0 || strcmp(cmd,"cd")==0 || strcmp(cmd,"pwd")==0
		|| strcmp(cmd,"export")==0 || strcmp(cmd,"unset")==0 || strcmp(cmd,"env")==0
		|| strcmp(cmd,"exit")==0);
}
int exec_builtin(t_cmd *cmd)
{
	if (!cmd || !cmd->argv || !cmd->argv[0]) return -1;
	char **a = cmd->argv;
	if (strcmp(a[0],"echo")==0)
	{
		int nflag = (a[1] && strcmp(a[1],"-n")==0);
		int i = nflag ? 2 : 1;
		for (; a[i]; ++i) { if (i> (nflag?2:1)) write(1," ",1); write(1,a[i],strlen(a[i])); }
		if (!nflag) write(1,"\n",1);
		return 0;
	}
	if (strcmp(a[0],"pwd")==0)
	{
		char cwd[1024];
		if (getcwd(cwd, sizeof(cwd))) { write(1,cwd,strlen(cwd)); write(1,"\n",1); }
		return 0;
	}
	if (strcmp(a[0],"cd")==0)
	{
		char *p = a[1] ? a[1] : getenv("HOME");
		if (!p) p = ".";
		if (chdir(p) != 0) { perror("cd"); }
		return 0;
	}
	if (strcmp(a[0],"env")==0)
	{
		extern char **environ;
		for (int i=0; environ[i]; ++i) { write(1,environ[i],strlen(environ[i])); write(1,"\n",1); }
		return 0;
	}
	if (strcmp(a[0],"exit")==0)
	{
		int code = 0;
		if (a[1]) code = atoi(a[1]);
		exit(code);
	}
	if (strcmp(a[0],"export")==0)
	{
		if (!a[1]) {
			extern char **environ;
			for (int i=0; environ[i]; ++i) { write(1,environ[i],strlen(environ[i])); write(1,"\n",1); }
			return 0;
		}
		char *eq = strchr(a[1],'=');
		if (eq) {
			*eq = '\0';
			setenv(a[1], eq+1, 1);
			*eq = '=';
		} else setenv(a[1], "", 1);
		return 0;
	}
	if (strcmp(a[0],"unset")==0)
	{
		if (a[1]) unsetenv(a[1]);
		return 0;
	}
	return -1;
}
