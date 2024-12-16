/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_image_composer.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrochd <rrochd@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 08:42:52 by rrochd            #+#    #+#             */
/*   Updated: 2024/12/16 13:27:55 by rrochd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	*create_empty_image(void *mlx, int width, int height)
{
	void	*img;

	img = mlx_new_image(mlx, width, height);
	if (!img)
		error("Failed to create new image");
	return (img);
}

static unsigned int	get_pixel_color(t_image img, int x, int y)
{
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	unsigned int	*pixel;

	addr = mlx_get_data_addr(img.image, &bits_per_pixel, &line_length, &endian);
	pixel = (unsigned int *)(addr + (y * line_length + x * (bits_per_pixel
					/ 8)));
	return (*pixel);
}

static void	put_pixel(void *img, int x, int y, unsigned int color)
{
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	unsigned int	*pixel;

	addr = mlx_get_data_addr(img, &bits_per_pixel, &line_length, &endian);
	pixel = (unsigned int *)(addr + (y * line_length + x * (bits_per_pixel
					/ 8)));
	*pixel = color;
}

static void	blend(void *result, t_image image, t_point pos, t_point start_pos)
{
	unsigned int	color;

	color = get_pixel_color(image, pos.x, pos.y);
	if (color != 0xFF000000)
		put_pixel(result, pos.x + start_pos.x, pos.y + start_pos.y, color);
}

void	*compose_images(t_game *game, t_image *images, int count)
{
	void	*result;
	t_point	start_pos;
	int		i;
	t_point	pos;

	result = create_empty_image(game->mlx, TILE_SIZE, TILE_SIZE);
	i = 0;
	while (i < count)
	{
		start_pos.x = (TILE_SIZE - images[i].width) / 2;
		start_pos.y = (TILE_SIZE - images[i].height) / 2;
		pos.y = 0;
		while (pos.y < images[i].height)
		{
			pos.x = 0;
			while (pos.x < images[i].width)
			{
				blend(result, images[i], pos, start_pos);
				pos.x++;
			}
			pos.y++;
		}
		i++;
	}
	return (result);
}
