#include "Threading.h"

CThread* create_Thread(void* function){
    CThread* thread = (CThread*)malloc(sizeof(CThread));
    TArgs* args = (TArgs*)malloc(sizeof(TArgs));

    args->self = thread;
    
    thread->alive = 1;
    thread->funciton = function;
    thread->vargp = args;
    if (pthread_create(&thread->thread_id, NULL, thread->funciton, thread->vargp)){
        free(thread);
        return NULL;
    }

    return thread;
}

void kill_Thread(CThread* thread){
    thread->alive = 0;
}

void destroy_Thread(CThread** thread){
    if (thread == NULL)
        return;

    kill_Thread(*thread);
    free((*thread)->vargp);
    free(*thread);
    thread = NULL;
}