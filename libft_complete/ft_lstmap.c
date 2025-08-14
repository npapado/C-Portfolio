#include "libft.h"

static void	free_list(t_list *lst, void (*del)(void *))
{
	t_list	*next;

	while (lst)
	{
		next = lst->next;
		if (del)
			del(lst->content);
		free(lst);
		lst = next;
	}
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*tail;
	t_list	*node;
	void	*content;

	if (!f)
		return (NULL);
	new_list = NULL;
	tail = NULL;
	while (lst)
	{
		content = f(lst->content);
		node = ft_lstnew(content);
		if (!node)
		{
			free_list(new_list, del);
			return (NULL);
		}
		if (!new_list)
			new_list = node;
		else
			tail->next = node;
		tail = node;
		lst = lst->next;
	}
	return (new_list);
}
