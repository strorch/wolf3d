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
	int **texture;

	texture = *texture_h;
	xorcolor = (i * 256 / texWidth) ^ (y * 256 / texHeight);
	ycolor = y * 256 / texHeight;
	xycolor = y * 128 / texHeight + i * 128 / texWidth;
	texture[0][texWidth * y + i] = 65536 * 254 * (i != y && i != texWidth - y);
	texture[1][texWidth * y + i] = xycolor + 256 * xycolor + 65536 * xycolor;
	texture[2][texWidth * y + i] = 256 * xycolor + 65536 * xycolor;
	texture[3][texWidth * y + i] = xorcolor + 256 * xorcolor + 65536 * xorcolor;
	texture[4][texWidth * y + i] = 256 * xorcolor;
	texture[5][texWidth * y + i] = 65536 * 192 * (i % 16 && y % 16);
	texture[6][texWidth * y + i] = 65536 * ycolor;
	texture[7][texWidth * y + i] = 128 + 256 * 128 + 65536 * 128;
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
		if (!(t[i] = (int *)ft_memalloc(texWidth * texHeight * sizeof(int))))
			;
	i = -1;
	while (++i < texWidth)
	{
		y = -1;
		while (++y < texHeight)
			init_pix_in_textures(&t, i, y);
	}
	return (t);
}
