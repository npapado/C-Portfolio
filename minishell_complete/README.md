# minishell (42 School) — minimal mandatory features
Build:
```
make
```
Run:
```
./minishell
```
This implements a minimal shell with:
- prompt, command execution (PATH), basic redirections (<, >, >>)
- pipes, simple variable substitution $VAR, builtins: echo, cd, pwd, export, unset, env, exit
- ctrl-C and ctrl-D handling
