#include "containers.h"

void	vector_init(t_vector *vec)
{
	vec->data = track_malloc(INITIAL_CAPACITY * sizeof(int));
	vec->size = 0;
	vec->capacity = INITIAL_CAPACITY;
}

void	vector_push(t_vector *vec, int item)
{
	int		*new_data;
	size_t	new_cap;

	if (vec->size == vec->capacity)
	{
		new_cap = vec->capacity * 2;
		new_data = _c_grow(vec->data, vec->capacity, new_cap, sizeof(int));
		vec->data = new_data;
		vec->capacity = new_cap;
	}
	vec->data[vec->size++] = item;
}

void	vector_destroy(t_vector *vec)
{
	free_resource(vec->data);
	vec->data = NULL;
	vec->size = 0;
	vec->capacity = 0;
}
