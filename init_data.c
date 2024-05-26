/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francesco <francesco@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 20:24:08 by francesco         #+#    #+#             */
/*   Updated: 2024/05/23 05:34:02 by francesco        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_data  *init_data()
{
    t_data  *res;

    res = malloc(sizeof(t_data));
    if (!res)
    {
        printf("%s\n", "\033[1;31mERROR: MALLOC FAILED\033[0m");
        return (NULL);
    }
    res->start = NULL;
    res->end = NULL;
    res->rooms = NULL;
    res->ants_count = -1;
    res->all_paths = NULL;
    res->selected_paths = NULL;
    return (res);
}
