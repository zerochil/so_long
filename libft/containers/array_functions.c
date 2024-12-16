#include "containers.h"

void	array_init(t_array *array)
{
	if (!array)
		return;
	array->data = track_malloc(INITIAL_CAPACITY * sizeof(void *));
	array->size = 0;
	array->capacity = INITIAL_CAPACITY;
}

void	array_push(t_array *array, void *item)
{
	void	**new_data;
	size_t	new_cap;

	if (!array)
		return;
	if (array->size == array->capacity)
	{
		new_cap = array->capacity * 2;
		new_data = _c_grow(array->data, array->capacity, new_cap, sizeof(void *));
		array->data = new_data;
		array->capacity = new_cap;
	}
	array->data[array->size++] = item;
}

void	array_remove(t_array *array, size_t index)
{
	if (!array || index >= array->size)
		return ;
	while (index < array->size - 1)
	{
		array->data[index] = array->data[index + 1];
		index++;
	}
	array->data[array->size - 1] = NULL;
	array->size--;
}

void	*array_dup(t_array *array)
{
	void	**new_data;

	if (!array || array->size == 0)
		return (NULL);
	new_data = track_malloc((array->size + 1) * sizeof(void *));
	ft_memcpy(new_data, array->data, array->size * sizeof(void *));
	return (new_data);
}

void array_insert(t_array *array, size_t index, void *element)
{
	size_t i;

	if (!array)
		return;
    if (array->size >= array->capacity)
    {
        size_t new_capacity = (array->capacity == 0) ? 1 : array->capacity * 2;
        void **new_data = track_malloc(sizeof(void *) * new_capacity);
		i = 0;
        while (i < array->size)
		{
            new_data[i] = array->data[i];
			i++;
		}
        free_resource(array->data);
        array->data = new_data;
        array->capacity = new_capacity;
    }
	i = array->size;
    while (i > index)
	{
        array->data[i] = array->data[i - 1];
		i--;
	}
    array->data[index] = element;
    array->size++;
}

void	array_destroy(t_array *array)
{
	if (!array)
		return;
	free_resource(array->data);
	array->data = NULL;
	array->size = 0;
	array->capacity = 0;
}
