/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 20:45:08 by mstorcha          #+#    #+#             */
/*   Updated: 2019/10/23 20:45:10 by mstorcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void	init_pix_in_textures(int ***texture_h, int i, int y)
{
	int xorcolor;
	int ycolor;
	int xycolor;
	int **t;

	t = *texture_h;
	xorcolor = (i * 256 / T_WIDTH) ^ (y * 256 / T_HEIGHT);
	ycolor = y * 256 / T_HEIGHT;
	xycolor = y * 128 / T_HEIGHT + i * 128 / T_WIDTH;
	t[0][T_WIDTH * y + i] = 65536 * 254 * (i != y && i != T_WIDTH - y);
	t[1][T_WIDTH * y + i] = xycolor + 256 * xycolor + 65536 * xycolor;
	t[2][T_WIDTH * y + i] = 256 * xycolor + 65536 * xycolor;
	t[3][T_WIDTH * y + i] = xorcolor + 256 * xorcolor + 65536 * xorcolor;
	t[4][T_WIDTH * y + i] = 256 * xorcolor;
	t[5][T_WIDTH * y + i] = 65536 * 192 * (i % 16 && y % 16);
	t[6][T_WIDTH * y + i] = 65536 * ycolor;
	t[7][T_WIDTH * y + i] = 128 + 256 * 128 + 65536 * 128;
}

int			**get_textures(void)
{
	int y;
	int i;
	int **t;

	if (!(t = (int **)ft_memalloc(sizeof(int *) * 8)))
		;
	i = -1;
	while (++i < 8)
		if (!(t[i] = (int *)ft_memalloc(T_WIDTH * T_HEIGHT * sizeof(int))))
			return (NULL);
	i = -1;
	while (++i < T_WIDTH)
	{
		y = -1;
		while (++y < T_HEIGHT)
			init_pix_in_textures(&t, i, y);
	}
	return (t);
}
