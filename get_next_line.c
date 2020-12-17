/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mciupek <mciupek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 14:06:02 by mciupek           #+#    #+#             */
/*   Updated: 2020/12/17 13:51:00 by mcciupek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_read_line(t_line *nl, int fd)
{
	char		buff[BUFFER_SIZE + 1];
	char		*tmp;
	int			ret;

	while ((ret = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[ret] = '\0';
		tmp = nl->txt;
		nl->txt = NULL;
		free(nl->txt);
		nl->txt = ft_strjoin(tmp, buff);
		free(tmp);
	}
	if (ret < 0)
		return (-1);
	return (ret);
}

static int	reset_line(char **line)
{
	if (!(*line = (char *)malloc(sizeof(char) * 1)))
		return (-1);
	*(line[0]) = '\0';
	return (0);
}

static int	reset_struct(t_line *nl, int b, char **line, int ret_val)
{
	if (b < 1)
		ret_val = reset_line(line);
	nl->txt = NULL;
	nl->count = 0;
	free(nl->txt);
	return (ret_val);
}

static int	stock_line(t_line *nl, char **line, int i)
{
	char		*tmp;

	tmp = nl->txt;
	if (!(*line = ft_strldup(tmp, i)))
		return (-1);
	tmp = nl->txt + i + 1;
	nl->txt = NULL;
	free(nl->txt);
	if (!(nl->txt = ft_strldup(tmp, ft_strlen(tmp))))
		return (-1);
	return (0);
}

int			get_next_line(int fd, char **line)
{
	static t_line	nl;
	int				i;
	int				eof;

	if (fd < 0 || !line || BUFFER_SIZE < 1)
		return (-1);
	if (!nl.count++)
		if (ft_read_line(&nl, fd) == -1)
			return (reset_struct(&nl, 0, line, -1));
	i = -1;
	eof = 1;
	while (nl.txt && *(nl.txt + ++i))
	{
		if (*(nl.txt + i) == '\n')
		{
			eof = 0;
			break ;
		}
	}
	if (!eof || i > 0)
		if (stock_line(&nl, line, i) == -1)
			return (-1);
	if (eof)
		return (reset_struct(&nl, i, line, 0));
	return (1);
}
