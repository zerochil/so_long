#include "containers.h"

int	array_size(void *ptr)
{
	size_t	size;
	void	**arr;

	if (!ptr)
		return (0);
	arr = ptr;
	size = 0;
	while (arr[size])
		size++;
	return (size);
}

