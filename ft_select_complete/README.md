
# ft_select (termcap)
- Single-column view with scrolling.
- **Underline** = cursor, **reverse video** = selected; both when cursor+selected.
- Clear redraw each key; viewport follows cursor; SIGWINCH resize handled.
- Keys: arrows, Space toggle, Backspace/Delete remove, Enter confirm, Esc quit.

Build:
```
make
```
Run:
```
./ft_select item1 item2 item3 ...
```
Note: Linker uses `-ltermcap`. On some systems use `-lncurses` instead.
