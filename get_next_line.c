/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcciupek <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 18:02:09 by mcciupek          #+#    #+#             */
/*   Updated: 2020/12/21 10:12:00 by mciupek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
#include <string.h>
#include "get_next_line.h"

static int	ft_err(int fd, char *buf, char **line)
{
	int	ret;

	ret = read(fd, buf, BUFFER_SIZE);
	buf[ret] = 0;
	if (fd < 0 || !line || BUFFER_SIZE < 1 || ret == -1)
	{
		//printf("je free buf\n");
		free(buf);
		return (-1);
	}
	return (ret);
}

static int	ft_read(int fd, char *buf, t_line *nl, int ret)
{
	char	*tmp;

	while (ret >= 0)
	{
		if (!(tmp = ft_strjoin(nl->txt, buf)))
			return (-1);
		//printf("je malloc tmp\n");
		if (nl->count > 1)
		{
		//	printf("je free nl->txt dans ft_read\n");
			free(nl->txt);
		}
		if (!(nl->txt = ft_strldup(tmp, ft_strlen(tmp))))
			return (-1);
		//printf("je malloc nl->txt\n");
		//printf("je free tmp\n");
		free(tmp);
		if (ft_strchr(buf, '\n') || !ret)
			break ;
		ret = read(fd, buf, BUFFER_SIZE);
		buf[ret] = 0;
	}

	//printf("je free buf\n");
	free(buf);
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
		{
	//		printf("je malloc line\n");
			*(line[0]) = 0;
		}
	}
	//printf("je free nl->txt\n");
	free(nl->txt);
	nl->count = 0;
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
	//printf("je malloc line\n");
	if (!eof)
	{
		if (!(tmp = ft_strldup(nl->txt + i + 1, ft_strlen(nl->txt) - i - 1)))
			return (-1);
	//	printf("je malloc tmp\n");
	//	printf("je free nl->txt\n");
		free(nl->txt);
		if (!(nl->txt = ft_strldup(tmp, ft_strlen(tmp))))
			return (-1);
	//	printf("je malloc nl->txt\n");
	//	printf("je free tmp\n");
		free(tmp);
	}
	return (eof == 0);
}

int		get_next_line(int fd, char **line)
{
	char			*buf;
	static t_line	nl;
	int			err;

	if (nl.count++ == 0)
		nl.txt = NULL;
	if (!(buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	//printf("je malloc buf\n");
	if ((err = ft_err(fd, buf, line)) == -1)
		return (-1);
	if ((err = ft_read(fd, buf, &nl, err)) == -1)
		return (ft_reset(&nl, line, 1, -1));
	if (!(err = ft_stock(&nl, line)))
		ft_reset(&nl, line, 0, err);
	return (err);
}
