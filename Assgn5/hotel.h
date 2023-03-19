#include <bits/stdc++.h>
#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

using namespace std;

typedef struct _stay{
    int guestid;
    int stay_time;
}Stay;

typedef struct _room{
    Stay guests_stayed[2];
    int roomid;
    int num_guests_stayed;
    bool clean;
}Room;

typedef struct _guest{
    int guestid;
    int room_no;
    int priority;
}Guest;

typedef struct _cleaner{
    int cleanerid;
    int cleaning_dur;
}Cleaner;

Room* rooms;

void* cleaner(void *args);
void* guest(void *args);

int N, X, Y;
sem_t *semp;