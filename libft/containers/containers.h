/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   containers.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrochd <rrochd@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 10:57:55 by rrochd            #+#    #+#             */
/*   Updated: 2024/12/19 10:57:59 by rrochd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTAINERS_H
# define CONTAINERS_H

# include "../base/base.h"
# include "../memory_management/memory_management.h"

# define INITIAL_CAPACITY 8

typedef struct s_array
{
	void	**data;
	size_t	size;
	size_t	capacity;
}			t_array;

typedef struct s_vector
{
	int		*data;
	size_t	size;
	size_t	capacity;
}			t_vector;

typedef struct s_string
{
	char	*data;
	size_t	size;
	size_t	capacity;
}			t_string;

typedef struct s_point
{
	int		x;
	int		y;
}			t_point;

typedef struct s_dimensions
{
	int		width;
	int		height;
}			t_dimensions;

t_point		*new_point(int x, int y);

void		*_c_grow(void *old_data, size_t old_cap, size_t new_cap,
				size_t elem_size);

void		array_init(t_array *arr);
void		array_push(t_array *arr, void *item);
void		array_destroy(t_array *arr);
void		array_remove(t_array *arr, size_t index);
void		array_insert(t_array *array, size_t index, void *element);
void		array_do(t_array *array, void (*func)(void *));
void		free_array(t_array *array);
void		*array_pop(t_array *array);
void		*array_dup(t_array *arr);
void		*array_first_item(t_array *array);
void		*array_last_item(t_array *array);
void		*array_find(t_array *array, void *element, int (*cmp)(void *,
					void *));

void		vector_init(t_vector *vec);
void		vector_push(t_vector *vec, int item);
void		vector_destroy(t_vector *vec);

void		string_init(t_string *str);
void		string_append(t_string *str, const char *text);
void		string_destroy(t_string *str);

t_point		find_in_matrix(void **arr, t_dimensions dim, int target,
				size_t size);
int			count_in_matrix(void **arr, t_dimensions dim, int target,
				size_t size);
int			is_true_in_matrix(void **arr, t_dimensions dim,
				int condition(t_point, t_dimensions, int), size_t size);

#endif
