#include "containers.h"

t_point	*new_point(int x, int y)
{
	t_point	*point;

	point = track_malloc(sizeof(t_point));
	point->x = x;
	point->y = y;
	return (point);
}
