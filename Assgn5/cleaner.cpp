#include "hotel.h"

void *cleaner(void *args)
{

    int id = *(int *)args;
    int k = 2; // proportionality constant

    while (1)
    {
        pthread_mutex_lock(&cond_mutex);
        while (all_uncleaned == false)
            pthread_cond_wait(&clean_cond, &cond_mutex);
        pthread_mutex_unlock(&cond_mutex);
            // assign a dirty room
            pthread_mutex_lock(&cond_mutex);
            if (!no_uncleaned)
            {
                
                all_cleaned = true;
                all_uncleaned = false;
                
                no_uncleaned = 0;
                pthread_mutex_unlock(&cond_mutex);
                break;
            }
            int curr_roomid = no_uncleaned - 1;
            no_uncleaned--;
            pthread_mutex_unlock(&cond_mutex);

            // clean
            cout << "Cleaner " << id << " is cleaning room " << curr_roomid << ". \n";
            Room *curr_room = rooms + curr_roomid;
            int clean_time = k * (curr_room->guests_stayed[0].stay_time + curr_room->guests_stayed[1].stay_time);

            sleep(clean_time);

            // mark room as clean
            curr_room->clean = true;
            curr_room->num_guests_stayed = 0;
            curr_room->guests_stayed[0].guestid = -1;
            curr_room->guests_stayed[0].is_staying = false;
            curr_room->guests_stayed[0].stay_time = -1;

            curr_room->guests_stayed[1].guestid = -1;
            curr_room->guests_stayed[1].is_staying = false;
            curr_room->guests_stayed[1].stay_time = -1;
        //}
    }

    pthread_exit(0);
}