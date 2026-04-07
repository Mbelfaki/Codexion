
#include "coder.h"
#include "parcing.h"
#include "queue.h"

Dongle_t	*request_dongle(Coder_t *Coder, int i)
{
	Dongle_t	*dongle;

	if (i == 0)
		dongle = Coder->dongle_left;
	else if (i == 1)
		dongle = Coder->dongle_right;
	// printf("i am in");
	pthread_mutex_lock(dongle->lock);
	enqueue(dongle->queue, Coder);
	pthread_mutex_unlock(dongle->lock);
	return (dongle);
}

void	get_dongle(Dongle_t *dongle, Coder_t *coder)
{
	pthread_mutex_lock(dongle->lock);
	// printf("stuts of %d is %d\n", coder->id, dongle->taken);
	if (dongle->taken)
	{
		// printf("%d  bolock\n", coder->id);
		pthread_cond_wait(&dongle->cond, dongle->lock);
		// printf("%dunbolock\n", coder->id);
	}
	pthread_mutex_unlock(dongle->lock);
	if (!istop(dongle->queue, coder))
		printf("i am %d still in %d \n", coder->id, dongle->id);
	while (!istop(dongle->queue, coder) || dongle->dongle_cooldown
		+ dongle->time_to_reaelse > get_time())
		;
	// printf("stuts of %d is %d is out\n", coder->id, dongle->taken);
	pthread_mutex_lock(dongle->lock);
	dequeue(dongle->queue);
	dongle->taken = TRUE;
	pthread_mutex_unlock(dongle->lock);
}

void	release_dongles(Coder_t *Coder)
{
	pthread_mutex_lock(Coder->dongle_right->lock);
	pthread_mutex_lock(Coder->dongle_left->lock);
	// printf("%d release\n", Coder->id);
	pthread_cond_broadcast(&Coder->dongle_right->cond);
	pthread_cond_broadcast(&Coder->dongle_left->cond);
	Coder->dongle_left->taken = FALSE;
	Coder->dongle_right->taken = FALSE;
	Coder->dongle_left->time_to_reaelse = get_time();
	pthread_mutex_unlock(Coder->dongle_right->lock);
	pthread_mutex_unlock(Coder->dongle_left->lock);
}
void display_data(Coder_t *Coder, char * massge){
		pthread_mutex_lock(Coder->dongle_right->lock);
		printf("%ld %d  %s\n",massge, get_time() - Coder->data->time,Coder->id);
		pthread_mutex_lock(Coder->dongle_right->lock);

}
void	*coder_thread(void *arg)
{
	Coder_t		*Coder;
	Dongle_t	*dongle;
	int			i;

	Coder = (Coder_t *)arg;
	i = 0;
	while (i < Coder->data->values[5])
	{
		dongle = request_dongle(Coder, Coder->id % 2);
		get_dongle(dongle, Coder);
		printf("%ld %d  has taken a dongle\n", get_time() - Coder->data->time,
			Coder->id);
		dongle = request_dongle(Coder, (Coder->id + 1) % 2);
		get_dongle(dongle, Coder);
		printf("%ld  %d has taken a dongle\n", get_time() - Coder->data->time,
			Coder->id);
		printf("%ld %d is compiling\n", get_time() - Coder->data->time,
			Coder->id);
		usleep(Coder->data->values[2]);
		release_dongles(Coder);
		printf("%ld %d is debugging\n", get_time() - Coder->data->time,
			Coder->id);
		usleep(Coder->data->values[3]);
		printf("%ld %d is refactoring\n", get_time() - Coder->data->time,
			Coder->id);
		usleep(Coder->data->values[4]);
		i++;
	}
	return (NULL);
}

void	thread_list_join(pthread_t *thread_list, int thread_number)
{
	int	i;

	i = 0;
	while (i < thread_number)
	{
		pthread_join(thread_list[i], NULL);
		i++;
	}
}

void	create_list_thread(Data_t *data, pthread_t *thread_list,
		void *(*coder_thread)(void *))
{
	int				i;
	Coder_t			*Coder_list;
	Dongle_t		*dongle_list;
	pthread_mutex_t	*lock_list;

	i = 0;
	Coder_list = malloc(sizeof(Coder_t) * data->values[0]);
	if(!Coder_list)
	printf("wwww1\n");
	dongle_list = malloc(sizeof(Dongle_t) * data->values[0]);
	if(!dongle_list)
	printf("wwww2\n");
	dongle_list[0].id = 0;
	lock_list = malloc(sizeof(pthread_mutex_t) * data->values[0]);
	if(!lock_list)
	printf("wwww3\n");
	while (i < data->values[0])
	{
		pthread_mutex_init(&lock_list[i], NULL);
		dongle_list[i].queue = create_queue(2);
		dongle_list[i].dongle_cooldown = data->values[6];
		Coder_list[i].data = data;
		Coder_list[i].id = i + 1;
		dongle_list[i + 1].id = i + 1;
		dongle_list[i].lock = &lock_list[i];
		dongle_list[i].taken = FALSE;
		Coder_list[i].dongle_left = &dongle_list[i];
		Coder_list[i].dongle_right = &dongle_list[(i + 1) % data->values[0]];
		pthread_create(&thread_list[i], NULL, coder_thread, &Coder_list[i]);
		i++;
	}
	thread_list_join(thread_list, i);
}
