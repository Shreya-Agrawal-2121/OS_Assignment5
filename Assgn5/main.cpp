#include "hotel.h"
Room *rooms;
Guest *guests;
sem_t semp, semc;

int N;
int no_uncleaned = 0;
int main()
{

    int X, Y;
    cout << "Enter N, X and Y respectively: ";
    cin >> N >> X >> Y;
    int guest_idx[Y];
    // allocate memory and initialise rooms
    rooms = (Room *)malloc(N * sizeof(Room));
    guests = (Guest *)malloc(Y * sizeof(Guest));
    for (int i = 0; i < N; i++)
    {
        Room *curr_room = rooms + i;
        curr_room->roomid = i;
        curr_room->clean = true;
        curr_room->num_guests_stayed = 0;
        curr_room->guests_stayed[0].guestid = -1;
        curr_room->guests_stayed[1].guestid = -1;
    }
    for (int i = 0; i < Y; i++)
    {
        guests[i].guestid = i;
        guests[i].priority = rand() % Y + 1;
        guests[i].room_no = -1;
        guest_idx[i] = i;
        guests[i].is_removed = false;
    }

    // declare and initialise semaphores

    sem_init(&semp, 0, N);
    sem_init(&semc, 1, 1);

    // declare and create threads
    pthread_t tguest[Y], tcleaner[X];
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    // pthread_cond_init(&clean_cond, NULL);
    // pthread_mutex_init(&cond_mutex, NULL);

    for (int i = 0; i < X; i++)
    {
        pthread_create(&tcleaner[i], &attr, cleaner, &i);
    }
    for (int i = 0; i < Y; i++)
    {
        pthread_create(&tguest[i], &attr, guest, &guest_idx[i]);
    }

    for (int i = 0; i < X + Y; i++)
    {
        if (i < X)
        {
            pthread_join(tcleaner[i], NULL);
        }
        else
        {
            pthread_join(tguest[i - X], NULL);
        }
    }
    sem_destroy(&semp);
}
