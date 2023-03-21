#include "hotel.h"

void* cleaner(void *args){

    int id = *(int*)args;
    int k = 2; //proportionality constant
    
    while(1){
        //pthread_cond_wait(&clean_cond, &cond_mutex);

        while(1){
            //assign a dirty room
            sem_wait(&semc);
            if(!no_uncleaned){
                sem_post(&semc);
                break;
            }
            int curr_roomid  = no_uncleaned - 1;
            no_uncleaned--;
            sem_post(&semc);

            //clean
            cout<< "Cleaner "<<id<<" is cleaning room "<<curr_roomid<<". \n";
            Room *curr_room = rooms+curr_roomid;
            int clean_time = k * (curr_room->guests_stayed[0].stay_time 
                                        + curr_room->guests_stayed[1].stay_time);

            sleep(clean_time); 

            //mark room as clean
            curr_room->clean = true;
        }

    }
    
    pthread_exit(0);
}
