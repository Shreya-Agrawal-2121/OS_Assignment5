#include "hotel.h"
Room *rooms;
Guest *guests;
sem_t semp,semc;
int N;
int no_uncleaned = 0;
bool all_cleaned = true;
bool all_uncleaned = false;
pthread_cond_t clean_cond;
pthread_mutex_t cond_mutex,u_mutex;
int main()
{

    int X, Y;
    cout << "Enter N, X and Y respectively: ";
    cin >> N >> X >> Y;
    int guest_idx[Y];
    int cleaner_idx[X];
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
    for(int i = 0; i < X; i++){
        cleaner_idx[i] = i;
    }
    // declare and create threads
    pthread_t tguest[Y], tcleaner[X];
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    for (int i = 0; i < X; i++)
    {
        pthread_create(&tcleaner[i], &attr, cleaner, &cleaner_idx[i]);
    }
    for (int i = 0; i < Y; i++)
    {
        pthread_create(&tguest[i], &attr, guest, &guest_idx[i]);
    }
    // declare and initialise semaphores
    pthread_mutex_init(&cond_mutex,NULL);
    pthread_mutex_init(&u_mutex,NULL);
    sem_init(&semp, 0, N);
    sem_init(&semc, 1, 1);
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