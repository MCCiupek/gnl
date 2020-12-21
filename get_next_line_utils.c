/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcciupek <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 11:52:40 by mcciupek          #+#    #+#             */
/*   Updated: 2020/12/21 10:57:58 by mciupek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dest, char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (!dest || !src)
		return (0);
	while (i < size)
	{
		if (!src[i])
		{
			dest[i] = '\0';
			break ;
		}
		if (i == size - 1)
		{
			dest[i] = '\0';
			break ;
		}
		dest[i] = src[i];
		i++;
	}
	return (i);
}

char	*ft_strldup(char *src, size_t size)
{
	char	*tab;

	tab = (char *)malloc(sizeof(char) * (size + 1));
	if (tab)
	{
		ft_strlcpy(tab, src, size + 1);
		return (tab);
	}
	return (NULL);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*tab;
	size_t	l1;
	size_t	l2;

	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	if ((tab = (char *)malloc(sizeof(char) * (l1 + l2 + 1))))
	{
		ft_strlcpy(tab, s1, l1 + 1);
		ft_strlcpy(tab + l1, s2, l2 + 1);
		return (tab);
	}
	return (NULL);
}

int		ft_strchr(char *str, int ch)
{
	int	i;

	i = -1;
	if (!str)
		return (0);
	while (str[++i])
		if (str[i] == ch)
			return (1);
	return (0);
}
