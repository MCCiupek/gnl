/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mciupek <mciupek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 14:06:02 by mciupek           #+#    #+#             */
/*   Updated: 2020/12/16 13:56:02 by mciupek          ###   ########.fr       */
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
		nl->txt = ft_strjoin(tmp, buff);
		free(tmp);
	}
	if (ret < 0)
		return (-1);
	return (ret);
}

int			reset_struct(t_line *nl, int b_reset_line, char **line, int ret_val)
{
	if (b_reset_line)
	{
		if (!(*line = (char *)malloc(sizeof(char *) * 1)))
			return (-1);
		*(line[0]) = '\0';
	}
	nl->txt = NULL;
	nl->count = 0;
	free(nl->txt);
	return (ret_val);
}

int			get_next_line(int fd, char **line)
{
	static t_line	nl;
	int				i;

	if (!fd || fd < 0 || !line)
		return (-1);
	if (!nl.count++)
		if (ft_read_line(&nl, fd) == -1)
			return (reset_struct(&nl, 0, line, -1));
	i = -1;
	if (!nl.txt)
		return (reset_struct(&nl, 1, line, 0));
	while (*(nl.txt + ++i))
		if (*(nl.txt + i) == '\n')
			break ;
	if (!*(nl.txt + i))
		nl.count = -1;
	if (nl.count == -1 && !i)
		return (reset_struct(&nl, 1, line, 0));
	if (!(*line = ft_strldup(nl.txt, i, 0)))
		return (-1);
	if (!(nl.txt = ft_strldup(nl.txt + i + 1, ft_strlen(nl.txt) - i - 1, 0)))
		return (-1);
	if (nl.count == -1)
		return (reset_struct(&nl, 0, line, 0));
	return (1);
}
