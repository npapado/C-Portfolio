#include "minishell.h"
#include <string.h>
#include <stdio.h>
char *get_env_value(const char *name)
{
	extern char **environ;
	size_t n = strlen(name);
	for (int i = 0; environ[i]; ++i)
	{
		if (strncmp(environ[i], name, n) == 0 && environ[i][n] == '=')
			return environ[i] + n + 1;
	}
	return NULL;
}
static char *join_path(const char *a, const char *b)
{
	size_t la = strlen(a), lb = strlen(b);
	char *p = malloc(la + lb + 2);
	if (!p) return NULL;
	strcpy(p, a);
	p[la] = '/';
	strcpy(p + la + 1, b);
	return p;
}
char **split_path(void)
{
	char *p = get_env_value("PATH");
	if (!p) return NULL;
	char *tmp = strdup(p);
	if (!tmp) return NULL;
	size_t count = 1;
	for (char *t = tmp; *t; ++t) if (*t == ':') count++;
	char **arr = malloc((count+1)*sizeof(char*));
	if (!arr) { free(tmp); return NULL; }
	size_t idx = 0;
	char *tok = strtok(tmp, ":");
	while (tok)
	{
		arr[idx++] = strdup(tok);
		tok = strtok(NULL, ":");
	}
	arr[idx] = NULL;
	free(tmp);
	return arr;
}
char *find_executable(char *cmd)
{
	if (!cmd) return NULL;
	if (strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0) return strdup(cmd);
		return NULL;
	}
	char **paths = split_path();
	if (!paths) return NULL;
	char *res = NULL;
	for (int i = 0; paths[i]; ++i)
	{
		char *try = join_path(paths[i], cmd);
		if (access(try, X_OK) == 0) { res = try; break; }
		free(try);
	}
	for (int i = 0; paths[i]; ++i) free(paths[i]);
	free(paths);
	return res;
}
