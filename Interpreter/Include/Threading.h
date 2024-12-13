#pragma once
#include <pthread.h>
#include <stdlib.h>

typedef struct CPU CPU;

typedef struct CThread{
    pthread_t thread_id;
    void* funciton;
    void* vargp;

    char alive;
} CThread;

typedef struct TArgs{
    CPU* cpu;
    CThread* self;
} TArgs;


CThread* create_Thread(void* function);
void kill_Thread(CThread* thread);
void destroy_Thread(CThread** thread);
