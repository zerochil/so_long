#include "containers.h"

void    *_c_grow(void *old_data, size_t old_cap, size_t new_cap, size_t elem_size)
{
    void    *new_data;
    
    new_data = track_malloc(new_cap * elem_size);
    if (old_data)
    {
        ft_memcpy(new_data, old_data, old_cap * elem_size);
        free_resource(old_data);
    }
    return (new_data);
}
