#include "containers.h"

t_point	find_in_matrix(void **arr, t_dimensions dim, int target, size_t size)
{
	int	x;
	int	y;

	if (!arr)
		return ((t_point){-1, -1});
	y = 0;
	while (y < dim.height)
	{
		x = 0;
		while (x < dim.width)
		{
			if (size == sizeof(int) && ((int *)arr[y])[x] == target)
				return ((t_point){x, y});
			if (size == sizeof(char) && ((char *)arr[y])[x] == target)
				return ((t_point){x, y});
			x++;
		}
		y++;
	}
	return ((t_point){-1, -1});
}

int	count_in_matrix(void **arr, t_dimensions dim, int target, size_t size)
{
	int	x;
	int	y;
	int	count;

	if (!arr)
		return (0);
	y = 0;
	count = 0;
	while (y < dim.height)
	{
		x = 0;
		while (x < dim.width)
		{
			if (size == sizeof(int) && ((int *)arr[y])[x] == target)
				count++;
			if (size == sizeof(char) && ((char *)arr[y])[x] == target)
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

int	is_true_in_matrix(void **arr, t_dimensions dim, int condition(t_point, t_dimensions, int), size_t size)
{
	int	x;
	int	y;

	if (!arr)
		return (0);
	y = 0;
	while (y < dim.height)
	{
		x = 0;
		while (x < dim.width)
		{
			if (size == sizeof(int) && condition((t_point){x, y}, dim, ((int *)arr[y])[x]) == 0)
				return (0);
			if (size == sizeof(char) && condition((t_point){x, y}, dim,((char *)arr[y])[x]) == 0)
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}
