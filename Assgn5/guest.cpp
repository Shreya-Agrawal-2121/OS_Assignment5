#include "hotel.h"

void *guest(void *args)
{
    int idx = *((int *)args);
    while (1)
    {
        if (guests[idx].room_no == -1)
        {
            int rand_sleep = rand()%11 + 10;
            sleep(rand_sleep);
            int semp_value;
            sem_getvalue(&semp, &semp_value);
            bool found = false;
            if (semp_value <= 0)
            {
                int i;
                for (i = 0; i < N; i++)
                {
                    if (rooms[i].num_guests_stayed == 1)
                    {
                        int g_id = rooms[i].guests_stayed[0].guestid;
                        if (guests[g_id].priority < guests[idx].priority)
                        {
                            found = true;
                            break;
                        }
                    }
                }
                if (found)
                {
                    int g_id = rooms[i].guests_stayed[0].guestid;
                    rooms[i].guests_stayed[1].guestid = idx;
                    guests[g_id].room_no = -1;
                    guests[idx].room_no = i;
                    int rand_stay = rand()%21 + 10;
                    rooms[i].guests_stayed[1].stay_time = rand_stay;
                    rooms[i].num_guests_stayed++;
                    sleep(rand_stay);
                    rooms[i].clean  = false;
                    no_uncleaned++;
                    if(guests[idx].room_no != -1)
                        sem_post(&semp);
                    continue;
                }
            }
            sem_wait(&semp);
                int i;
                for(i = 0; i < N; i++){
                    if(rooms[i].num_guests_stayed == 0){
                        break;
                    }
                }
                rooms[i].guests_stayed[0].guestid  = idx;
                rooms[i].num_guests_stayed++;
                guests[idx].room_no = i;
                int rand_stay = rand()%21 + 10;
                rooms[i].guests_stayed[0].stay_time = rand_stay;
                sleep(rand_stay);
            if(guests[idx].room_no != -1)
                sem_post(&semp);
            
        
    }
    
}
pthread_exit(0);
}