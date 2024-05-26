/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dl_del.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francesco <francesco@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 10:06:05 by gbrunet           #+#    #+#             */
/*   Updated: 2024/05/22 18:09:32 by francesco        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_dl_last(t_list *lst, void (*del)(void *))
{
	t_list *temp;

	temp = lst;
	while (temp->next != NULL)
	{
		if (temp->next->next == NULL)
		{
			del(temp->next->content);
			free(temp->next);
			temp->next = NULL;
			return ;
		}
		temp = temp->next;
	}
	return ;
}
