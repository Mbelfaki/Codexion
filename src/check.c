/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelfaki <mbelfaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 15:03:44 by mbelfaki          #+#    #+#             */
/*   Updated: 2026/06/19 10:20:36 by mbelfaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	check_start(t_coder *coder)
{
	pthread_mutex_lock(&coder->data->commen_locks[4]);
	coder->data->thread_count++;
	while (!coder->data->time)
		pthread_cond_wait(&coder->data->cond, &coder->data->commen_locks[4]);
	pthread_mutex_unlock(&coder->data->commen_locks[4]);
}

void	start_simulation(t_data *data, t_coder *coder_list, int thread_count)
{
	int	i;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(&data->commen_locks[4]);
		if (data->thread_count < thread_count)
		{
			pthread_mutex_unlock(&data->commen_locks[4]);
			usleep(300);
		}
		else
			break ;
	}
	data->time = get_time();
	while (i < thread_count - 1)
	{
		coder_list[i].last_compiling = get_time();
		i++;
	}
	pthread_cond_broadcast(&data->cond);
	pthread_mutex_unlock(&data->commen_locks[4]);
}

t_Bool	thread_ruten(t_coder *coder)
{
	int		i;

	i = 0;
	while (i < coder->data->values[5] && !cheak_burnout(coder))
	{
		if (!get_dongles(coder))
			return (FALSE);
		display_data(coder, "is debugging");
		if (thread_sleep(coder->data->values[3], coder))
			return (FALSE);
		if (cheak_burnout(coder))
			return (FALSE);
		display_data(coder, "is refactoring");
		if (thread_sleep(coder->data->values[4], coder))
			return (FALSE);
		if (cheak_burnout(coder))
			return (FALSE);
		i++;
	}
	return (TRUE);
}
