
# fillit (42 School) — no rotations

- Allowed funcs: `exit, open, close, write, read, malloc, free`.
- Pieces are **not rotated**; they are translated and kept in the orientation they appear in the file.
- Solver: backtracking, tries positions top-left first to satisfy "upper-left" rule.

## Build
```
make
```

## Run
```
./fillit samples/valid.fillit
```
