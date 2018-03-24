/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 17:30:34 by bmoiroud          #+#    #+#             */
/*   Updated: 2016/11/21 17:57:53 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(const void *content, size_t content_size)
{
	t_list			*newlist;
	unsigned char	*newcont;

	if ((newlist = (t_list *)malloc(sizeof(t_list))) == NULL)
		return (NULL);
	if (content != NULL)
	{
		if ((newcont = (unsigned char *)malloc(content_size)))
		{
			ft_memcpy(newcont, content, content_size);
			newlist->content = (void *)newcont;
		}
		if (content_size != 0)
			newlist->content_size = content_size;
		else
			newlist->content_size = 0;
	}
	else
	{
		newlist->content = 0;
		newlist->content_size = 0;
	}
	newlist->next = NULL;
	return (newlist);
}
