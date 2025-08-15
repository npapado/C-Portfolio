# ft_ls (mandatory flags: -l -R -a -r -t)

- Sort: name asc; `-t` by mtime desc; `-r` reverses.
- `-R` recurses (skips `.` and `..`).
- `-l` prints perms, links, owner, group, size or major/minor, date (6‑month rule), symlink target.
- Errors as `ft_ls: <path>: <strerror>`.

## Build
make

## Run
./ft_ls -lRart .
