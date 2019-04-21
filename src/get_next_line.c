/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swarner <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 21:06:28 by swarner           #+#    #+#             */
/*   Updated: 2019/04/21 21:06:32 by swarner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"

static void		file_init(t_file *file)
{
	ft_bzero(file->buf, BUFF_SIZE + 1);
	file->len = BUFF_SIZE;
	file->start = NULL;
	file->end = NULL;
}

static int		vec_init(t_vector *vec, int fd)
{
	t_vector	tmp;
	int			i;

	if (fd >= vec->size)
	{
		tmp = *vec;
		vec->size = fd + 1;
		if (!(vec->array = (t_file **)malloc(sizeof(t_file *) * vec->size)))
			return (-1);
		i = -1;
		while (++i < vec->size)
			vec->array[i] = i < tmp.size ? tmp.array[i] : NULL;
		free(tmp.array);
	}
	if (vec->array[fd] == NULL)
	{
		if (!(vec->array[fd] = (t_file *)malloc(sizeof(t_file))) ||
		!(vec->array[fd]->buf = (char *)malloc(sizeof(char) * BUFF_SIZE + 1)))
			return (-1);
		file_init(vec->array[fd]);
	}
	return (0);
}

static int		get_line(char **line, t_file *file, int fd)
{
	if (file->start && file->start - file->buf > file->len)
		file->start = NULL;
	if ((file->end = ft_strchr(file->start, '\n')))
		*file->end = '\0';
	if (!(*line = ft_strdup(file->start)))
		return (-1);
	while (file->len == BUFF_SIZE && !file->end)
	{
		if ((file->len = read(fd, file->buf, BUFF_SIZE)) == -1)
			return (-1);
		*(file->buf + file->len) = '\0';
		if ((file->end = ft_strchr(file->buf, '\n')))
			*file->end = '\0';
		if (!(*line = ft_rejoin(*line, file->buf)))
			return (-1);
	}
	file->start = file->buf;
	file->end ? file->start = file->end + 1 : ft_bzero(file->buf, BUFF_SIZE);
	if (!file->end && !(**line))
		ft_strdel(line);
	if (file->len < BUFF_SIZE && !file->end)
		file_init(file);
	return (*line ? 1 : 0);
}

static void		gnl_free(t_vector *vec)
{
	int		i;

	i = -1;
	while (++i < vec->size)
		if (vec->array[i])
		{
			if (vec->array[i]->buf)
			{
				free(vec->array[i]->buf);
				vec->array[i]->buf = NULL;
			}
			free(vec->array[i]);
			vec->array[i] = NULL;
		}
	if (vec->array)
	{
		free(vec->array);
		vec->array = NULL;
		vec->size = 0;
	}
}

int				get_next_line(const int fd, char **line)
{
	int				res;
	static t_vector	vec = {NULL, 0};

	if (!line)
	{
		gnl_free(&vec);
		return (-1);
	}
	if ((read(fd, 0, 0)) == -1 || BUFF_SIZE < 1)
		return (-1);
	if (!(res = vec_init(&vec, fd)))
		res = get_line(line, vec.array[fd], fd);
	if (res == -1 && vec.array)
	{
		if (vec.array[fd])
		{
			if (vec.array[fd]->buf)
				free(vec.array[fd]->buf);
			vec.array[fd]->buf = NULL;
			free(vec.array[fd]);
			vec.array[fd] = NULL;
		}
		return (-1);
	}
	return (res);
}
