#ifndef __TM_PQUEUE__H
#define __TM_PQUEUE__H 123
#include<tm_common.h>
#include<tm_heap.h>

typedef struct __$_tm__pQueue
{
Heap *heap;
}PQueue;

PQueue *createPQueue(int (*predicate)(void *,void *),bool *success);
void addToPQueue(PQueue *pQueue,void *ptr,bool *success);
void * removeFromPQueue(PQueue *pQueue,bool *success);
int getSizeOfPQueue(PQueue *pQueue);
void * elementAtFrontOfPQueue(PQueue *pQueue,bool *success);
void *getElementFromPQueue(PQueue *pQueue,int index,int *success);
void updateElementInPQueue(PQueue *pQueue,int index,void *element,int *success);
bool isPQueueEmpty(PQueue *pQueue);
void clearPQueue(PQueue *pQueue);
void destroyPQueue(PQueue *pQueue);
#endif