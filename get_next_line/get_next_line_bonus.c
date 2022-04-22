/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkasmi <abkasmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 11:10:22 by abkasmi           #+#    #+#             */
/*   Updated: 2021/10/27 11:14:47 by abkasmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	int			ret;
	static char	*str[OPEN_MAX];
	char		*buff;
	int			pos;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	pos = ft_strchr(str[fd]);
	buff = NULL;
	while (pos == -1)
	{
		buff = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (!buff)
			return (NULL);
		ret = read(fd, buff, BUFFER_SIZE);
		if (ret <= 0)
		{
			ft_free(&buff);
			break ;
		}
		str[fd] = ft_strnjoin(str[fd], buff, ret);
		pos = ft_strchr(str[fd]);
		ft_free(&buff);
	}
	return (return_value(&str[fd], pos, ret));
}

char	*return_value(char **str, int pos, int ret)
{
	char	*str2;

	if (!*str && ret <= 0)
		return (NULL);
	str2 = NULL;
	if (pos == -1)
		pos = ft_strlen(*str);
	else
		pos++;
	str2 = ft_strndup(*str, pos);
	if (pos == ft_strlen(*str))
		ft_free(str);
	else
	{
		*str = ft_get_after_nl(str, pos);
	}
	return (str2);
}

char	*ft_strndup(char *s1, int n)
{
	char	*ptr;
	int		i;

	ptr = malloc(sizeof(char) * (n + 1));
	if (!ptr)
		return (NULL);
	i = -1;
	while (++i < n)
		ptr[i] = s1[i];
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_get_after_nl(char **str, int pos)
{
	char	*str2;

	str2 = ft_strndup(&(*str)[pos], ft_strlen(*str) - pos);
	ft_free(str);
	*str = str2;
	return (*str);
}

void	ft_free(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
}
