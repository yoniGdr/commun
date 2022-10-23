#ifndef __SM_DEFS_H__
#define __SM_DEFS_H__
#include <pthread.h>

#define MAX_QUEUED_EVENTS 10
#define ERR_QUEUE_FULL -1

typedef int Evt_t;

class EvtQueue {
    Evt_t array[MAX_QUEUED_EVENTS];
    int head;
    int tail;
    int num; 
    pthread_mutex_t m; 
    pthread_cond_t c;  
 public:
    EvtQueue();
    int insert(Evt_t evt);
    Evt_t extract();
};
    
class StateMachine {
    EvtQueue queue;
    pthread_t thread_id;
 public:
    StateMachine();
    void send(Evt_t evt);
    EvtQueue & get_queue() { return queue; }
    virtual void handler(Evt_t evt) = 0;
};

#endif 
