/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrochd <rrochd@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 10:57:55 by rrochd            #+#    #+#             */
/*   Updated: 2024/12/19 10:57:59 by rrochd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "containers.h"

void	string_init(t_string *str)
{
	str->data = track_malloc((INITIAL_CAPACITY + 1) * sizeof(char));
	str->size = 0;
	str->capacity = INITIAL_CAPACITY;
}

void	string_append(t_string *str, const char *text)
{
	char	*new_data;
	size_t	text_len;
	size_t	new_cap;

	if (!text)
		return ;
	text_len = ft_strlen(text);
	if (str->size + text_len >= str->capacity)
	{
		new_cap = str->capacity;
		while (new_cap < str->size + text_len + 1)
			new_cap *= 2;
		new_data = _c_grow(str->data, str->capacity, new_cap, sizeof(char));
		str->data = new_data;
		str->capacity = new_cap;
	}
	ft_memcpy(str->data + str->size, text, text_len);
	str->size += text_len;
}

void	string_destroy(t_string *str)
{
	free_resource(str->data);
	str->data = NULL;
	str->size = 0;
	str->capacity = 0;
}
