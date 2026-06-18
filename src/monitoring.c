/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelfaki <mbelfaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 18:00:20 by mbelfaki          #+#    #+#             */
/*   Updated: 2026/06/17 20:11:09 by mbelfaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

t_Bool	get_finched_flage(t_coder *coder)
{
	t_Bool	flage;

	pthread_mutex_lock(&coder->data->commen_locks[1]);
	flage = coder->finched_flage;
	pthread_mutex_unlock(&coder->data->commen_locks[1]);
	return (flage);
}

t_Bool	finched_cheak(t_monitor_arg *monitor_arg)
{
	int	i;

	i = 0;
	while (i < monitor_arg->number_coders)
	{
		if (!get_finched_flage(&monitor_arg->coders[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

t_Bool	monitor_cheak(t_monitor_arg *monitor_arg)
{
	int	i;

	i = 0;
	while (i < monitor_arg->number_coders)
	{
		if (!get_finched_flage(&monitor_arg->coders[i])
			&& get_last_compiling(&monitor_arg->coders[i])
			+ monitor_arg->coders[i].time_to_burnout < get_time())
		{
			pthread_mutex_lock(&monitor_arg->coders[i].data->commen_locks[3]);
			monitor_arg->burnout_flage = TRUE;
			pthread_mutex_unlock(&monitor_arg->coders[i].data->commen_locks[3]);
			pthread_mutex_lock(&monitor_arg->coders[i].data->commen_locks[0]);
			printf("%ld %d burn out\n", get_time()
				- monitor_arg->coders[i].data->time, monitor_arg->coders[i].id);
			pthread_mutex_unlock(&monitor_arg->coders[i].data->commen_locks[0]);
			if (monitor_arg->number_coders == 1)
				pthread_cond_broadcast(
					&monitor_arg->coders[0].dongle_left->cond);
			return (FALSE);
		}
		usleep(100);
		i++;
	}
	return (TRUE);
}

void	*monitor_thread(void *arg)
{
	t_monitor_arg	*monitor_arg;
	// printf("monitor thread\n");
	monitor_arg = (t_monitor_arg *)arg;
	check_start(&monitor_arg->coders[0]);
	while (1)
	{
		if (finched_cheak(monitor_arg))
			return (NULL);
		if (!monitor_cheak(monitor_arg))
			return (NULL);
	}
	return (0);
}
