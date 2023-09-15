/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akazuki <akazuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 16:28:19 by akazuki           #+#    #+#             */
/*   Updated: 2023/09/15 11:03:04 by akazuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_free(char **str)
{
	free(*str);
	*str = NULL;
	return (NULL);
}

static void	ft_save_set(char *line, char *save)
{
	size_t	count;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	count = ft_strlen_c(line, '\n');
	while (count-- > 0)
		i++;
	while (line[i] != '\0')
	{
		save[j] = line[i];
		i++;
		j++;
	}
	save[j] = '\0';
}

static char	*ft_save(char *line, char *save)
{
	char	*keep;
	size_t	count;
	size_t	i;

	i = 0;
	count = ft_strlen_c(line, '\n');
	keep = ft_calloc(count + 1, 1);
	if (!keep)
		return (ft_free(&line));
	while (count > 0)
	{
		keep[i] = line[i];
		i++;
		count--;
	}
	keep[i] = '\0';
	ft_save_set(line, save);
	ft_free(&line);
	return (keep);
}

static char	*ft_line_set(char *save, char *line, int fd)
{
	ssize_t	size;
	char	*tmp;

	size = 1;
	while (ft_strchr(save, '\n') != 1 && size != 0 && size != -1)
	{
		size = read(fd, (void *)save, BUFFER_SIZE);
		save[size] = '\0';
		if (size == -1)
			return (ft_free(&line));
		tmp = ft_strjoin(line, save);
		ft_free(&line);
		if (!tmp)
			return (NULL);
		line = tmp;
	}
	if (size == 0 && line[0] == '\0')
		return (ft_free(&line));
	else if (size == 0 && ft_strchr(line, '\n') != 1)
		return (line);
	else
		return (ft_save(line, save));
}

char	*get_next_line(int fd)
{
	static char	save[BUFFER_SIZE + 1];
	char		*line;
	char		*tmp;

	line = ft_calloc(1, 1);
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (ft_free(&line));
	if (save[0] != '\0')
	{
		tmp = ft_strjoin(line, save);
		ft_free(&line);
		if (!tmp)
			return (NULL);
		line = tmp;
	}
	return (ft_line_set(save, line, fd));
}

// int	main(void)
// {
// 	int	fd;
// 	fd = open("./test.txt",O_RDONLY);
// 	printf("%s",get_next_line(fd));
// 	// puts("------------------");
// 	// printf("%s",get_next_line(fd));
// 	close(fd);
// }
// int main(int argc, char const *argv[])
// {
// 	char	*str;
// 	int		fd;

// 	if (argc == 1)
// 		fd = 0;
// 	else
// 	{
// 		fd = open(argv[1], O_RDONLY);
// 		if (fd == -1)
// 			return (1);
// 	}
// 	while (1)
// 	{
// 		str = get_next_line(fd);
// 		printf("%s", str);
// 		if (!str)
// 			break ;
// 		free(str);
// 	}
// 	close(fd);
// 	// system("leaks -q a.out");
// 	return 0;
// }
