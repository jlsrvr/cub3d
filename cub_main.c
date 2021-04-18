/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrivoire <jrivoire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 09:16:03 by jrivoire          #+#    #+#             */
/*   Updated: 2021/04/16 15:42:43 by jrivoire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*static void	free_description(t_des *description)
  {
  int	index;

  if (!description)
  return ;
  free(description->no_path);
  free(description->ea_path);
  free(description->so_path);
  free(description->we_path);
  free(description->s_path);
  if (description->map)
  {
  index = -1;
  while (description->map[++index])
  free(description->map[index]);
  free(description->map);
  }
  }

  static int	pre_game_checks(char **av, int *fd, t_des *ptn_description)
  {
  if (path_checker(av[1], ".cub"))
  {
  printf(RED"Error\n"RESET"%s : invalid", av[1]);
  return (1);
  }
 *fd = open(av[1], O_RDONLY);
 if (cub_parser(*fd, &ptn_description))
 {
 printf(RED"Error\n"RESET);
 printf("There is a problem with the scene given at %s", av[1]);
 return (1);
 }
 else if (cub_validator(ptn_description))
 return (1);
 return (0);
 }

 int	main(int ac, char **av)
 {
 t_des	*ptn_description;
 int		ret;
 int		fd;

 ptn_description = NULL;
 ret = 0;
 if (ac == 1)
 {
 printf(RED"Error\n"RESET"A path to a scene description must be given!");
 return (1);
 }
 ret = pre_game_checks(av, &fd, ptn_description);
 close(fd);
 free_description(ptn_description);
 return (ret);
 }*/

#include <X11/X.h>
#include <X11/keysym.h>


typedef struct s_rect
{
	int	x;
	int	y;
	int width;
	int height;
	int color;

}	t_rect;

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;

}	t_data;

int handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	else if (keysym == XK_w)
	{
		printf("Keypress 'w' (forward)\n");
	}
	else if (keysym == XK_a)
	{
		printf("Keypress 'a' (rotate left)\n");
	}
	else if (keysym == XK_s)
	{
		printf("Keypress 's' (backward)\n");
	}
	else if (keysym == XK_d)
	{
		printf("Keypress 'd' (rotate right)\n");
	}
	return (0);
}

int handle_keyrelease(int keysym, void *data)
{
	(void)data;
	if (keysym == XK_w)
	{
		printf("Key release 'w' (forward)\n");
	}
	else if (keysym == XK_a)
	{
		printf("Key release 'a' (rotate left)\n");
	}
	else if (keysym == XK_s)
	{
		printf("Key release 's' (backward)\n");
	}
	else if (keysym == XK_d)
	{
		printf("Key release 'd' (rotate right)\n");
	}
	return (0);
}

#define RED_PIXEL 0xFF0000
#define WIN_X 1200
#define WIN_Y 800

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
		/* big endian, MSB is the leftmost bit */
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		/* little endian, LSB is the leftmost bit */
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

int render_rect(t_img *img, t_rect rect)
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
	return (0);
}

void	render_background(t_img *img, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < WIN_Y)
	{
		j = 0;
		while (j < WIN_X)
			img_pix_put(img, j++, i, color);
		++i;
	}
}

int render(t_data *data)
{
	if (data->win_ptr == NULL)
		return (1);
	render_background(&data->img, 0xffffff);
	render_rect(&data->img, (t_rect){WIN_X - 200, WIN_Y - 200, 100, 50, 0x00FF00});
	render_rect(&data->img, (t_rect){0, WIN_Y - 150, 200, 50, 0x00FFFF});
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
	return (0);
}

int main(void)
{
	t_data data;

	data.mlx_ptr = mlx_init();
	data.win_ptr = mlx_new_window(data.mlx_ptr, WIN_X, WIN_Y, "I Have keys");
	data.img.mlx_img = mlx_new_image(data.mlx_ptr, WIN_X, WIN_Y);
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp, &data.img.line_len, &data.img.endian);
	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &handle_keyrelease, &data);
	mlx_loop(data.mlx_ptr);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
	return (0);
}
