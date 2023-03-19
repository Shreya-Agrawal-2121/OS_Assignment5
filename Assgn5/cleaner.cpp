#include "hotel.h"

void* cleaner(void *args){
    
    sem_wait(semp);
    int flag=1;
    while (flag)
    {
        for (int i=0;i<N;i++)
        {
            Room* curr_room = rooms+i;
            if (curr_room->num_guests_stayed==2)
                continue;
            else
            {
                flag=0;
            }
        }
    }
    int count=N;
    while(count)
    {
        int temp=rand()%N;
        Room* curr_room = rooms+temp;
        while(1) 
        {
            if (curr_room->clean!=false)
            {
                temp=rand()%N;
                Room* curr_room = rooms+temp;
            }
            else
                break;
        }
        int time;                       //todo: proportionality time needs to be handled
        sleep(time);
        curr_room->clean=true;
        count--;
    }
    sem_post(semp);
    pthread_exit(0);
}