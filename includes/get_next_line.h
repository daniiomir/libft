/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swarner <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 21:06:53 by swarner           #+#    #+#             */
/*   Updated: 2019/04/21 21:06:58 by swarner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 10000

typedef struct	s_file
{
	int				len;
	char			*buf;
	char			*start;
	char			*end;
}				t_file;

typedef struct	s_vector
{
	t_file	**array;
	int		size;
}				t_vector;

int				get_next_line(const int fd, char **line);

#endif
