/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrochd <rrochd@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 10:57:55 by rrochd            #+#    #+#             */
/*   Updated: 2024/12/19 10:57:59 by rrochd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "containers.h"

t_point	*new_point(int x, int y)
{
	t_point	*point;

	point = track_malloc(sizeof(t_point));
	point->x = x;
	point->y = y;
	return (point);
}
