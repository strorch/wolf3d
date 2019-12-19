/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 19:53:44 by mstorcha          #+#    #+#             */
/*   Updated: 2019/10/19 19:53:46 by mstorcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static int		str_array_size(char **array)
{
	int i;

	if (!array)
		return (0);
	i = -1;
	while (array[++i] != 0)
		;
	return (i);
}

static char		**set_line_arr(const char *str, int sz_alloc)
{
	char	**split;

	if (!(split = ft_strsplit(str, ' ')))
		return (NULL);
	if (str_array_size(split) != (int)sz_alloc)
		exit_message("Wrong map sizes");
	return (split);
}

t_vec			*get_map_size(const int fd)
{
	t_vec	*size;
	char	*size_str;
	char	**splitted_size;
	int		res;

	res = ft_get_next_line(fd, &size_str);
	if (res == -1)
		return (NULL);
	splitted_size = ft_strsplit(size_str, ' ');
	ft_memdel((void **)&size_str);
	if (!(size = (t_vec *)ft_memalloc(sizeof(t_vec))))
	{
		ft_del_str(splitted_size);
		return (NULL);
	}
	if (str_array_size(splitted_size) != 2)
		exit_message("Wrong map sizes");
	size->x = ft_atoi(splitted_size[0]);
	size->y = ft_atoi(splitted_size[1]);
	if (size->x < 3 || size->y < 3)
		exit_message("Wrong map sizes");
	ft_del_str(splitted_size);
	return (size);
}

char			***readf(int fd, t_vec *map_sz)
{
	int		i;
	char	*str;
	char	***res;
	int		res_fd;

	i = -1;
	if (!(res = (char ***)ft_memalloc(sizeof(char **) * map_sz->x)))
		return (NULL);
	while (++i < map_sz->x)
	{
		res_fd = ft_get_next_line(fd, &str);
		if (res_fd == 0)
			break ;
		else if ((res_fd == -1)
				|| !(res[i] = set_line_arr(str, (int)map_sz->y)))
		{
			ft_memdel((void **)&str);
			return (NULL);
		}
		ft_memdel((void **)&str);
	}
	if (map_sz->x != i)
		exit_message("Alloc error");
	return (res);
}
