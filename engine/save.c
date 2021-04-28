/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrivoire <jrivoire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 12:00:03 by jrivoire          #+#    #+#             */
/*   Updated: 2021/04/28 12:00:08 by jrivoire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

#define HEADER_SIZE 14
#define INFO_HEADER_SIZE 40

static void	compression_and_colour(int fd)
{
	int temp;

	temp = 0;
	write(fd, &temp, 4);
	write(fd, &temp, 4);
	write(fd, &temp, 4);
	write(fd, &temp, 4);
	write(fd, &temp, 4);
	write(fd, &temp, 4);
}

static void	info_header(int fd, t_data *data, int width, int height)
{
	int temp;
	int plane;
	int reserved;
	int data_offset;

	reserved = 0x0000;
	write(fd, &reserved, 4);
	data_offset = HEADER_SIZE + INFO_HEADER_SIZE;
	write(fd, &data_offset, 4);
	temp = INFO_HEADER_SIZE;
	write(fd, &temp, 4);
	write(fd, &width, 4);
	write(fd, &height, 4);
	plane = 1;
	write(fd, &plane, 2);
	write(fd, &data->img.bpp, 2);
	compression_and_colour(fd);
}

static void	write_in_file(int fd, t_data *data, int padded_row_size)
{
	int i;
	int height;
	int width;
	int pixel_offset;
	int unpadded_row_size;

	height = data->desc->y_res;
	width = data->desc->x_res;
	unpadded_row_size = width * (data->img.bpp / 8);
	i = -1;
	while (++i < height)
	{
		pixel_offset = ((height - i) - 1) * unpadded_row_size;
		write(fd, &data->img.addr[pixel_offset], padded_row_size);
	}
	close(fd);
}

int			save_image(t_data *data)
{
	int fd;
	int height;
	int width;
	int temp;
	int padded_row_size;

	data->win_ptr = NULL;
	fd = open("./screenshot.bmp", O_WRONLY | O_TRUNC | O_CREAT, 0755);
	if (fd == -1)
	{
		destroy_mlx_resources(data);
		printf(RED"Error\n"RESET"Unable to create or open file for screenshot");
		return (1);
	}
	height = data->desc->y_res;
	width = data->desc->x_res;
	write(fd, "BM", 2);
	padded_row_size = (int)(4 * ceil((float)width / 4.0f))
							* (data->img.bpp / 8);
	temp = padded_row_size * height + HEADER_SIZE + INFO_HEADER_SIZE;
	write(fd, &temp, 4);
	info_header(fd, data, width, height);
	write_in_file(fd, data, padded_row_size);
	destroy_mlx_resources(data);
	return (0);
}
