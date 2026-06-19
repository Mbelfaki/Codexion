/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelfaki <mbelfaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 18:45:11 by mbelfaki          #+#    #+#             */
/*   Updated: 2026/06/18 18:34:37 by mbelfaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

t_Bool	create_locks(t_data *data, int number_lock)
{
	int	i;

	data->commen_locks = malloc(sizeof(pthread_mutex_t) * number_lock);
	pthread_cond_init(&data->cond, NULL);
	if (!data->commen_locks)
		return (FALSE);
	i = 0;
	while (i < number_lock)
	{
		if (pthread_mutex_init(&data->commen_locks[i], NULL))
			break ;
		i++;
	}
	if (i != number_lock)
	{
		while (i > 0)
		{
			i--;
			pthread_mutex_destroy(&data->commen_locks[i]);
		}
		return (FALSE);
	}
	return (TRUE);
}

void	init_coders(t_coder *coder_list, t_data *data, t_dongle *dongle_list)
{
	int	i;

	i = 0;
	while (i < data->values[0])
	{
		coder_list[i].finched_flage = FALSE;
		coder_list[i].data = data;
		coder_list[i].id = i + 1;
		coder_list[i].time_to_burnout = data->values[1];
		coder_list[i].last_compiling = data->time;
		coder_list[i].dongle_left = &dongle_list[i];
		coder_list[i].dongle_right = &dongle_list[(i + 1) % data->values[0]];
		i++;
	}
}

int	create_threads(t_data *data, pthread_t *thread_list, t_coder *coder_list)
{
	int	i;

	i = 0;
	while (i < data->values[0])
	{
		if (pthread_create(&thread_list[i], NULL, coder_thread, &coder_list[i]))
			return (i);
		i++;
	}
	return (i);
}

t_monitor_arg	*create_list_thread(t_data *data, pthread_t *thread_list)
{
	t_coder			*coder_list;
	t_dongle		*dongle_list;
	t_monitor_arg	*monitor_arg;
	int				thread_count;

	thread_count = 0;
	monitor_arg = NULL;
	coder_list = malloc(sizeof(t_coder) * data->values[0]);
	if (!coder_list)
		return (monitor_arg);
	dongle_list = create_dongle(data);
	if (!dongle_list)
		return (free(coder_list), monitor_arg);
	if (!create_locks(data, 5))
		return (free(coder_list), free(dongle_list), monitor_arg);
	init_coders(coder_list, data, dongle_list);
	monitor_arg = create_monitor(data, coder_list);
	if (!monitor_arg)
		return (free(coder_list), free(dongle_list), monitor_arg);
	thread_count = create_threads(data, thread_list, coder_list);
	if (thread_count == data->values[0])
		if (!pthread_create(&thread_list[data->values[0]], NULL, monitor_thread,
				monitor_arg))
			thread_count++;
	if (thread_count != data->values[0] + 1)
		*data->burnout_flage = TRUE;
	start_simulation(data, coder_list, thread_count);
	thread_list_join(thread_list, thread_count);
	return (monitor_arg);
}
