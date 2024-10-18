#ifndef __TM_HEAP__C
#define __TM_HEAP__C 123
#include<tm_heap.h>
#include<tm_array.h>
#include<stdlib.h>


Heap *createHeap(int (*comparator) (void *,void *),int *success)
{
int succ;
Heap *heap=NULL;
if(success) *success=false;
if(comparator==NULL) return heap;
heap=(Heap *)malloc(sizeof(Heap));
if(heap==NULL) return heap;
heap->array=createArray(&succ);
if(!succ)
{
free(heap);
return NULL;
}
heap->size=0;
heap->comparator=comparator;
if(success) *success=true;
return heap;
}

void addToHeap(Heap *heap,void *element,int *success)
{
int succ,ri,ci,weight;
void *riValue,*ciValue;
if(success) *success=false;
if(heap==NULL) return;
setElementOfArray(heap->array,heap->size,element,&succ);
if(!succ) return;
heap->size++;
ci=heap->size-1;
while(ci>0)
{
ri=(ci-1)/2;
ciValue=getElementOfArray(heap->array,ci);
riValue=getElementOfArray(heap->array,ri);
weight=heap->comparator(ciValue,riValue);
if(weight<0)
{
setElementOfArray(heap->array,ci,riValue,&succ);
setElementOfArray(heap->array,ri,ciValue,&succ);
ci=ri;
}
else break;
}
if(success) *success=true;
}

void *removeFromHeap(Heap *heap,int *success)
{
void *element,*lastElement,*riValue,*swiValue;
int ri,lci,rci,swi,succ,UpperBound;
if(success) *success=false;
if(heap==NULL) return NULL;
if(heap->size==0) return NULL;
element=getElementOfArray(heap->array,0);
lastElement=getElementOfArray(heap->array,heap->size-1);
setElementOfArray(heap->array,0,lastElement,&succ);
heap->size--;
UpperBound=heap->size-1;
ri=0;
while(ri<UpperBound)
{
lci=(rci*2)+1;
if(lci>UpperBound) break;
rci=lci+1;
if(rci>UpperBound) swi=lci;
else
{
if(heap->comparator(getElementOfArray(heap->array,lci),getElementOfArray(heap->array,rci))<0)
swi=lci;
else swi=rci;
}
riValue=getElementOfArray(heap->array,ri);
swiValue=getElementOfArray(heap->array,swi);
if(heap->comparator(swiValue,riValue)<0)
{
setElementOfArray(heap->array,swi,riValue,&succ);
setElementOfArray(heap->array,ri,swiValue,&succ);
ri=swi;
}
else break;
}//Heap Adjustment Loop Ends
if(success) *success=true;
return element;
}
void *elementAtTopOfHeap(Heap *heap,int *success)
{
if(success) *success=false;
if(heap==NULL) return NULL;
if(heap->size==0) return NULL;
if(success) *success=true;
return getElementOfArray(heap->array,0);
}
int getSizeOfHeap(Heap *heap)
{
if(heap==NULL) return 0;
return heap->size;
}
void destroyHeap(Heap *heap)
{
if(heap==NULL) return;
destroyArray(heap->array);
free(heap);
}


void *getElementFromHeap(Heap *heap,int index,int *success)
{
void *element=NULL;
if(success) *success=false;
if(heap==NULL) return element;
if(index<0 || index>=heap->size) return element;
element=getElementOfArray(heap->array,index);
if(success) *success=true;
return element;
}
void updateElementInHeap(Heap *heap,int index,void *element,int *success)
{
int succ,ri,ci,weight,swi,lci,rci,goDown,upperBound;
void *riValue,*ciValue,*swiValue;
if(success) *success=false;
if(heap==NULL) return;
if(index<0 || index>=heap->size) return;
setElementOfArray(heap->array,index,element,&succ);
if(index==0) goDown=true;
else if(index==heap->size-1) goDown=false;
else
{
ci=index;
ri=(ci-1)/2;
ciValue=getElementOfArray(heap->array,ci);
riValue=getElementOfArray(heap->array,ri);
weight=heap->comparator(ciValue,riValue);
if(weight<0) goDown=false;
else goDown=true;
}
if(goDown)
{
upperBound=heap->size-1;
ri=index;
while(ri<upperBound)
{
lci=(ri*2)+1;
if(lci>upperBound) break;
rci=lci+1;
if(rci>upperBound) swi=lci;
else
{
if(heap->comparator(getElementOfArray(heap->array,lci),getElementOfArray(heap->array,rci))<0)
swi=lci;
else swi=rci;
}
riValue=getElementOfArray(heap->array,ri);
swiValue=getElementOfArray(heap->array,swi);
if(heap->comparator(swiValue,riValue)<0)
{
setElementOfArray(heap->array,swi,riValue,&succ);
setElementOfArray(heap->array,ri,swiValue,&succ);
ri=swi;
}
else break;
}
}
else //logic to heapify upwards
{
ci=index;
while(ci>0)
{
ri=(ci-1)/2;
ciValue=getElementOfArray(heap->array,ci);
riValue=getElementOfArray(heap->array,ri);
weight=heap->comparator(ciValue,riValue);
if(weight<0)
{
setElementOfArray(heap->array,ci,riValue,&succ);
setElementOfArray(heap->array,ri,ciValue,&succ);
ci=ri;
}
else break;
}
}
if(success) *success=true;
}
#endif