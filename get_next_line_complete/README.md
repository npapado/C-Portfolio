
# get_next_line (42 School)

Implements `get_next_line(int fd, char **line)` returning:
- `1` when a line is read (without the trailing newline in `*line`)
- `0` at EOF
- `-1` on error

## Build
```sh
make        # builds mandatory version into gnl_test
make bonus  # builds bonus (multi-fd with single static list head)
```

## Run
```sh
./gnl_test path/to/file
# or read from stdin:
./gnl_test
```
