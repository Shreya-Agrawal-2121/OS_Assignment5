#include "hotel.h"

int main()
{

    cout<<"Enter N, X and Y respectively: ";
    cin>>N>>X>>Y;
    
    // allocate memory and initialise rooms
    rooms = (Room* )malloc(N*sizeof(Room));
    for(int i=0; i<N; i++){
        Room* curr_room = rooms+i;
        curr_room->roomid = i;
        curr_room->clean = true;
        curr_room->num_guests_stayed = 0;
        curr_room->guests_stayed[0].guestid = -1;
        curr_room->guests_stayed[1].guestid = -1;
    }
    
    //declare and create threads
    pthread_t tguest[Y], tcleaner[X];
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    for(int i=0; i<X+Y; i++){
        if(i<X){
            pthread_create(&tcleaner[i], &attr, cleaner, NULL);
        }
        else{
            pthread_create(&tguest[i-X], &attr, guest, NULL);
        }
    }

    //declare and initialise semaphores
    sem_init(semp, 0, N);

    for(int i=0; i<X+Y; i++){
        if(i<X){
            pthread_join(tcleaner[i], NULL);
        }
        else{
            pthread_join(tguest[i-X], NULL);
        }
    }
    sem_destroy(semp);

}