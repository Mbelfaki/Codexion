/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelfaki <mbelfaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 11:19:26 by mbelfaki          #+#    #+#             */
/*   Updated: 2026/04/02 12:39:37 by mbelfaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coder.h"
#include "parcing.h"
#include "queue.h"

int	main(int argc, char **argv)
{
	Data_t		*data;
	pthread_t	*thread_list;

	if (!cheak_arges(argc, &argv[1]))
		return (0);
	data = getdata(argc, &argv[1]);
	thread_list = malloc(sizeof(pthread_t) * data->values[0]);
	if(!thread_list)
	printf("wwww4\n");
	create_list_thread(data, thread_list, coder_thread);
}
