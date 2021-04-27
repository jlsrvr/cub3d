#include "engine.h"

#define HEADER_SIZE 14
#define INFO_HEADER_SIZE 40
#define NO_COMPRESSION 0
#define MAX_NUMBER_OF_COLOURS 0
#define ALL_COLORS_REQUIRED 0

int save_image(t_data *data)
{
	int fd;

	data->win_ptr = NULL;
	fd = open("./screenshot.bmp", O_WRONLY| O_CREAT | O_TRUNC);
	if (fd == -1)
	{
		printf(RED"Error\n"RESET"Unable to create or open file for screenshot");
		return (1);
	}
	//*****HEADER************//
	int bytes_per_pixel;
	int height;
	int width;

	bytes_per_pixel = data->img.bpp / 8;
	height = data->desc->y_res;
	width = data->desc->x_res;
	write(fd, "BM", 2);
	int padded_row_size = (int)(4 * ceil((float)width / 4.0f)) * bytes_per_pixel;
	int file_size = padded_row_size * height + HEADER_SIZE + INFO_HEADER_SIZE;
	write(fd, &file_size, 4);
	int reserved = 0x0000;
	write(fd, &reserved, 4);
	int dataOffset = HEADER_SIZE + INFO_HEADER_SIZE;
	write(fd, &dataOffset, 4);
	//*******INFO*HEADER******//
	int infoHeaderSize = INFO_HEADER_SIZE;
	write(fd, &infoHeaderSize, 4);
	write(fd, &width, 4);
	write(fd, &height, 4);
	int planes = 1; //always 1
	write(fd, &planes, 2);
	write(fd, &data->img.bpp, 2);
	//write compression
	int compression = NO_COMPRESSION;
	write(fd, &compression, 4);
	//write image size (in bytes)
	int imageSize = height * width * bytes_per_pixel;
	write(fd, &imageSize, 4);
	int resolution_x = 0; //300 dpi
	int resolution_y = 0; //300 dpi
	write(fd, &resolution_x, 4);
	write(fd, &resolution_y, 4);
	int colors_used = MAX_NUMBER_OF_COLOURS;
	write(fd, &colors_used, 4);
	int important_colors = ALL_COLORS_REQUIRED;
	write(fd, &important_colors, 4);
	int i = 0;
	int unpadded_row_size = width * bytes_per_pixel;
	for ( i = 0; i < height; i++)
	{
		int pixel_offset = ((height- i) - 1) * unpadded_row_size;
		write(fd, &data->img.addr[pixel_offset], padded_row_size);
	}
	close(fd);
	destroy_mlx_resources(data);
	return (0);
}
