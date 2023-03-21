#include "hotel.h"

void *guest(void *args)
{
    int idx = *((int *)args);
    bool has_requested = false;
    while (1)
    {
        if (guests[idx].room_no == -1)
        {
            if (guests[idx].is_removed == true)
            {
                has_requested = false;
                guests[idx].is_removed = false;
            }
            int rand_sleep = rand() % 11 + 10;
            cout << "Guest " << idx << " sleeping for " << rand_sleep << " seconds\n";
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
                    guests[g_id].is_removed = true;
                    cout << "Guest " << g_id << " removed from Room " << i << "\n";

                    int rand_stay = rand() % 21 + 10;
                    rooms[i].guests_stayed[1].stay_time = rand_stay;
                    rooms[i].guests_stayed[1].is_staying = true;
                    rooms[i].num_guests_stayed++;
                    cout << "Guest " << idx << " allotted to Room " << i << " for duration of " << rand_stay << "\n";
                    sleep(rand_stay);
                    rooms[i].clean = false;
                    guests[idx].room_no = -1;
                    has_requested = false;

                    sem_post(&semp);
                    pthread_mutex_lock(&cond_mutex);
                    no_uncleaned++;
                    cout << "No of uncleaned rooms " << no_uncleaned << "\n";
                    if (no_uncleaned == N)
                    {
                        pthread_cond_broadcast(&clean_cond);
                    }
                    pthread_mutex_unlock(&cond_mutex);

                    continue;
                }
            }
            if (!has_requested)
            {
                sem_wait(&semp);
                int i = -1;
                for (i = 0; i < N; i++)
                {
                    if (rooms[i].num_guests_stayed == 0)
                    {
                        break;
                    }
                }
                if (i < N)
                {
                    rooms[i].guests_stayed[rooms[i].num_guests_stayed].guestid = idx;
                    int rand_stay = rand() % 21 + 10;
                    rooms[i].guests_stayed[rooms[i].num_guests_stayed].stay_time = rand_stay;
                    rooms[i].guests_stayed[rooms[i].num_guests_stayed].is_staying = true;
                    rooms[i].num_guests_stayed++;
                    guests[idx].room_no = i;
                    cout << "Guest " << idx << " allotted to Room " << i << " for duration of " << rand_stay << "\n";
                    sleep(rand_stay);
                    if (guests[idx].room_no != -1)
                    {

                        // cout << "Guest " << idx << " stayed in Room " << i << " for duration of " << rand_stay << "\n";
                        rooms[guests[idx].room_no].guests_stayed[0].is_staying = false;
                        has_requested = false;
                        sem_post(&semp);
                    }
                    else
                        has_requested = true;
                    guests[idx].room_no = -1;
                }
                else
                {
                    for (i = 0; i < N; i++)
                    {
                        if (rooms[i].num_guests_stayed == 1 && rooms[i].guests_stayed[0].is_staying == false)
                        {
                            break;
                        }
                    }
                    if (i < N)
                    {
                        rooms[i].guests_stayed[rooms[i].num_guests_stayed].guestid = idx;
                        int rand_stay = rand() % 21 + 10;
                        rooms[i].guests_stayed[rooms[i].num_guests_stayed].stay_time = rand_stay;
                        rooms[i].guests_stayed[rooms[i].num_guests_stayed].is_staying = true;
                        rooms[i].num_guests_stayed++;
                        guests[idx].room_no = i;
                        cout << "Guest " << idx << " allotted to Room " << i << " for duration of " << rand_stay << "\n";
                        sleep(rand_stay);
                        rooms[i].clean = false;
                        guests[idx].room_no = -1;
                        has_requested = false;

                        sem_post(&semp);
                        pthread_mutex_lock(&cond_mutex);
                        no_uncleaned++;
                        cout << "No of uncleaned rooms " << no_uncleaned << "\n";

                        if (no_uncleaned == N)
                            pthread_cond_broadcast(&clean_cond);
                        pthread_mutex_unlock(&cond_mutex);
                    }
                    else
                    {
                        guests[idx].room_no = -1;

                        has_requested = true;
                    }
                }
            }
            else
            {
                guests[idx].room_no = -1;
            }
        }
    }
    pthread_exit(0);
}