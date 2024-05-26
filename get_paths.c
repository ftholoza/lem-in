/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francesco <francesco@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:53:17 by francesco         #+#    #+#             */
/*   Updated: 2024/05/26 17:46:43 by francesco        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

bool    check_room_diff(t_room  *first, t_room   *second,char  *start_name, char *end_name)
{
    //printf("%s\n", start_name);
    //printf("%s, %s\n", first->name, second->name);
    if (ft_strncmp(start_name, first->name, ft_strlen(start_name) + 1) == 0
        || ft_strncmp(start_name, second->name, ft_strlen(start_name) + 1) == 0)
        return (false);
    if (ft_strncmp(end_name, first->name, ft_strlen(end_name) + 1) == 0
        || ft_strncmp(end_name, second->name, ft_strlen(end_name) + 1) == 0)
        return (false);
    if (ft_strncmp(first->name, second->name, ft_strlen(first->name) + 1) == 0)
        return (true);
    return (false);
}

bool    check_path_diff(t_list   *first, t_list  *second, char  *start_name, char *end_name)
{
    t_list  *temp_first;
    t_list  *temp_second;
    t_room  *room;
    t_list  *best;
    
    temp_first = first;
    temp_second = second;
    /*printf("-----------------------\n");
    print_room_list(first);
    print_room_list(second);
    printf("-----------------------\n");*/
    while (temp_first != NULL)
    {
        while(temp_second != NULL)
        {
            if (check_room_diff(temp_first->content, temp_second->content, start_name, end_name) == true)
            {
                //printf("is diff\n");
                return (true);
            }
            temp_second = temp_second->next;
        }
        temp_second = second;
        temp_first = temp_first->next;
    }
    //printf("ok\n");
    return (false);
}

bool    add_to_selected(t_list  *all_paths, t_data  *data)
{
    t_list  *temp;
    t_list  *seltemp;
    t_list  *paths;
    bool    x;
    bool    y;

    x = true;
    y = false;
    seltemp = data->selected_paths;
    paths = all_paths;
    temp = all_paths;
    if (ft_lstsize(all_paths) == 1)
    {
        ft_lstadd_back(&data->selected_paths, ft_lstnew(temp->content));
        return false;
    }
    while (paths != NULL)
    {
        if (ft_lstsize(temp->content) >= ft_lstsize(paths->content))
        {
            while (seltemp != NULL)
            {
                if (check_path_diff(seltemp->content, paths->content, data->start->name, data->end->name) == true)
                    x = false;
                seltemp = seltemp->next;
            }
            //printf("%d\n", x);
            if (x == true)
            {
                temp = paths;
                y = true;
            }
        }
        x = true;
        seltemp = data->selected_paths;
        paths = paths->next;
    }
    if (y == true)
    {
        //print_room_list(temp->content);
        ft_lstadd_back(&data->selected_paths, ft_lstnew(temp->content));
        return (true);
    }
    return (false);
}

void    clean_paths(t_list *all_paths, t_data   *data)
{
    data->selected_paths = NULL;
    while (add_to_selected(all_paths, data) == true)
        ;
        //printf("call here:\n")
    //add_to_selected(all_paths, data);
    //add_to_selected(all_paths, data);
    //add_to_selected(all_paths, data);

}

void    print_all_paths(t_list *all_paths)
{
    t_list *temp;
    t_room  *room;

    //printf("ok\n");
    temp = all_paths;
    printf("\033[1;34m------------------PATHS------------------- \n\033[0m");
    while (temp != NULL)
    {
        //temp->content;
        print_room_list(temp->content);
        printf("\033[1;34m------------------------------------------- \n\033[0m");
        temp = temp->next;
    }
    //printf("%d\n", ft_lstsize(all_paths));
    //printf("fin du print\n");
    return ;
}

void    print_room_list(t_list *list)
{
    t_list *temp;
    t_room *room;


    temp = list;
    printf("\033[1;34m[START]\033[0m ");
    while (temp != NULL)
    {
        room = temp->content;
        printf("%s", room->name);
        printf("\033[1;35m => \033[0m");
        temp = temp->next;
    }
    printf("\033[1;34m[END] \n\033[0m");
    return;
}

void    del_room(void *room)
{
    t_room *r = room;
    (void)room;
}

t_list *ft_lstclone(t_list *lst)
{
    t_list  *res;
    t_list  *temp;

    temp = lst;
    res = NULL;
    while (temp != NULL)
    {
        ft_lstadd_back(&res, ft_lstnew(temp->content));
        temp = temp->next;
    }
    return (res);
}

void    find_path_rec(t_data * data, t_room *room, t_list *path)
{
    t_list *temp;
    t_room *r;
    t_room  *x;
    
    if (path == NULL)
        ft_lstadd_back(&path, ft_lstnew(data->start));
    if (ft_strncmp(room->name, data->end->name, ft_strlen(data->end->name) + 1) == 0)
    {
        ft_lstadd_back(&path, ft_lstnew(room));
        ft_lstadd_back(&data->all_paths, ft_lstnew(ft_lstclone(path)));
        ft_dl_last(path, del_room);
        return ;
    }
    temp = room->next_room;
    while (temp != NULL)
    {
        r = temp->content;
        if (r->visited == true)
            ;
        else
        {
            if (ft_strncmp(room->name, data->start->name, ft_strlen(room->name) + 1) == 0)
                ;
            else
                ft_lstadd_back(&path, ft_lstnew(room));
            room->visited = true;
            find_path_rec(data, r, path);
            x = ft_lstlast(path)->content;
            x->visited = false;
            ft_dl_last(path, del_room);
        }
        temp = temp->next;
    }
    //printf ("end process: %s\n", room->name);
    //ft_dl_last(path, del_room);
    return;
}

void    reset_visits(t_data *data)
{
    t_list *temp;
    t_room * room;
    
    temp = data->rooms;
    while (temp != NULL)
    {
        room = temp->content;
        room->visited = false;
        temp = temp->next;
    }
    return ;
}

void    get_paths(t_data *data)
{
    t_room *start;
    t_list *temp;
    t_room *room;
    int     i;

    i = 0;
    temp = data->rooms;

    start = data->start;
    temp = start->next_room;
    room = temp->content;
    find_path_rec(data, data->start, NULL);
    temp = temp->next;
}