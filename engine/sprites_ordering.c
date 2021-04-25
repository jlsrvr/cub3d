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

int			init_sprite_order(t_data *data, int **sprite_order, double **sprite_dist)
{
	int			index;
	double		pos_x;
	double 		pos_y;
	t_sprite	sprite;

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
