/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelfaki <mbelfaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 18:00:13 by mbelfaki          #+#    #+#             */
/*   Updated: 2026/06/16 15:19:08 by mbelfaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	*coder_thread(void *arg)
{
	t_coder	*coder;
	int		i;

	coder = (t_coder *)arg;
	i = 0;
	check_start(coder);
	set_last_compiling(coder, get_time());
	while (i < coder->data->values[5] && !cheak_burnout(coder))
	{
		if (!get_dongles(coder))
			return (NULL);
		display_data(coder, "is debugging");
		if (thread_sleep(coder->data->values[3], coder))
			return (NULL);
		if (cheak_burnout(coder))
			return (NULL);
		display_data(coder, "is refactoring");
		if (thread_sleep(coder->data->values[4], coder))
			return (NULL);
		if (cheak_burnout(coder))
			return (NULL);
		i++;
	}
	set_finched_flage(coder, TRUE);
	return (NULL);
}

void	thread_list_join(pthread_t *thread_list, int thread_number)
{
	int	i;

	i = 0;
	while (i < thread_number + 1)
	{
		pthread_join(thread_list[i], NULL);
		i++;
	}
}

t_monitor_arg	*create_monitor(t_data *data, t_coder *coder_list)
{
	t_monitor_arg	*monitor_arg;

	monitor_arg = malloc(sizeof(t_monitor_arg));
	if (!monitor_arg)
		return (NULL);
	data->burnout_flage = &monitor_arg->burnout_flage;
	monitor_arg->coders = coder_list;
	monitor_arg->burnout_flage = FALSE;
	monitor_arg->number_coders = data->values[0];
	monitor_arg->commen_locks = data->commen_locks;
	return (monitor_arg);
}
