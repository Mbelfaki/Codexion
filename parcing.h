#ifndef PARCING_H
# define PARCING_H
# include "coder.h"
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
Data_t	*getdata(int argc, char **argv);
int		cheak_arges(int argc, char **argv);
long	get_time(void);

#endif