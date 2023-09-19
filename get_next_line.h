#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

char    *get_next_line(int fd);
char    *ft_read(int fd, char *buffer);
char	*ft_write_line(char *line, char *buffer);
void    ft_shiftmem(char *buffer, size_t len);
char    *ft_realloc(char *ptr, size_t size);
void    ft_strcat(char *dst, char *src);
int		ft_strchr(const char *s, int c);

#endif
