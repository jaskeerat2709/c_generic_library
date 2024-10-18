#ifndef __TM_PQUEUE__C
#define __TM_PQUEUE__C 123
#include<tm_common.h>
#include<tm_heap.h>
#include<tm_pqueue.h>
#include<stdlib.h>

PQueue * createPQueue(int (*predicate)(void *,void *),bool *success)
{
PQueue *pQueue;
Heap *heap;
heap=createHeap(predicate,success);
if(*success==false) return NULL;
pQueue=(PQueue *)malloc(sizeof(PQueue));
if(pQueue==NULL)
{
destroyHeap(heap);
if(success) *success=false;
return NULL;
}
pQueue->heap=heap;
if(success) *success=true;
return pQueue;
}

void clearPQueue(PQueue *pQueue)
{
int succ;
if(pQueue==NULL) return;
if(pQueue->heap) return;
while(getSizeOfHeap(pQueue->heap)>0)
{
removeFromHeap(pQueue->heap,&succ);
}
}

void destroyPQueue(PQueue *pQueue)
{
if(pQueue==NULL) return;
if(pQueue->heap==NULL) return;
destroyHeap(pQueue->heap);
free(pQueue);
}

void addToPQueue(PQueue *pQueue,void *ptr,bool *success)
{
if(success) *success=false;
if(pQueue==NULL || pQueue->heap==NULL) return;
addToHeap(pQueue->heap,ptr,success);
}

bool isPQueueEmpty(PQueue *pQueue)
{
if(pQueue==NULL) return true;
if(pQueue->heap==NULL) return true;
if(getSizeOfHeap(pQueue->heap)==0) return true;
return false;
}

void * removeFromPQueue(PQueue *pQueue,bool *success)
{
void *ptr;
if(success) *success=false;
if(isPQueueEmpty(pQueue)) return NULL;
ptr=removeFromHeap(pQueue->heap,success);
if(success) *success=true;
return ptr;
}


int getSizeOfPQueue(PQueue *pQueue)
{
if(pQueue==NULL || pQueue->heap==NULL) return 0;
return getSizeOfHeap(pQueue->heap);
}


void * elementAtFrontOfPQueue(PQueue *pQueue,bool *success)
{
void *ptr;
if(success) *success=false;
if(isPQueueEmpty(pQueue)) return NULL;
ptr=elementAtTopOfHeap(pQueue->heap,success);
if(success) *success=true;
return ptr;
}

void *getElementFromPQueue(PQueue *pQueue,int index,int *success)
{
void *element=NULL;
if(success) *success=false;
if(pQueue==NULL) return element;
element=getElementFromHeap(pQueue->heap,index,success);
if(success) *success=true;
return element;
}
void updateElementInPQueue(PQueue *pQueue,int index,void *element,int *success)
{
if(success) *success=false;
if(pQueue==NULL) return;
updateElementInHeap(pQueue->heap,index,element,success);
}

#endif