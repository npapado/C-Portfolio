
#include "ft_select.h"
#include <string.h>

int main(int argc, char **argv)
{
    t_state st;

    if (argc < 2) return 0;

    memset(&st, 0, sizeof(st));
    st.count = argc - 1;
    st.items = xmalloc(sizeof(t_item) * st.count);
    for (int i = 0; i < st.count; ++i)
    {
        st.items[i].text = xstrdup(argv[i+1]);
        st.items[i].selected = 0;
        st.items[i].alive = 1;
    }
    st.cur = 0; st.top = 0;

    if (term_init(&st) != 0) { write(2, "ft_select: terminal init failed\n", 32); return 1; }
    setup_signals(&st);
    ui_refresh(&st);

    for (;;)
    {
        int r = handle_key(&st);
        if (r == 2) return 0;
        ui_refresh(&st);
    }
}
