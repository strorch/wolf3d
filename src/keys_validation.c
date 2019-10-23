/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 20:44:44 by mstorcha          #+#    #+#             */
/*   Updated: 2019/10/23 20:44:45 by mstorcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static int		check_items(char *item)
{
	int			i;
	int			tmp;
	const char	*valid_keys[ITEMS_NUM];

	valid_keys[0] = "0";
	valid_keys[1] = "1";
	valid_keys[2] = "2";
	valid_keys[3] = "3";
	valid_keys[4] = "4";
	valid_keys[5] = "5";
	valid_keys[6] = "6";
	valid_keys[7] = "7";
	valid_keys[8] = "8";
	valid_keys[9] = "U";
	i = -1;
	tmp = 0;
	while (++i < ITEMS_NUM)
		if (!ft_strcmp(valid_keys[i], item))
			tmp = 1;
	return (tmp);
}

static int		check_border_item(char *item)
{
	return (!ft_strcmp(item, "0") || !ft_strcmp(item, "U"));
}

int				keys_validation(char ***map, t_vec *map_sz)
{
	int i;
	int j;

	i = -1;
	while (++i < map_sz->x)
		if (check_border_item(map[i][0])
			|| check_border_item(map[i][(int)map_sz->y - 1]))
			return (0);
	i = -1;
	while (++i < map_sz->y)
		if (check_border_item(map[(int)map_sz->x - 1][i])
			|| check_border_item(map[0][i]))
			return (0);
	i = -1;
	j = -1;
	while (++i < map_sz->x)
	{
		j = -1;
		while (++j < map_sz->y)
			if (!check_items(map[i][j]))
				return (0);
	}
	return (1);
}
