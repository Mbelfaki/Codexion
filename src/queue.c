/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelfaki <mbelfaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 18:00:24 by mbelfaki          #+#    #+#             */
/*   Updated: 2026/06/18 15:25:21 by mbelfaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	higher_priority(t_coder *a, t_coder *b, char *algo)
{
	if (strcmp(algo, "edf") == 0)
	{
		if (a->last_compiling != b->last_compiling)
			return (a->last_compiling < b->last_compiling);
		else
		{
			return (a->id < b->id);
		}
	}
	return (0);
}

void	swap_queue(t_queue *queue, int i, int best)
{
	t_coder	*tmp;

	tmp = queue->coders[i];
	queue->coders[i] = queue->coders[best];
	queue->coders[best] = tmp;
}

int	get_best(t_queue *queue, int best, char *algo)
{
	int	left;
	int	right;

	left = 2 * best + 1;
	right = 2 * best + 2;
	if (left < queue->count && higher_priority(queue->coders[left],
			queue->coders[best], algo))
		best = left;
	if (right < queue->count && higher_priority(queue->coders[right],
			queue->coders[best], algo))
		best = right;
	return (best);
}

t_Bool	istop(t_dongle *dongle, t_coder *coder)
{
	if (dongle->queue->count == 0)
		return (0);
	return (dongle->queue->coders[0] == coder);
}

t_queue	*create_queue(int size)
{
	t_queue	*queue;

	queue = malloc(sizeof(t_queue));
	if (!queue)
		return (NULL);
	queue->coders = malloc(sizeof(t_coder *) * size);
	if (!queue->coders)
		return (NULL);
	queue->size = size;
	queue->count = 0;
	return (queue);
}
