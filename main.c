
#include <pthread.h>
#include <unistd.h>
#include "parcing.h"

int main(int argc, char **argv){
int *values;
if(cheak_arges(argc, &argv[1]))
    values = getvalues(argc, &argv[1]);

    

}