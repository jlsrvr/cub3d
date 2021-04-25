#include "engine.h"

static void	sort_sprites(int *order, double *dist, int amount)
{
	int		index;
	int		icomp;
	int		temp_order;
	double	temp_dist;

	index = -1;
	while (++index < amount)
	{
		icomp = index;
		while (++icomp < amount)
			if (dist[index] < dist[icomp])
			{
				temp_order = order[index];
				temp_dist = dist[index];
				order[index] = order[icomp];
				dist[index] = dist[icomp];
				order[icomp] = temp_order;
				dist[icomp] = temp_dist;
			}
	}
}

typedef struct	s_draw_sprite_vars
{
	double	sprite_x;
	double	sprite_y;
	double	inv_det;
	double	transform_x;
	double	transform_y;
	int		sprite_screen_x;
	int		sprite_height;
	int		sprite_width;
	int		draw_start_y;
	int		draw_end_y;
	int		draw_start_x;
	int		draw_end_x;
	int		stripe;
	int		tex_x;
	int		tex_y;
	int		y;
	int		d;
	int		colour;

}				t_draw_sprite_vars;

int	init_sprite_order(t_data *data, int **sprite_order, double **sprite_dist)
{
	int index;
	double pos_x;
	double pos_y;
	t_sprite sprite;

	*sprite_order = malloc(sizeof(**sprite_order) * data->desc->sprite_cnt);
	*sprite_dist = malloc(sizeof(**sprite_dist) * data->desc->sprite_cnt);
	if (!*sprite_order || !*sprite_dist)
	{
		free(sprite_order);
		free(sprite_dist);
		return (1);
	}
	index = -1;
	while (++index < data->desc->sprite_cnt)
	{
		pos_x = data->cast.pos_x;
		pos_y = data->cast.pos_y;
		sprite = data->desc->sprites[index];
		(*sprite_order)[index] = index;
		(*sprite_dist)[index] = ((pos_x - sprite.pos_x) * (pos_x - sprite.pos_x)
				+ (pos_y - sprite.pos_y) * (pos_y - sprite.pos_y));
	}
	sort_sprites(*sprite_order, *sprite_dist, data->desc->sprite_cnt);
	return (0);
}

static  void sprite_init_calculations(t_data *data, t_draw_sprite_vars *draw_vars)
{
	t_cast cast;

	cast = data->cast;
	draw_vars->inv_det = 1.0 / (cast.plane_x * cast.dir_y - cast.dir_x * cast.plane_y);
	draw_vars->transform_x = draw_vars->inv_det * (cast.dir_y * draw_vars->sprite_x - cast.dir_x * draw_vars->sprite_y);
	draw_vars->transform_y = draw_vars->inv_det * (-cast.plane_y * draw_vars->sprite_x + cast.plane_x * draw_vars->sprite_y);
	draw_vars->sprite_screen_x = (int)((cast.width / 2) * (1 + draw_vars->transform_x / draw_vars->transform_y));
	draw_vars->sprite_height = abs((int)(cast.height / (draw_vars->transform_y)));
	draw_vars->sprite_width = abs((int)(cast.height / (draw_vars->transform_y)));
}

static void define_start_end(t_draw_sprite_vars *draw_vars, t_data *data)
{
	t_cast cast;

	cast = data->cast;
	draw_vars->draw_start_y = -draw_vars->sprite_height / 2 + cast.height / 2;
	if (draw_vars->draw_start_y < 0)
		draw_vars->draw_start_y = 0;
	draw_vars->draw_end_y = draw_vars->sprite_height / 2 + cast.height / 2;
	if (draw_vars->draw_end_y >= cast.height)
		draw_vars->draw_end_y = cast.height - 1;
	draw_vars->draw_start_x = -draw_vars->sprite_width / 2 + draw_vars->sprite_screen_x;
	if (draw_vars->draw_start_x < 0)
		draw_vars->draw_start_x = 0;
	draw_vars->draw_end_x = draw_vars->sprite_width / 2 + draw_vars->sprite_screen_x;
	if (draw_vars->draw_end_x >= cast.width)
		draw_vars->draw_end_x = cast.width - 1;
}

int	add_sprites(t_data *data)
{
	int index;
	int	*sprite_order;
	double *sprite_dist;
	t_draw_sprite_vars draw_vars;

	if (init_sprite_order(data, &sprite_order, &sprite_dist))
		return (1);
	index = -1;
	while (++index < data->desc->sprite_cnt)
	{
		draw_vars.sprite_x = data->desc->sprites[sprite_order[index]].pos_x - data->cast.pos_x;
		draw_vars.sprite_y = data->desc->sprites[sprite_order[index]].pos_y - data->cast.pos_y;
		sprite_init_calculations(data, &draw_vars);
		define_start_end(&draw_vars, data);
		draw_vars.stripe = draw_vars.draw_start_x - 1;
		while (++draw_vars.stripe < draw_vars.draw_end_x)
		{
			draw_vars.tex_x = (int)(256 * (draw_vars.stripe - (-draw_vars.sprite_width / 2 + draw_vars.sprite_screen_x)) * data->textures[4].width / draw_vars.sprite_width) / 256;
			if (draw_vars.transform_y > 0 && draw_vars.stripe > 0 && draw_vars.stripe < data->cast.width && draw_vars.transform_y < data->wall_dist[draw_vars.stripe])
			{
				draw_vars.y = draw_vars.draw_start_y - 1;
				while (++draw_vars.y < draw_vars.draw_end_y)
				{
					draw_vars.d = (draw_vars.y) * 256 - data->cast.height *128 + draw_vars.sprite_height * 128;
					draw_vars.tex_y = ((draw_vars.d * data->textures[4].height) / draw_vars.sprite_height) / 256;
					draw_vars.colour = data->textures[4].addr[data->textures[4].width * draw_vars.tex_y + draw_vars.tex_x];
					if ((draw_vars.colour & 0x00FFFFFF) != 0)
						img_pix_put(&data->img, draw_vars.stripe, draw_vars.y, draw_vars.colour);
				}
			}
		}
	}
	free(sprite_order);
	free(sprite_dist);
	return (0);
}
