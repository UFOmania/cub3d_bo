/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <massrayb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:16:27 by ybassour          #+#    #+#             */
/*   Updated: 2025/08/28 13:08:03 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_list
{
	char			*str_buffer;
	void			*content;
	struct s_list	*next;
}	t_list;
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

t_list	*ft_find_first_node(t_list *list);
char	*get_next_line(int fd);
char	*ft_read_line(t_list *list);
size_t	ft_is_found_newline(t_list *list);
size_t	ft_length_to_newline(t_list *list);
int		ft_listmap(t_list **list);
int		ft_create_list(t_list **list, int fd);
void	ft_strcpy_fromlist(t_list *list, char *str);
int		ft_listclear(t_list **list, t_list *new_node, char *buffer);
void	ft_listadd_back(t_list **list, char *buf);

int		ft_isdigit(int c);

int		ft_atoi(const char *str);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

size_t	ft_strlcpy(char *dest, const char *src, size_t destsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);

void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *b, size_t n);

void	*ft_calloc(size_t n, size_t size);

void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
char	*ft_strdup(const char *s1);
char	*ft_inttoa(int n);

#endif
