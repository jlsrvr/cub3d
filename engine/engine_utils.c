////header///

#include "engine.h"

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char    *pixel;
	int		pix_pos;
	int		i;

	i = img->bpp - 8;
	pix_pos = y * img->line_len + x * (img->bpp / 8);
	pixel = img->addr + pix_pos;
	while (i >= 0)
	{
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

void render_rect(t_img *img, t_rect rect)
{
	int	i;
	int j;

	i = rect.y;
	while (i < rect.y + rect.height)
	{
		j = rect.x;
		while (j < rect.x + rect.width)
			img_pix_put(img, j++, i, rect.color);
		++i;
	}
}

