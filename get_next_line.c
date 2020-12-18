/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcciupek <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 18:02:09 by mcciupek          #+#    #+#             */
/*   Updated: 2020/12/18 15:18:28 by mcciupek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "get_next_line.h"

static int	ft_err(int fd, char *buf, char **line)
{
	int	ret;

	ret = read(fd, buf, BUFFER_SIZE);
	if (fd < 0 || !line || BUFFER_SIZE < 1 || ret < 0)
		return (-1);
	return (ret);
}

static int	ft_read(int fd, char *buf, t_line *nl)
{
	char	*tmp;
	int	ret;

	if (!(nl->txt = ft_strldup(buf, ft_strlen(buf))))
		return (-1);
	while ((ret = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[ret] = 0;
		if (!(tmp = ft_strjoin(nl->txt, buf)))
			return (-1);
		free(nl->txt);
		if (!(nl->txt = ft_strldup(tmp, ft_strlen(tmp))))
			return (-1);
		free(tmp);
	}
	if (ret < 0)
		return (-1);
	return (ret);
}

static int	ft_reset(t_line *nl, char **line, int b_line, int ret_val)
{
	if (b_line)
	{
		if (!(*line = (char *)malloc(sizeof(char) * 1)))
			ret_val = -1;
		else
			*(line[0]) = 0;
	}
	nl->count = 0;
	free(nl->txt);
	return (ret_val);
}

static int	ft_stock(t_line *nl, char **line)
{
	int	i;
	int	eof;
	char	c;
	char	*tmp;

	i = -1;
	eof = 1;
	while (nl->txt && (c = *(nl->txt + ++i)))
		if (c == '\n')
			break ;
	if (c == '\n')
		eof = 0;
	if (!(*line = ft_strldup(nl->txt, i)))
		return (-1);
	if (!eof)
	{
		if (!(tmp = ft_strldup(nl->txt + i + 1, ft_strlen(nl->txt) - i - 1)))
			return (-1);
		free(nl->txt);
		if (!(nl->txt = ft_strldup(tmp, ft_strlen(tmp))))
			return (-1);
		free(tmp);
	}
	return (eof == 0);
}

int		get_next_line(int fd, char **line)
{
	char			buf[BUFFER_SIZE + 1];
	static t_line	nl;
	int			err;

	if ((err = ft_err(fd, buf, line)) == -1)
		return (-1);
	buf[err] = 0;
	if (!nl.count++)
		err = ft_read(fd, buf, &nl);
	if (err == -1)
		return (ft_reset(&nl, line, 1, -1));
	err = ft_stock(&nl, line);
	if (!err)
		ft_reset(&nl, line, 0, err);
	return (err);
}
