/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelfaki <mbelfaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 18:00:08 by mbelfaki          #+#    #+#             */
/*   Updated: 2026/06/06 15:56:57 by mbelfaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

t_dongle	*request_dongle(t_coder *coder, int i)
{
	t_dongle	*dongle;

	dongle = NULL;
	if (i == 0)
		dongle = coder->dongle_left;
	else if (i == 1)
		dongle = coder->dongle_right;
	pthread_mutex_lock(&dongle->lock);
	enqueue(dongle->queue, coder, coder->data->algo);
	pthread_mutex_unlock(&dongle->lock);
	return (dongle);
}

t_Bool	get_dongle(t_dongle *dongle, t_coder *coder)
{
	pthread_mutex_lock(&dongle->lock);
	if (dongle->taken)
	{
		pthread_cond_wait(&dongle->cond, &dongle->lock);
	}
	pthread_mutex_unlock(&dongle->lock);
	while (!istop(dongle, coder) || get_clodown(dongle) > get_time())
		;
	pthread_mutex_lock(&dongle->lock);
	dequeue(dongle->queue, coder->data->algo);
	dongle->taken = TRUE;
	pthread_mutex_unlock(&dongle->lock);
	if (cheak_burnout(coder))
		return (FALSE);
	display_data(coder, "has taken a dongle");
	return (TRUE);
}

void	release_dongles(t_coder *coder)
{
	pthread_mutex_lock(&coder->dongle_left->lock);
	if (coder->dongle_left->taken)
	{
		coder->dongle_left->taken = FALSE;
		coder->dongle_left->dongle_cooldown = get_time()
			+ coder->data->values[6];
		pthread_cond_broadcast(&coder->dongle_left->cond);
	}
	pthread_mutex_unlock(&coder->dongle_left->lock);
	pthread_mutex_lock(&coder->dongle_right->lock);
	if (coder->dongle_right->taken)
	{
		coder->dongle_right->taken = FALSE;
		coder->dongle_right->dongle_cooldown = get_time()
			+ coder->data->values[6];
		pthread_cond_broadcast(&coder->dongle_right->cond);
	}
	pthread_mutex_unlock(&coder->dongle_right->lock);
}

t_Bool	get_dongles(t_coder *coder)
{
	t_dongle	*dongle;

	dongle = request_dongle(coder, coder->id % 2);
	if (!get_dongle(dongle, coder))
	{
		release_dongles(coder);
		return (0);
	}
	if (cheak_burnout(coder))
	{
		release_dongles(coder);
		return (0);
	}
	dongle = request_dongle(coder, (coder->id + 1) % 2);
	get_dongle(dongle, coder);
	if (cheak_burnout(coder))
	{
		release_dongles(coder);
		return (0);
	}
	return (compile(coder));
}

t_dongle	*create_dongle(t_data *data)
{
	t_dongle	*dongle_list;
	int			i;

	i = 0;
	dongle_list = malloc(sizeof(t_dongle) * data->values[0]);
	if (!dongle_list)
		return (NULL);
	while (i < data->values[0])
	{
		dongle_list[i].id = i;
		dongle_list[i].taken = FALSE;
		if (pthread_mutex_init(&dongle_list[i].lock, NULL))
			return (NULL);
		if (pthread_cond_init(&dongle_list[i].cond, NULL))
			return (NULL);
		dongle_list[i].queue = create_queue(2);
		dongle_list[i].dongle_cooldown = 0;
		i++;
	}
	return (dongle_list);
}
