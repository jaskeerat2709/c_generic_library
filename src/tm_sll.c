#ifndef __TM_SLL__C
#define __TM_SLL__C 123
#include<stdio.h>
#include<stdlib.h>
#include<tm_sll.h>

/*=================================FUNCTIONS START=====================================*/

//====================================CREATION===========================================


SinglyLinkedList *createSinglyLinkedList(bool *success)
{
SinglyLinkedList *singlyLinkedList;
if(success) *success=false;
singlyLinkedList=(SinglyLinkedList *)malloc(sizeof(SinglyLinkedList));
if(singlyLinkedList==NULL) return NULL;
singlyLinkedList->start=NULL;
singlyLinkedList->end=NULL;
singlyLinkedList->size=0;
if(success) *success=true;
return singlyLinkedList;
}


//===================================ADD TO SLL==========================================


void addToSinglyLinkedList(SinglyLinkedList *singlyLinkedList,void *ptr,bool *success)
{
SinglyLinkedListNode *node;
if(success) *success=false;
if(singlyLinkedList==NULL) return;
node=(SinglyLinkedListNode *)malloc(sizeof(SinglyLinkedListNode));
if(node==NULL) return;
node->ptr=ptr;
node->next=NULL;
if(singlyLinkedList->start==NULL)
{
singlyLinkedList->start=node;
singlyLinkedList->end=node;
}
else
{
singlyLinkedList->end->next=node;
singlyLinkedList->end=node;
}
singlyLinkedList->size++;
if(success) *success=true;
}

//=================================INSERT INTO SLL=======================================

void insertIntoSinglyLinkedList(SinglyLinkedList *singlyLinkedList,int index,void *ptr,bool *success)
{
SinglyLinkedListNode *p1,*p2,*node;
int x;
if(success) *success=false;
if(singlyLinkedList==NULL) return;
if(index<0 || index>singlyLinkedList->size) return;
if(index==singlyLinkedList->size) //ADD AT END
{
addToSinglyLinkedList(singlyLinkedList,ptr,success);
return;
}
node=(SinglyLinkedListNode *)malloc(sizeof(SinglyLinkedListNode));
node->ptr=ptr;
node->next=NULL;
if(node==NULL) return;
if(index==0)  //ADD AT START
{
node->next=singlyLinkedList->start;
singlyLinkedList->start=node;
singlyLinkedList->size++;
if(success) *success=true;
return;
}
p1=singlyLinkedList->start;
x=0;
while(x<index)
{
p2=p1;
p1=p1->next;
x++;
}
p2->next=node;
node->next=p1;
singlyLinkedList->size++;
if(success) *success=true;
}


//===================================REMOVE FROM SLL=====================================


void * removeFromSinglyLinkedList(SinglyLinkedList *singlyLinkedList,int index,bool *success)
{
SinglyLinkedListNode *p1,*p2;
void *ptr;
int x;
if(success) *success=false;
if(singlyLinkedList==NULL) return NULL;
if(singlyLinkedList->start==NULL) return NULL;
if(index<0 || index>=singlyLinkedList->size) return NULL;
p1=singlyLinkedList->start;
x=0;
while(x<index)
{
p2=p1;
p1=p1->next;
x++;
}
ptr=p1->ptr;
if(singlyLinkedList->start==p1 && singlyLinkedList->end==p1)
{
singlyLinkedList->start=NULL;
singlyLinkedList->end=NULL;
}
else if(singlyLinkedList->start==p1) 
singlyLinkedList->start=singlyLinkedList->start->next;
else if(singlyLinkedList->end==p1)
{
singlyLinkedList->end=p2;
singlyLinkedList->end->next=NULL;
}
else p2->next=p1->next;
free(p1);
singlyLinkedList->size--;
if(success) *success=true;
return ptr;
}

//==================================APPEND TO SLL========================================

void appendToSinglyLinkedList(SinglyLinkedList *targetSinglyLinkedList,SinglyLinkedList *sourceSinglyLinkedList,bool *success)
{
bool done;
SinglyLinkedListNode *node,*s,*e,*t;
if(success) *success=false;
if(targetSinglyLinkedList==NULL) return; 
if(sourceSinglyLinkedList==NULL ||  sourceSinglyLinkedList->size==0)
{
if(success) *success=true;
return;
}
s=e=NULL;
done=true;
t=sourceSinglyLinkedList->start;
while(t!=NULL)
{
node=(SinglyLinkedListNode *)malloc(sizeof(SinglyLinkedListNode));
if(node==NULL) {done=false; break;}
node->ptr=t->ptr;
node->next=NULL;
if(s==NULL)
{
s=node;
e=node;
}
else
{
e->next=node;
e=node;
}
t=t->next;
}
if(done==false)
{
while(s!=NULL)
{
node=s;
s=s->next;
free(node);
}
return;
}
if(targetSinglyLinkedList->start==NULL)
{
targetSinglyLinkedList->start=s;
targetSinglyLinkedList->end=e;
targetSinglyLinkedList->size=sourceSinglyLinkedList->size;
}
else
{
targetSinglyLinkedList->end->next=s;
targetSinglyLinkedList->end=e;
targetSinglyLinkedList->size+=sourceSinglyLinkedList->size;
}
}

//=================================GET FROM SLL==========================================

void * getFromSinglyLinkedList(SinglyLinkedList *singlyLinkedList,int index,bool *success)
{
SinglyLinkedListNode *node;
int x;
if(success) *success=false;
if(singlyLinkedList==NULL) return NULL;
if(index<0 || index>singlyLinkedList->size) return NULL;
node=singlyLinkedList->start;
x=0;
while(x<index)
{
node=node->next;
x++;
}
if(success) *success=true;
return node->ptr;
}


//=================================ITERATOR FUNCTIONS====================================

SinglyLinkedListIterator getSinglyLinkedListIterator(SinglyLinkedList *singlyLinkedList,bool *success)
{
SinglyLinkedListIterator singlyLinkedListIterator;
singlyLinkedListIterator.node=NULL;
if(success) *success=false;
if(singlyLinkedList==NULL) return singlyLinkedListIterator;
if(singlyLinkedList->start==NULL)
{
if(success) *success=true;
return singlyLinkedListIterator;
}
if(success) *success=true;
singlyLinkedListIterator.node=singlyLinkedList->start;
return singlyLinkedListIterator;
}

bool hasNextInSinglyLinkedList(SinglyLinkedListIterator *singlyLinkedListIterator)
{
if(singlyLinkedListIterator==NULL) return false;
if(singlyLinkedListIterator->node==NULL) return false;
return true;
}

void * getNextElementFromSinglyLinkedList(SinglyLinkedListIterator *singlyLinkedListIterator,bool *success)
{
if(success) *success=false;
void *ptr=NULL;
if(singlyLinkedListIterator==NULL || singlyLinkedListIterator->node==NULL) return ptr;
ptr=singlyLinkedListIterator->node->ptr;
singlyLinkedListIterator->node=singlyLinkedListIterator->node->next;
if(success) *success=true;
return ptr;
}


//=======================================SIZE============================================

int getSizeOfSinglyLinkedList(SinglyLinkedList *singlyLinkedList)
{
if(singlyLinkedList==NULL) return 0;
return singlyLinkedList->size;
}



//=====================================CLEAR SLL=========================================


void clearSinglyLinkedList(SinglyLinkedList *singlyLinkedList)
{
SinglyLinkedListNode *node;
if(singlyLinkedList==NULL) return;
while(singlyLinkedList->start!=NULL)
{
node=singlyLinkedList->start;
singlyLinkedList->start=singlyLinkedList->start->next;
free(node);
}
singlyLinkedList->size=0;
}

//===================================DESTROY SLL=========================================

void destroySinglyLinkedList(SinglyLinkedList *singlyLinkedList)
{
if(singlyLinkedList==NULL) return;
clearSinglyLinkedList(singlyLinkedList);
free(singlyLinkedList);
}
#endif