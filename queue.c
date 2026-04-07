
#include "parcing.h"
#include "queue.h"

queue_t	*create_queue(int size)
{
	queue_t	*queue;

	queue = malloc(sizeof(queue_t));
	if(!queue)
	printf("wwww6\n");
	queue->coders = malloc(sizeof(Coder_t *) * size);
	if(!queue->coders)
	printf("wwww7\n");
	queue->size = size;
	queue->rear = queue->front = -1;
	return (queue);
}

void	enqueue(queue_t *queue, Coder_t *Coder)
{
	if (queue->front == (queue->rear + 1) % queue->size)
	{
		printf("Queue is full\n");
		return ;
	}
	else if (queue->front == -1)
		queue->front = queue->rear = 0;
	else
		queue->rear = (queue->rear + 1) % queue->size;
	queue->coders[queue->rear] = Coder;
	printf("%d", Coder->id);
}

Coder_t	*dequeue(queue_t *queue)
{
	Coder_t	*Coder;

	if (queue->front == -1)
	{
		printf("Queue is empty\n");
		return (NULL);
	}
	Coder = queue->coders[queue->front];
	queue->coders[queue->front] = NULL;
	if (queue->front == queue->rear)
		queue->front = queue->rear = -1;
	else
		queue->front = (queue->front + 1) % queue->size;
	return (Coder);
}

Bool	istop(queue_t *queue, Coder_t *coder)
{
	if (queue->coders[queue->front] == coder)
		return (TRUE);
	else
		return (FALSE);
}

// int main(){

// queue_t *q = create_queue(2);
// Coder_t	*coder1 = malloc(sizeof(Coder_t));
// Coder_t	*coder2 = malloc(sizeof(Coder_t));
// enqueue(q,coder1);
// dequeue(q);
// enqueue(q,coder2);
// printf("%d",istop(q,coder1));
// printf("%d",istop(q,coder2));
// }