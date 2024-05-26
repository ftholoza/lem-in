/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francesco <francesco@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 20:00:00 by francesco         #+#    #+#             */
/*   Updated: 2024/05/26 17:53:04 by francesco        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "lem_in.h"

char    *get_room_name(char *line)
{
    int     i;
    int     j;
    int     count;
    char    *res;

    i = 0;
    j = 0;
    count = 0;
    while (line[i] && isspace(line[i]))
        i++;
    while (line[i] && !isspace(line[i]))
    {
        count++;
        i++;
    }
    res = malloc(sizeof(char) * count + 1);
    if (!res)
    {
        printf("%s\n", "\033[1;31mERROR: MALLOC FAILED\033[0m");
        return (NULL);
    }
    res[count] = '\0';
    while (line[i - count] && !isspace(line[i - count]))
    {
        res[j] = line[i - count];
        i++;
        j++;
    }
    return (res);
}

void    init_room_x_cord(char *line, t_room *room)
{
    int i;
    int j;
    int count;
    char    *temp;

    i = 0;
    j = 0;
    count = 0;
    (void)room;
    while (line[i] && isspace(line[i]))
        i++;
    while (line[i] && !isspace(line[i]))
        i++;
    while (line[i] && isspace(line[i]))
        i++;
    while (line[i] && !isspace(line[i]))
    {
        i++;
        count++;
    }
    temp = malloc(sizeof(char) * count + 1);
    temp[count] = '\0';
    while (line[i - count] && !isspace(line[i - count]))
    {
        temp[j] = line[i - count];
        i++;
        j++;
    }
    room->x = atoi(temp);
    //printf("%d\n", room->x);
    free (temp);
    return;
}

void    init_room_y_cord(char *line, t_room *room)
{
    int i;
    int j;
    int count;
    char    *temp;

    i = 0;
    j = 0;
    count = 0;
    (void)room;
    while (line[i] && isspace(line[i]))
        i++;
    while (line[i] && !isspace(line[i]))
        i++;
    while (line[i] && isspace(line[i]))
        i++;
    while (line[i] && !isspace(line[i]))
        i++;
    while (line[i] && isspace(line[i]))
        i++;
    while (line[i] && !isspace(line[i]))
    {
        i++;
        count++;
    }
    temp = malloc(sizeof(char) * count + 1);
    temp[count] = '\0';
    while (line[i - count] && !isspace(line[i - count]))
    {
        temp[j] = line[i - count];
        i++;
        j++;
    }
    room->y = atoi(temp);
    free (temp);
    return;
}

t_room  *init_room(char *line)
{
    t_room  *res;

    res = malloc(sizeof(t_room));
    if (!res)
    {
        printf("%s\n", "\033[1;31mERROR: MALLOC FAILED\033[0m");
        return (NULL);
    }
    res->name = get_room_name(line);
    res->next_room = NULL;
    init_room_x_cord(line, res);
    init_room_y_cord(line, res);
    res->visited = false;
    res->tot_ants = 0;
    res->waiting_room = 0;
    res->ant_name = 0;
    res->starting_room = false;
    //res->is_valid = -1;
    return (res);
}

void    add_start(t_data *data, int fd)
{
    char    *line;

    line = get_next_line(fd);
    data->start = init_room(line);
    data->start->visited = true;
    if (!line)
        return ;    
}

void    add_end(t_data *data, int fd)
{
    char    *line;

    line = get_next_line(fd);
    data->end = init_room(line);
    if (!line)
        return ;    
}

void    add_room(t_data *data, char *line)
{
    t_room *room;

    room = malloc(sizeof(t_room));
    room->name = get_room_name(line);
    room->next_room = NULL;
    init_room_x_cord(line, room);
    init_room_y_cord(line, room);
    room->visited = false;
    room->tot_ants = 0;
    room->waiting_room = 0;
    room->ant_name = 0;
    room->starting_room = false;
    //room->is_valid = -1;
    //if (data->rooms == NULL)
    //    data->rooms = ft_lstnew(room);
    //else
    ft_lstadd_front(&data->rooms, ft_lstnew(room));
    return ;
}

void    print_connections(t_list *next_rooms)
{
    t_room  *r;
    t_list  *temp;

    //(void)r;
    //(void)temp;
    printf("\033[1;32mconnections: \033[0m");
    temp = next_rooms;
    if (temp == NULL)
    {
        printf("Not connected\n");
        return;
    }
    /*r = temp->content;
    printf("%s ", r ->name);
    temp = temp->next;
    r = temp->content;
    printf("%s\n", r ->name);
    temp = temp->next;
    //printf("%p\n", temp);
    temp = temp->next;*/
    //printf("%p\n", temp);


    while (temp != NULL)
    {
        //printf("%p ", temp);
        r = temp->content;
        printf("%s ", r->name);
        temp = temp->next;
    }
    printf("\n\n");
    return ;
}

void    print_data(t_data *data)
{
    t_list *temp;
    t_room *r;
    temp = data->rooms;
    printf("\033[1;32m-----Start room-----\n\033[0m");
    printf("\033[1;32mname:\033[0m%s", data->start->name);
    printf("\033[1;32m x: \033[0m%d ", data->start->x);
    printf("\033[1;32my: \033[0m%d\n", data->start->y);
    print_connections(data->start->next_room);
    printf("\033[1;32m-----End room-----\n\033[0m");
    printf("\033[1;32mname:\033[0m%s", data->end->name);
    printf("\033[1;32m x: \033[0m%d ", data->end->x);
    printf("\033[1;32my: \033[0m%d\n", data->end->y);
    print_connections(data->end->next_room);
    printf("\033[1;32m------ROOMS------\n\033[0m");
    while (temp != NULL) 
    {
        r = temp->content;
        printf("\033[1;32mname:\033[0m%s", r->name);
        printf("\033[1;32m x: \033[0m%d ", r->x);
        printf("\033[1;32my: \033[0m%d\n", r->y);
        //printf("%p\n", r->next_room);
        print_connections(r->next_room);
        temp = temp->next;
    }
}

bool    check_connection(char *line)
{
    int i;

    i = 0;
    //printf("%s\n", line);
    while (line[i])
    {
        if (line[i] == '-')
            return (true);
        i++;
    }
    return (false);
}

int ft_strlen(char *str)
{
    int i;
    
    i = 0;
    if (!str)
        return (0);
    while (str[i])
        i++;
    return(i);
}

t_room  *find_room(char *name, t_data *data)
{
    t_room  *room;
    t_list  *temp;
    
    temp = data->rooms;
    (void)name;
    while (temp != NULL)
    {
        room = temp->content;
        //printf("ici:%s\n", room->name);
        if (ft_strncmp(room->name, name, ft_strlen(room->name)) == 0)
            return (room);
        temp = temp->next;
    }
    room = data->start;
    if (ft_strncmp(room->name, name, ft_strlen(room->name)) == 0)
        return (room);
    room = data->end;
    if (ft_strncmp(room->name, name, ft_strlen(room->name)) == 0)
        return (room);
    return (NULL);
}

void    connect(char *first, char *second, t_data *data)
{
    t_room *a;
    t_room *b;

    (void)b;
    //printf("%s\n", first);
    a = find_room(first, data);
    b = find_room(second, data);
    //printf("%p\n", a->next_room);
    //printf("here a: %p\n", a->next_room);
    ft_lstadd_front(&a->next_room, ft_lstnew(b));
    //printf("here b: %p\n", b->next_room);
    ft_lstadd_front(&b->next_room, ft_lstnew(a));
    return ;
}

void    add_connection(char *line, t_data *data)
{
    char *first;
    char *second;
    int i;
    int j;
    int count;
    int temp;

    i = 0;
    j = 0;
    count = 0;
    (void)second;
    while (line[i] && line[i] != '-')
    {
        count++;
        i++;
    }
    first = malloc(sizeof(char) * count + 1);
    first[count] = '\0';
    temp = i;
    while (line[temp - count] && line[temp - count] != '-')
    {
        first[j] = line[temp - count];
        j++;
        temp++;   
    }
    if ((line[temp - count] != '\0') && line[temp - count] == '-')
        temp++;
    i = temp - count;
    temp = i;
    j = 0;
    while (line[i])
    {
        j++;
        i++;
    }
    second = malloc(sizeof(char) * j + 1);
    second[j] = '\0';
    j = 0;
    while (line[temp])
    {
        second[j] = line[temp];
        temp++;
        j++;
    }
    connect(first, second, data);
}

int     find_nstring(t_data *data)
{
    t_list  *temp;
    t_room  *room;
    int     nb;

    temp = data->rooms;
    nb = 0;
    while (temp != NULL)
    {
        room = temp->content;
        //printf("%s ", room->name);
        //printf("y: %d\n", room->y);
        if (room->y > nb)
            nb = room->y;
        temp = temp->next;
    }
    room = data->start;
    if (room->y > nb)
        nb = room->y;
    room = data->end;
    if (room->y > nb)
        nb = room->y;
    return nb;
}

int     find_nchar(t_data *data)
{
    t_list  *temp;
    t_room  *room;
    int     nb;

    temp = data->rooms;
    nb = 0;
    while (temp != NULL)
    {
        room = temp->content;
        //printf("%s ", room->name);
        //printf("x: %d\n", room->y);
        if (room->x > nb)
            nb = room->x;
        temp = temp->next;
    }
    room = data->start;
    if (room->x > nb)
        nb = room->x;
    room = data->end;
    if (room->x > nb)
        nb = room->x;
    return nb;
}

void    print_tab(char **tab)
{
    int i;
    int j;

    i = 0;
    j = 0;
    printf(" ");
    while (i < ft_strlen(tab[j]))
    {
        printf("-");
        i++;
    }
    printf("\n");
    i = 0;
    while (tab[j])
    {
        printf("|%s|\n", tab[j]);
        j++;
    }
    j = 0;
    printf(" ");
    while (i < ft_strlen(tab[j]))
    {
        printf("-");
        i++;
    }
    printf("\n");
    i = 0;
}

void    add_map_rooms(t_data *data, char **map)
{
    t_list  *temp;
    t_room  *room;

    temp = data->rooms;
    while (temp != NULL)
    {
        room = temp->content;
        map[room->y][room->x] = room->name[0];
        //printf("co: %d, %d\n", room->y, room->x);
        temp = temp->next;
    }
    room = data->start;
    map[room->y][room->x] = room->name[0];
    room = data->end;
    map[room->y][room->x] = room->name[0];
}

void    init_map(char **map, int nstring, int nchar)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while(j < nstring)
    {
        //printf("ok\n");
        while (i < nchar)
        {
            map[j][i] = ' ';
            i++;
        }
        i = 0;
        j++;
    }
    //print_tab(map);
}

void    print_map(t_data *data)
{
    int     nstring;
    int     nchar;
    char    **map;
    int     i;
    int     j;

    i = 0;
    j = 0;
    nstring = find_nstring(data);
    nchar = find_nchar(data);

    nstring += 3;
    nchar += 3;
    map = malloc(sizeof(char *) * (nstring + 1));
    map[nstring] = NULL;
    while(j < nstring)
    {
        map[j] = malloc(sizeof(char) * nchar + 1);
        map[j][nchar] = '\0';
        j++;
    }
    init_map(map, nstring, nchar);
    add_map_rooms(data, map);
    print_tab(map);
}

t_data  *readfile(char *file_name, t_data *data)
{
    char    *line;
    int     fd;

    (void)line;
    data->ants_count = 5;
    fd = open(file_name, O_RDONLY);
    if (!fd)
    {
        printf("%s\n", "\033[1;31mERROR: INVALID FILE\033[0m");
        return (NULL);
    }
    line = get_next_line(fd);
    while (line)
    {
        if  (ft_strlen(line) <= 1)
            ;
        else if (ft_strncmp(line, "##start", 7) == 0)
            add_start(data, fd);
        else if (ft_strncmp(line, "##end", 5) == 0)
            add_end(data, fd);
        else if (check_connection(line) == true)
        {
            //printf("here: %s\n", line);
            add_connection(line, data);
        }
        else
            add_room(data, line);
        line = get_next_line(fd);
    }
    return (NULL);
}