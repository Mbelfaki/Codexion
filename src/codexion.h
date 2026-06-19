/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelfaki <mbelfaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 18:00:46 by mbelfaki          #+#    #+#             */
/*   Updated: 2026/06/19 10:20:56 by mbelfaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef enum t_Bool
{
	FALSE,
	TRUE,
}						t_Bool;

typedef struct s_data	t_data;
typedef struct s_coder	t_coder;
typedef struct s_dongle	t_dongle;
typedef struct s_queue	t_queue;

struct					s_data
{
	long				values[7];
	long				time;
	char				*algo;
	pthread_mutex_t		*commen_locks;
	t_Bool				*burnout_flage;
	int					thread_count;
	pthread_cond_t		cond;
};
struct					s_queue
{
	t_coder				**coders;
	int					front;
	int					rear;
	int					count;
	int					size;
};

struct					s_dongle
{
	int					id;
	t_Bool				taken;
	pthread_cond_t		cond;
	t_queue				*queue;
	pthread_mutex_t		lock;
	long				dongle_cooldown;
};

struct					s_coder
{
	t_data				*data;
	int					id;
	t_dongle			*dongle_left;
	t_dongle			*dongle_right;
	long				last_compiling;
	long				time_to_burnout;
	t_Bool				finched_flage;
};
typedef struct s_monitor_arg
{
	t_Bool				burnout_flage;
	t_coder				*coders;
	int					number_coders;
	pthread_mutex_t		*commen_locks;
}						t_monitor_arg;

t_dongle				*request_dongle(t_coder *coder, int i);
void					release_dongles(t_coder *coder);
t_monitor_arg			*create_list_thread(t_data *data,
							pthread_t *thread_list);
void					thread_list_join(pthread_t *thread_list,
							int thread_number);
void					*coder_thread(void *arg);
t_data					*getdata(int argc, char **argv);
int						cheak_arges(int argc, char **argv);
long					get_time(void);
t_queue					*create_queue(int size);
void					enqueue(t_queue *queue, t_coder *coder, char *algo);
t_coder					*dequeue(t_queue *queue, char *algo);
t_Bool					istop(t_dongle *dongle, t_coder *coder);
t_dongle				*request_dongle(t_coder *coder, int i);
t_Bool					get_dongle(t_dongle *dongle, t_coder *coder);

void					display_data(t_coder *coder, char *massge);
t_Bool					get_dongles(t_coder *coder);
void					*monitor_thread(void *arg);
t_dongle				*create_dongle(t_data *data);
t_Bool					compile(t_coder *coder);
t_Bool					thread_sleep(long time, t_coder *coder);
t_Bool					cheak_burnout(t_coder *coder);
t_Bool					get_finched_flage(t_coder *coder);
long					get_last_compiling(t_coder *coder);
t_Bool					cheak_burnout(t_coder *coder);
t_monitor_arg			*create_monitor(t_data *data, t_coder *coder_list);
void					free_coders(t_monitor_arg *monitor_arg);
long					get_clodown(t_dongle *dongle);
void					set_last_compiling(t_coder *coder, long time);
void					set_finched_flage(t_coder *coder, t_Bool flage);
int						get_best(t_queue *queue, int best, char *algo);
int						higher_priority(t_coder *a, t_coder *b, char *algo);
void					swap_queue(t_queue *queue, int i, int best);
void					check_start(t_coder *coder);
void					start_simulation(t_data *data, t_coder *coder_list,
							int thread_count);
t_Bool	thread_ruten(t_coder *coder);
#endif