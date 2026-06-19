/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelfaki <mbelfaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 14:33:52 by mbelfaki          #+#    #+#             */
/*   Updated: 2026/06/18 18:50:27 by mbelfaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	destroy(t_monitor_arg *monitor_arg)
{
	int	i;

	i = 0;
	pthread_cond_destroy(&monitor_arg->coders[0].data->cond);
	while (i < monitor_arg->number_coders)
	{
		pthread_mutex_destroy(&monitor_arg->coders[i++].dongle_left->lock);
		pthread_cond_destroy(&monitor_arg->coders[i++].dongle_left->cond);
	}
	i = 0;
	while (i < 5)
		pthread_mutex_destroy(&monitor_arg->commen_locks[i++]);
}

void	free_coders(t_monitor_arg *monitor_arg)
{
	int	i;

	i = 0;
	destroy(monitor_arg);
	while (i < monitor_arg->number_coders)
	{
		free(monitor_arg->coders[i].dongle_left->queue->coders);
		free(monitor_arg->coders[i].dongle_left->queue);
		i++;
	}
	free(monitor_arg->coders[0].dongle_left);
	free(monitor_arg->coders[0].data);
	free(monitor_arg->coders);
	free(monitor_arg->commen_locks);
	free(monitor_arg);
}
