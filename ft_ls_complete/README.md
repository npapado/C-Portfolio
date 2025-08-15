
# ft_ls (42) — flags: -l -R -a -r -t

- Close to BSD `ls`.
- Uses `lstat`; shows symlink target in `-l`.
- Recursive `-R`, hidden with `-a`.
- Sort by name or mtime (`-t`), reversed with `-r`.

## Build
```
make
```
