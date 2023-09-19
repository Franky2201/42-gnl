#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

#include "get_next_line.h"

char    *ft_realloc(char *ptr, size_t size)
{
    char    *new;
    size_t  i;

    i = 0;
    new = (char *)malloc(size + 1);
    if (!new)
        return (NULL);
    if (ptr)
	{
		while (ptr[i])
    	{
    	    new[i] = ptr[i];
    	    i++;
    	}
    	new[i] = '\0';
    	free(ptr);
	}
    return (new);
}

void    ft_strcat(char *dst, char *src)
{
    size_t  i;
    size_t  j;

	if (!dst || !src)
		return ;
    i = 0;
    while (dst[i])
        i++;
    j = 0;
    while (src[j])
    {
        dst[i + j] = src[j];
        src[j] = '\0';
        j++;
    }
    dst[i + j] = '\0';
    free(src);
    return ;
}

int	ft_strchr(const char *s, int c)
{
	while (*s || (char)c == 0)
	{
		if (*s == (char)c)
			return (1);
		s++;
	}
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char    *ft_read(int fd, char *buffer)
{
	char	*temp;
    ssize_t i;
	size_t	len;

    temp = (char *)malloc(BUFFER_SIZE + 1);
    if (!temp)
        return (NULL);
    i = 1;
	len = ft_strlen(buffer);
    while (i > 0)
    {
        i = read(fd, temp, BUFFER_SIZE);
        if (i == -1)
        {
            free(temp);
            return (NULL);
        }
		if (i)
		{
        	temp[i] = '\0';
			len += i;
			buffer = ft_realloc(buffer, len);
			ft_strcat(buffer, temp);
        	if (ft_strchr(buffer, '\n'))
        	    i = 0;
		}
		else
			free(temp);
    }
    return (buffer);
}

char	*ft_write_line(char *line, char *buffer)
{
	size_t	len;
	size_t	i;

	len = 0;
	while (buffer[len] && buffer[len] != '\n')
		len++;
	line = (char *)malloc(len + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (i < len)
	{
		line[i] = buffer[i];
		i++;
	}
	line[i] = '\0';
	ft_shiftmem(buffer, len);
	return (line);
}

void	ft_shiftmem(char *buffer, size_t len)
{
	size_t	i;

	i = 0;
	if (buffer[len] == '\n')
		len++;
	while (buffer[len])
	{
		buffer[i] = buffer[len];
		i++;
		len++;
	}
	buffer[i] = '\0';
}

char    *get_next_line(int fd)
{
	static char	*buffers[4096];
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, 0, 0) < 0)
        return (NULL);
	buffers[fd] = ft_read(fd, buffers[fd]);
	if (!buffers[fd] || !buffers[fd][0])
		return (NULL);
	//printf("$%s$\n", buffers[fd]);
	//printf("%i", fd);
	line = ft_write_line(NULL, buffers[fd]);
	//printf("$%s$\n", buffers[fd]);
	return (line);
}
/*
int main(int argc, char **argv)
{
    int fd, line_count;
    char *line;
	int	i;

	(void)line_count;
    line_count = 1;
    line = NULL;
    if (argc == 2)
    {
        line = argv[1];
        fd = open(line, O_RDONLY);
        line = get_next_line(fd);
		i = 0;
        while (i < 5)
        {
            printf("\n [ Return: ] | A line has been read #%d => $%s$\n", line_count, line);
            line_count++;
            free(line);
            line = get_next_line(fd);
			i++;
        }
        printf("\n [ Return: ] A line has been read #%d: $%s$\n", line_count++, line);
        printf("\n");
        if (!line)
        {
            printf("-----------\n EOF has been reached\n");
            free(line);
        }
        close(fd);
    }
}*/

int	main(int ac, char *av[])
{
	if (ac < 2)
		return (0);

	int n = 1;
	int i = 1;
	char *print;
	while (av[n + 1])
		n++;
	int fd[n];
	while (n-- > 0)
	{
		fd[n] = open(av[n], O_RDONLY);
	}
	n = ac - 1;
	while (n)
	{
		printf("\n\t\t{%s}", av[n]);
		printf("[%i]\n", fd[n - 1]);
		while (i)
		{
			print = get_next_line(fd[n - 1]);
			printf(">>>|%s|<<<\n", print);
			if (!print)
				i = 0;
			else
				free (print);
		}
		close(fd[n - 1]);
		n--;
	}
	printf("\n\n\n");
	system("Leaks a.out");
}
