/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelfaki <mbelfaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 18:00:00 by mbelfaki          #+#    #+#             */
/*   Updated: 2026/06/17 19:29:32 by mbelfaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	check_int_max(char *str)
{
	int		i;
	long	value;

	i = 0;
	value = 0;
	while (str[i])
	{
		value = value * 10 + (str[i] - 48);
		if (value > 2147483647)
			return (1);
		i++;
	}
	return (0);
}

static int	is_digete(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '\0' || check_int_max(str))
		return (0);
	if (str[0] == '+')
		i++;
	while (str[i])
	{
		if ((str[i] < '0') || (str[i] > '9'))
			return (0);
		i++;
	}
	return (1);
}

int	cheak_arges(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc != 9)
	{
		printf("wrong number of args \n");
		return (0);
	}
	if (!atoi(argv[0]))
		return (0);
	while (i < argc - 2)
	{
		if (!is_digete(argv[i]))
		{
			printf("args must be positive digeites and less than int max \n");
			return (0);
		}
		i++;
	}
	if (strcmp(argv[i], "fifo") && strcmp(argv[i], "edf"))
	{
		printf("fifo or edf\n");
		return (0);
	}
	return (1);
}

t_data	*getdata(int argc, char **argv)
{
	int		i;
	t_data	*data;

	i = 0;
	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	while (i < argc - 2)
	{
		data->values[i] = atoi(argv[i]);
		i++;
	}
	data->time = 0;
	data->algo = argv[7];
	data->thread_count = 0;
	return (data);
}
