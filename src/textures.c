#include "wolf.h"

int		**get_textures(void)
{
	int **texture = (int **)ft_memalloc(sizeof(int *) * 8);
	for (int i = 0; i < 8; i++) {
		texture[i] = (int *)ft_memalloc(sizeof(int) * texWidth * texHeight);
	}

	for(int x = 0; x < texWidth; x++)
		for(int y = 0; y < texHeight; y++)
		{
			int xorcolor = (x * 256 / texWidth) ^ (y * 256 / texHeight);
			int ycolor = y * 256 / texHeight;
			int xycolor = y * 128 / texHeight + x * 128 / texWidth;
			texture[0][texWidth * y + x] = 65536 * 254 * (x != y && x != texWidth - y);
			texture[1][texWidth * y + x] = xycolor + 256 * xycolor + 65536 * xycolor;
			texture[2][texWidth * y + x] = 256 * xycolor + 65536 * xycolor;
			texture[3][texWidth * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor;
			texture[4][texWidth * y + x] = 256 * xorcolor;
			texture[5][texWidth * y + x] = 65536 * 192 * (x % 16 && y % 16);
			texture[6][texWidth * y + x] = 65536 * ycolor;
			texture[7][texWidth * y + x] = 128 + 256 * 128 + 65536 * 128;
		}
	return texture;
}
