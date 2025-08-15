/* Very small parser: handles ;, |, >, >>, <, simple quotes and $VAR substitution */
#include "minishell.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
static char *dup_subst(const char *s)
{
	char buf[4096]; size_t bi=0;
	for (size_t i=0; s[i] && bi+1 < sizeof(buf); )
	{
		if (s[i]=='\'') {
			i++;
			while (s[i] && s[i] != '\'') { buf[bi++] = s[i++]; }
			if (s[i]=='\'') i++;
		}
		else if (s[i]=='"') {
			i++;
			while (s[i] && s[i]!='"') {
				if (s[i]=='$') {
					i++;
					size_t st=i;
					while (s[i] && (isalnum((unsigned char)s[i])|| s[i]=='_')) i++;
					char name[256]; size_t ln = i-st;
					if (ln>=sizeof(name)) ln = sizeof(name)-1;
					strncpy(name, s+st, ln); name[ln]=0;
					char *v = getenv(name);
					if (v) {
						size_t lv = strlen(v);
						if (bi + lv < sizeof(buf)) { memcpy(buf+bi, v, lv); bi += lv; }
					}
				} else { buf[bi++] = s[i++]; }
			}
			if (s[i]=='"') i++;
		}
		else if (s[i]=='$') {
			i++;
			size_t st=i;
			while (s[i] && (isalnum((unsigned char)s[i])|| s[i]=='_')) i++;
			char name[256]; size_t ln = i-st;
			if (ln>=sizeof(name)) ln = sizeof(name)-1;
			strncpy(name, s+st, ln); name[ln]=0;
			char *v = getenv(name);
			if (v) {
				size_t lv = strlen(v);
				if (bi + lv < sizeof(buf)) { memcpy(buf+bi, v, lv); bi += lv; }
			}
		}
		else buf[bi++] = s[i++];
	}
	buf[bi]=0;
	return strdup(buf);
}
static char *next_word(const char *s, size_t *pos)
{
	while (s[*pos] && isspace((unsigned char)s[*pos])) (*pos)++;
	if (!s[*pos]) return NULL;
	size_t i = *pos;
	char tmp[4096]; size_t ti=0;
	if (s[i]=='\'' || s[i]=='"')
	{
		char q = s[i++]; while (s[i] && s[i]!=q) tmp[ti++]=s[i++]; if (s[i]==q) i++;
	}
	else
	{
		while (s[i] && !isspace((unsigned char)s[i]) && s[i] != '|' && s[i] != ';' ) tmp[ti++]=s[i++];
	}
	tmp[ti]=0;
	*pos = i;
	return dup_subst(tmp);
}
static char *strdup_safe(const char *s) { return s ? strdup(s) : NULL; }
t_cmd *parse_line(const char *line)
{
	size_t pos=0;
	t_cmd *head = NULL;
	t_cmd *cur = NULL;
	while (1)
	{
		char *word = next_word(line, &pos);
		if (!word) break;
		if (!cur) {
			cur = calloc(1, sizeof(t_cmd));
			if (!head) head = cur;
			else {
				// find tail and append
				t_cmd *t = head; while (t->next) t=t->next; t->next = cur;
			}
		}
		int argc = 0;
		if (cur->argv) { while (cur->argv[argc]) argc++; }
		char **nargv = malloc((argc+2+1)*sizeof(char*));
		for (int i=0;i<argc;i++) nargv[i]=cur->argv[i];
		nargv[argc]=word;
		nargv[argc+1]=NULL;
		free(cur->argv);
		cur->argv = nargv;
		while (line[pos] && isspace((unsigned char)line[pos])) pos++;
		if (line[pos] == '>')
		{
			int append = 0;
			if (line[pos+1] == '>') { append = 1; pos++; }
			pos++;
			while (isspace((unsigned char)line[pos])) pos++;
			char *f = next_word(line, &pos);
			cur->outfile = strdup_safe(f);
			cur->append = append;
		}
		else if (line[pos] == '<')
		{
			pos++;
			while (isspace((unsigned char)line[pos])) pos++;
			char *f = next_word(line, &pos);
			cur->infile = strdup_safe(f);
		}
		while (line[pos] && isspace((unsigned char)line[pos])) pos++;
		if (line[pos] == '|')
		{
		 cur->is_pipe = 1;
		 pos++;
		 t_cmd *n = calloc(1,sizeof(t_cmd));
		 cur->next = n;
		 cur = n;
		}
		else if (line[pos] == ';')
		{
		 pos++;
		 cur->next = NULL;
		 cur = NULL;
		}
	}
	return head;
}
void free_cmds(t_cmd *head)
{
	while (head)
	{
		t_cmd *n = head->next;
		if (head->argv) { for (int i=0; head->argv[i]; ++i) free(head->argv[i]); free(head->argv); }
		free(head->infile);
		free(head->outfile);
		free(head);
		head = n;
	}
}
