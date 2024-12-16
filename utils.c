/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrochd <rrochd@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 10:18:02 by rrochd            #+#    #+#             */
/*   Updated: 2024/12/16 10:48:00 by rrochd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	*get_game_instance(void)
{
	static t_game	game;

	return (&game);
}

void	game_over(char *message)
{
	if (message && *message)
		ft_putendl_fd(message, 1);
	free_all_resources();
	exit(0);
}
