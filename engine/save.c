#include "engine.h"

int save_image(t_data *data)
{
	(void)data;
	printf("saved");
	data->win_ptr = NULL;
	destroy_mlx_resources(data);
	return (0);
}
