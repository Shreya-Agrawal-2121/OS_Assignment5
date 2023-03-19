#include "hotel.h"

void* cleaner(void *args){
    pthread_exit(0);
}