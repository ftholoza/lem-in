/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francesco <francesco@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:58:16 by francesco         #+#    #+#             */
/*   Updated: 2024/05/26 15:13:39 by francesco        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "fcntl.h"
# include "stdbool.h"
# include "ctype.h"


typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct  t_room
{
    char    *name;
    char    *end;
    int     x;
    int     y; 
    bool    visited;
    bool    starting_room;
    int     ant_name;
    int     waiting_room;
    int     tot_ants;
    int     score;
    struct s_list  *next_room;
}   t_room;

typedef struct  t_data
{
    t_room  *start;
    t_room  *end;
    struct  s_list  *rooms;
    int     ants_count;
    t_list  *all_paths;
    t_list  *selected_paths;
}   t_data;

char	*get_next_line(int fd);
t_data  *init_data();
t_data  *readfile(char *file_name, t_data *data);
int     ft_strncmp(const char *s1, const char *s2, size_t n);
int     ft_lstsize(t_list *lst);
t_list	*ft_lstnew(void *content);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
int     ft_strlen(char *str);
void    print_data(t_data *data);
void    print_room_list(t_list *list);
void    get_paths(t_data *data);
void    print_all_paths(t_list *all_paths);
void    print_map(t_data *data);
void	ft_dl_last(t_list *lst, void (*del)(void *));
void    clean_paths(t_list  *all_paths, t_data  *data);
t_list *ft_lstclone(t_list *lst);





#endif