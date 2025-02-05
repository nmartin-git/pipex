/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:00:14 by nmartin           #+#    #+#             */
/*   Updated: 2025/01/30 22:34:24 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H

# define LIBFT_H
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

/*--LIBFT--*/

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
size_t	ft_strlen(const char *s);
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t siz);
size_t	ft_strlcat(char *dst, const char *src, size_t siz);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
int		ft_atoi(const char *nptr);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/*--PRINTF--*/

void	ftp_c_null(const char *bns, t_list **rlst);
void	ftp_put_spaces(int is_minus, t_list **rlst, char *width);
void	ftp_str_error(t_list **rlst);
void	ftp_del(void *content);

char	*ftp_b_str_dot(const char *bns, char *str, int null);
int		ftp_b_dot_b(const char *str);
char	*ftp_b_is_dot_nb(const char *bns, char *str, int is_zero);
int		ftp_is_bonus(const char *str);
int		ftp_b_check(char c, const char *str);
int		ftp_b_check_d(const char *str);
char	*ftp_b_is_digit(const char *bns, char *str);
int		ftp_b_digit(const char *bns);
int		ftp_hashtag(const char *b);
void	ftp_b_hashtag(const char *bns, char *str, unsigned int nb);
char	*ftp_b_is_zero(const char *bns, char *str, int dot);

int		ft_printf(const char *str, ...);

int		ftp_printer(char *str, int fd);
int		ftp_print_result(t_list *lst, int fd);
int		ftp_print_txt(const char *str, t_list **rlst);
void	ftp_check_char(const char *str, va_list lst, t_list **rlst);

int		ftp_printf_conv(const char *str, va_list lst, t_list **rlst);

int		ftp_hlen(unsigned long long nbr);
int		ftp_ilen(long long nb);
int		ftp_hex_p(char *str, unsigned long long nb, int is_bns, t_list **rlst);
void	ftp_nbr_p(char *str, long long nb, int bn);
void	ftp_str_upper(char *str);

void	ftp_c(char c, const char *bns, t_list **rlst);
void	ftp_s(char *str, const char *bns, t_list **rlst);
void	ftp_p(unsigned long long ptr, const char *bns, t_list **rlst);
void	ftp_i(int nb, const char *bns, t_list **rlst);
void	ftp_x(unsigned long long nb, int up, const char *bns, t_list **rlst);
void	ftp_u(unsigned int nb, const char *bns, t_list **rlst);
void	ftp_percent(t_list **rlst);

/*--GNL--*/

char	*get_next_line(int fd);
void	*gnl_calloc(size_t nmemb, size_t size);
void	gnl_bzero(void *s, size_t n);
t_list	*gnl_lstnew(char *content);
int		gnl_nl_chr(char *str, size_t len);
int		gnl_str_lst_len(t_list *lst);

/*--Utils added--*/

void	ft_free_tab(char **tab);
int		ft_printf_fd(int fd, const char *str, ...);
int		ft_size_tab(char **tab);

#endif
