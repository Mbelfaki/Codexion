/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelfaki <mbelfaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 16:33:10 by mbelfaki          #+#    #+#             */
/*   Updated: 2026/06/07 16:45:00 by mbelfaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

t_coder	*dequeue(t_queue *queue, char *algo)
{
	int		i;
	int		best;
	t_coder	*result;

	result = queue->coders[0];
	queue->coders[0] = queue->coders[--queue->count];
	i = 0;
	while (1)
	{
		best = get_best(queue, i, algo);
		if (best == i)
			break ;
		swap_queue(queue, i, best);
		i = best;
	}
	return (result);
}

void	enqueue(t_queue *queue, t_coder *coder, char *algo)
{
	int		i;
	int		parent;
	t_coder	*tmp;

	if (queue->count >= queue->size)
		return ;
	i = queue->count++;
	queue->coders[i] = coder;
	while (i > 0)
	{
		parent = (i - 1) / 2;
		if (!higher_priority(queue->coders[i], queue->coders[parent], algo))
			break ;
		tmp = queue->coders[i];
		queue->coders[i] = queue->coders[parent];
		queue->coders[parent] = tmp;
		i = parent;
	}
}
