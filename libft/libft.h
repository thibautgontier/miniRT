/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgontier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 10:57:51 by tgontier          #+#    #+#             */
/*   Updated: 2019/11/23 17:41:17 by tgontier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>
# include <unistd.h>
# include <limits.h>

# include "get_next_line.h"

# define TRUE 1
# define FALSE 0

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

float				ft_atof(char *str);
int					ft_atoi(const char *nptr);
void				ft_bzero(void *s, size_t n);
char				*ft_c_to_str(char c);
void				*ft_calloc(size_t count, size_t size);
size_t				ft_intlen(intmax_t n);
int					ft_is_in_stri(char c, char *str);
size_t				ft_is_space(char c);
int					ft_isdigit(int c);
char				*ft_itoa(intmax_t n);
void				ft_lstadd_back(t_list **alst, t_list *new);
void				ft_lstclear(t_list **lst, void (*del)(void *));
t_list				*ft_lstlast(t_list *lst);
t_list				*ft_lstnew(void *content);
int					ft_lstsize(t_list *lst);
void				*ft_memalloc(size_t size);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memset(void *b, int c, size_t len);
void				ft_putchar_fd(char c, int fd);
void				ft_putchar(char c);
void				ft_putendl(char *s);
void				ft_putstr_fd(char *s, int fd);
void				ft_putstr(char *s);
char				**ft_split(char const *s, char c);
char				**ft_ssplit(char const *s, char *set);
int					ft_str_c_count(char *str, char c);
int					ft_str_end(char *str, char *end);
char				*ft_strcat(char *dst, const char *src);
char				*ft_strcpy(char *dst, const char *src);
void				ft_strdel(char **as);
int					ft_strequ(char *s1, char *s2);
char				*ft_strjoin(char const *s1, char const *s2);
size_t				ft_strlen_c(char *s, char c);
size_t				ft_strlen(const char *s);
char				*ft_strnew(size_t size);
char				*ft_substr(char const *s, unsigned int start, size_t len);
int					get_next_line(int fd, char **line);

#endif
