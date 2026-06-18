/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelfaki <mbelfaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 19:31:02 by mbelfaki          #+#    #+#             */
/*   Updated: 2026/04/24 19:32:25 by mbelfaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

long	get_last_compiling(t_coder *coder)
{
	long	time;

	pthread_mutex_lock(&coder->data->commen_locks[2]);
	time = coder->last_compiling;
	pthread_mutex_unlock(&coder->data->commen_locks[2]);
	return (time);
}

long	get_clodown(t_dongle *dongle)
{
	long	time;

	pthread_mutex_lock(&dongle->lock);
	time = dongle->dongle_cooldown;
	pthread_mutex_unlock(&dongle->lock);
	return (time);
}

void	set_last_compiling(t_coder *coder, long time)
{
	pthread_mutex_lock(&coder->data->commen_locks[2]);
	coder->last_compiling = time;
	pthread_mutex_unlock(&coder->data->commen_locks[2]);
}

void	set_finched_flage(t_coder *coder, t_Bool flage)
{
	pthread_mutex_lock(&coder->data->commen_locks[1]);
	coder->finched_flage = flage;
	pthread_mutex_unlock(&coder->data->commen_locks[1]);
}
