/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelfaki <mbelfaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 12:28:21 by mbelfaki          #+#    #+#             */
/*   Updated: 2026/04/28 10:19:16 by mbelfaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

long	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000LL) + (t.tv_usec / 1000));
}

void	display_data(t_coder *coder, char *massge)
{
	pthread_mutex_lock(&coder->data->commen_locks[0]);
	if (!cheak_burnout(coder))
		printf("%ld %d  %s\n", get_time() - coder->data->time, coder->id,
			massge);
	pthread_mutex_unlock(&coder->data->commen_locks[0]);
}

t_Bool	thread_sleep(long time, t_coder *coder)
{
	long	start;

	start = get_time();
	while (get_time() < time + start)
	{
		if (cheak_burnout(coder))
			return (TRUE);
		usleep(500);
	}
	return (FALSE);
}

t_Bool	cheak_burnout(t_coder *coder)
{
	t_Bool	flage;

	pthread_mutex_lock(&coder->data->commen_locks[3]);
	flage = *coder->data->burnout_flage;
	pthread_mutex_unlock(&coder->data->commen_locks[3]);
	return (flage);
}

t_Bool	compile(t_coder *coder)
{
	display_data(coder, "is compiling");
	set_last_compiling(coder, get_time());
	if (thread_sleep(coder->data->values[2], coder))
	{
		release_dongles(coder);
		return (FALSE);
	}
	if (cheak_burnout(coder))
	{
		release_dongles(coder);
		return (FALSE);
	}
	release_dongles(coder);
	if (cheak_burnout(coder))
		return (FALSE);
	return (TRUE);
}
