/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 17:54:03 by bmoiroud          #+#    #+#             */
/*   Updated: 2016/11/22 17:23:03 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*addend(t_list *alst, t_list *new)
{
	if (alst->next)
		addend(alst->next, new);
	else
		alst->next = new;
	return (alst);
}

t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list		*tmp;

	tmp = NULL;
	if (!lst)
		return (NULL);
	tmp = f(lst);
	if (!tmp || !f)
		return (NULL);
	return (addend(tmp, ft_lstmap(lst->next, f)));
}
