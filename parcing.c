#include "parcing.h"

static int is_digete(char *str){

int i ;
i=0;

while(str[i]){

if (str[i] < '0'  || str[i] > '9') 
 return 0;
i++;

}
return 1;
}
static void getupper(char *str){

    int i = 0;
    while (str[i]){
    if(str[i] >= 'a' && str[i] <= 'z')
        str[i] = str[i] - 32;
        i++;
    }
}
int cheak_arges(int argc, char **argv){
int i;
i = 0;
if (argc != 9){
    printf("wrong number of args \n");
return 0;}
while(i < argc - 2){
if(!is_digete(argv[i])){
printf("args must be digeites \n");
return 0;}
i++;
}
getupper(argv[i]);

if(strcmp(argv[i],"FIFO") && strcmp(argv[i],"EDF")){

printf("FIFO or   EDF\n");

    return 0;}
return 1;



}

int * getvalues(int argc, char **argv){
int i=0;
int *ptr = malloc(sizeof(int) * (argc - 2));
while(i < argc - 2){

ptr[i] = atoi(argv[i]);

i++;
}



return ptr;

}