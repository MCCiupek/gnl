/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcciupek <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 11:47:34 by mcciupek          #+#    #+#             */
/*   Updated: 2020/12/18 15:57:17 by mcciupek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

typedef struct		s_line
{
	int		count;
	char	*txt;
}					t_line;

int					get_next_line(int fd, char **line);
int					ft_strlen(char *str);
size_t				ft_strlcpy(char *dest, char *src, size_t size);
char				*ft_strldup(char *src, size_t size);
char				*ft_strjoin(char *s1, char *s2);

#endif
