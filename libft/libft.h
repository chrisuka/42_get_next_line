/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <ikarjala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 17:06:35 by ikarjala          #+#    #+#             */
/*   Updated: 2022/04/03 11:15:30 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <unistd.h>
# include <stdlib.h>
# include <string.h>

# define FT_INT_MAX	(signed int)0x7FFFFFFF
# define FT_INT_MIN	(signed int)0x80000000

# define FT_TRUE	1
# define FT_FALSE	0

typedef unsigned char		t_bool;
typedef unsigned char	t_byte;
typedef signed char		t_sbyte;
typedef unsigned int	t_uint;

/*
** PART 1 & 2
*/

void	ft_putchar_fd(char c, int fd);
void	ft_putchar(char c);
void	ft_putstr_fd(const char *s, int fd);
void	ft_putstr(const char *s);
void	ft_putendl_fd(const char *s, int fd);
void	ft_putendl(const char *s);
void	ft_putnbr_fd(int n, int fd);
void	ft_putnbr(int n);

int		ft_isdigit(int c);
int		ft_isalpha(int c);
int		ft_isalnum(int c);
int		ft_isprint(int c);
int		ft_isascii(int c);
int		ft_tolower(int c);
int		ft_toupper(int c);

int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *b, int c, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memccpy(void *dst, const void *src, int c, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_memalloc(size_t size);
void	ft_memdel(void **ap);

char	*ft_strcpy(char *dst, const char *src);
char	*ft_strncpy(char *dst, const char *src, size_t len);
char	*ft_strdup(const char *s1);
char	*ft_strcat(char *s1, const char *s2);
char	*ft_strncat(char *s1, const char *s2, size_t n);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);

size_t	ft_strlen(const char *s);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strequ(const char *s1, const char *s2);
int		ft_strnequ(const char *s1, const char *s2, size_t n);

char	*ft_strnew(size_t size);
void	ft_strdel(char **as);
void	ft_strclr(char *s);

char	**ft_strsplit(const char *s, char c);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strtrim(const char *s);
char	*ft_strsub(const char *s, unsigned int start, size_t len);
char	*ft_strmap(const char *s, char (*f)(char));
char	*ft_strmapi(const char *s, char (*f)(unsigned int, char));
void	ft_striter(char *s, void (*f)(char *));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));

char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strstr(const char *haystack, const char *needle);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

int		ft_atoi(const char *str);
char	*ft_itoa(int n);

/*
** BONUS PART
*/

typedef struct s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

t_list	*ft_lstnew(const void *content, size_t content_size);
t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void	ft_lstiter(t_list *lst, void (*f)(t_list *elem));
void	ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void	ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void	ft_lstadd(t_list **alst, t_list *new);

/*
** EXTRA
*/

int		ft_toinverse(int c);
int		ft_isspace(int c);
int		ft_islower(int c);
int		ft_isupper(int c);
int		ft_isxdigit(int c);
int		ft_strchr_equ(const char *s, int c);

t_uint	ft_abs(int n);
int		ft_log10(int n);
int		ft_pow(int n, int pow);

size_t	ft_wordcount(const char *s, const char *del);
int		*ft_mapi(int start, int end);
char	*ft_strword(const char *s, const char *delim, size_t *lenout);
void	*ft_memdup(const void *s1, size_t len);

void	ft_swap(char *a, char *b, size_t bs);
void	ft_memswap(char *a, char *b, size_t len);
void	ft_aiter(void **array, size_t len, void (*fn)(void **));
void	ft_freearray(void ***array, size_t len);
void	ft_sort_bubble(void *tab, size_t len,
			int (*cmpf)(void **, void **), size_t bs);

void	ft_memclr(void *ap, size_t size);

size_t	ft_lstlen(t_list *lst);
size_t	ft_lstclen(t_list *lst, t_list *target);
size_t	ft_lstbuflen(t_list *lst);
t_list	*ft_lstn(t_list *lst, size_t n);

t_list	*ft_lstinit(size_t elemc, size_t size);
char	*ft_lststr(t_list *lst);
int		ft_lstcut(t_list **alst, size_t start, size_t count,
			void (*del)(void *, size_t));

#endif
