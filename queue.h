#ifndef QUEUE_H
# define QUEUE_H

# include "coder.h"
queue_t	*create_queue(int size);
void	enqueue(queue_t *queue, Coder_t *coder);
Coder_t	*dequeue(queue_t *queue);
Bool	istop(queue_t *queue, Coder_t *coder);
#endif
