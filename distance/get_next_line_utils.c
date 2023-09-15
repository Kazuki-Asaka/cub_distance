/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akazuki <akazuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 16:28:24 by akazuki           #+#    #+#             */
/*   Updated: 2023/01/25 19:54:00 by akazuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_c(const char *str, char c)
{
	size_t	count;

	count = 0;
	while (*str != c)
	{
		count++;
		str++;
	}
	if (c == '\n')
		count++;
	return (count);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;

	if (count == 0 || size == 0)
	{
		count = 1;
		size = 1;
	}
	if (SIZE_MAX / count < size)
		return (NULL);
	p = malloc(count * size);
	if (p == NULL)
		return (NULL);
	ft_bzero(p, count * size);
	return (p);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*tmp;
	char	*tmpsave;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	tmp = malloc (sizeof(char) * (ft_strlen_c(s1, '\0') + \
	ft_strlen_c(s2, '\0')) + 1);
	if (tmp == NULL)
		return (NULL);
	tmpsave = tmp;
	while (*s1 != '\0')
		*tmp++ = *s1++;
	while (*s2 != '\0')
		*tmp++ = *s2++;
	*tmp = '\0';
	return (tmpsave);
}

int	ft_strchr(const char *s, int c)
{
	if ((char)c == '\0')
	{
		while (*s != '\0')
			s++;
		return (1);
	}
	if (*s != '\0')
	{
		while (*s != '\0')
		{
			if (*s == (char)c)
				return (1);
			else
				s++;
		}
		return (0);
	}
	else
		return (0);
}

void	ft_bzero(void	*s, size_t	n)
{
	size_t	i;
	char	*tmp;

	i = 1;
	tmp = s;
	while (i <= n)
	{
		*tmp = '\0';
		tmp++;
		i++;
	}
}
