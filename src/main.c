/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelfaki <mbelfaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 11:19:26 by mbelfaki          #+#    #+#             */
/*   Updated: 2026/06/18 18:13:43 by mbelfaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(int argc, char **argv)
{
	t_data			*data;
	pthread_t		*thread_list;
	t_monitor_arg	*monitor_arg;

	if (!cheak_arges(argc, &argv[1]))
		return (1);
	data = getdata(argc, &argv[1]);
	thread_list = malloc(sizeof(pthread_t) * (data->values[0] + 1));
	if (!thread_list)
		return (1);
	monitor_arg = create_list_thread(data, thread_list);
	if (monitor_arg)
		free_coders(monitor_arg);
	free(thread_list);
	return (0);
}
