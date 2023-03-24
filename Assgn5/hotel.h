#ifndef __HOTEL__H
#define __HOTEL__H
#include <bits/stdc++.h>
#include <iostream>
#include <pthread.h>
#include <semaphore.h>

using namespace std;

typedef struct _stay{
    int guestid;
    int stay_time;
    bool is_staying;
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
    bool is_removed;
}Guest;

typedef struct _cleaner{
    int cleanerid;
    int cleaning_dur;
}Cleaner;

extern Room* rooms;
extern Guest *guests;
extern sem_t semp,semc;
extern int N;
extern int no_uncleaned;
extern bool all_cleaned;
extern bool all_uncleaned;
void* cleaner(void *args);
void* guest(void *args);
extern pthread_cond_t clean_cond;
extern pthread_mutex_t cond_mutex,u_mutex;
#endif
