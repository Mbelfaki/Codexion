
#ifndef CODER_H
# define CODER_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef enum Bool
{
	FALSE,
	TRUE,

}						Bool;

typedef struct Data_s	Data_t;
typedef struct Coder_s	Coder_t;
typedef struct Dongle_s	Dongle_t;
typedef struct queue_s	queue_t;
typedef struct Data_s
{
	long				values[7];
	long				time;
	char				*algo;

}						Data_t;
struct					queue_s
{
	Coder_t				**coders;
	int					front;
	int					rear;
	int					size;
};

struct					Dongle_s
{
	int					id;
	Bool				taken;
	pthread_cond_t		cond;
	queue_t				*queue;
	pthread_mutex_t		*lock;
	long				dongle_cooldown;
	long				time_to_reaelse;
};

struct					Coder_s
{
	Data_t				*data;
	int					id;
	Dongle_t			*dongle_left;
	Dongle_t			*dongle_right;
	pthread_mutex_t		*commen_lock;
	
};
Dongle_t				*request_dongle(Coder_t *Coder, int i);
void					get_dongle(Dongle_t *dongle, Coder_t *coder);
void					release_dongles(Coder_t *Coder);
void					create_list_thread(Data_t *data, pthread_t *thread_list,
							void *(*coder_thread)(void *));
void					thread_list_join(pthread_t *thread_list,
							int thread_number);
void					*coder_thread(void *arg);
#endif