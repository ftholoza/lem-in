/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francesco <francesco@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:51:57 by francesco         #+#    #+#             */
/*   Updated: 2024/05/26 18:11:01 by francesco        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "stdio.h"
#include    "stdlib.h"
#include    "lem_in.h"

void    give_ants(t_list    *select_paths, int tot_ants)
{
    t_list  *temp;
    t_list  *temp2;
    t_list  *little;
    t_room  *room;
    t_room  *little_room;

    temp = select_paths;
    while (tot_ants > 0)
    {
        while (temp != NULL)
        {
            temp2 = temp->content;
            room = temp2->next->content;
            room->score = ft_lstsize(temp2) + room->tot_ants;
            temp = temp->next;
        }
        temp = select_paths;
        little = temp->content;
        while (temp != NULL)
        {
            temp2 = temp->content;
            little_room = little->next->content;
            room = temp2->next->content;
            if (little_room->score > room->score)
                little = temp2;
            temp = temp->next;
        }
        room = little->next->content;
        room->tot_ants++;
        room->starting_room = true;
        tot_ants--;
        temp = select_paths;
    }
    temp = select_paths;
    while (temp != NULL)
    {
        temp2 = temp->content;
        //print_room_list(temp2);
        room = temp2->next->content;
        //printf("ants: %d\n", room->tot_ants);
        temp = temp->next;
    }
}

void    print_parcour(t_data    *data, int  tot_ants)
{
    int i;
    t_list  *all_paths;
    t_list  *path;
    t_room  *room;
    t_room  *next_room;

    i = 1;
    (void)tot_ants;
    while (data->end->tot_ants != tot_ants)
    {
        //printf("%d\n", i);
        //printf("here: %d\n", data->end->tot_ants);
        all_paths = data->selected_paths;
        while (all_paths != NULL)
        {
            path = all_paths->content;
            while (path != NULL)
            {
                room = path->content;
                //printf("room_name: %s, %d\n", room->name, room->waiting_room);
                if (path->next != NULL)
                    next_room = path->next->content;
                else
                    next_room = NULL;
                if (next_room != NULL)
                {                    
                    if (room->starting_room == true)
                    {
                        if (room->waiting_room != 0)
                        {
                            room->ant_name = room->waiting_room;
                            room->waiting_room = 0;
                        }
                        if (room->ant_name != 0)
                        {
                            next_room->waiting_room = room->ant_name;
                            room->tot_ants--;
                            printf("L%d-%s ", room->ant_name, next_room->name);
                            room->ant_name = 0;
                        }
                        if (room->tot_ants > 0)
                        {
                            room->waiting_room = i;
                            printf("L%d-%s ", i, room->name);
                            i++;
                        }
                    }
                    else
                    {
                        if (room->ant_name != 0)
                        {
                            next_room->waiting_room = room->ant_name;
                            room->tot_ants--;
                            printf("L%d-%s ", room->ant_name, next_room->name);
                            room->ant_name = 0;
                        }
                        if (room->waiting_room != 0)
                        {
                            room->ant_name = room->waiting_room;
                            room->waiting_room = 0;
                            room->tot_ants++;
                        }
                    }
                }
                if (next_room == NULL)
                {
                    if (room->waiting_room != 0)
                        room->tot_ants++;
                    room->waiting_room = 0;
                }
                path = path->next;
            }
            all_paths = all_paths->next;
            //printf("\n");
        }
        printf("\n");
    }
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("%s\n", "\033[1;31mERROR: INVALIDS ARGUMENTS\033[0m");
        return (0);
    }
    t_data  *data;
    printf("\033[1;31m<LEM-IN> \n\033[0m");
    data = init_data();
    readfile(argv[1], data);
    print_data(data);
    print_map(data);
    get_paths(data);
    //print_all_paths(data->all_paths);
    clean_paths(data->all_paths, data);
    printf("\033[1;31m\n                SELECTED\n\033[0m");
    print_all_paths(data->selected_paths);
    give_ants(data->selected_paths, 20);
    print_parcour(data, 20);
    
    return (0);
}