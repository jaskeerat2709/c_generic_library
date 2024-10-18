#ifndef __TM_DLL__C
#define __TM_DLL__C 123
#include<stdio.h>
#include<stdlib.h>
#include<tm_dll.h>

/*=================================FUNCTIONS START=====================================*/

//====================================CREATION===========================================


DoublyLinkedList *createDoublyLinkedList(bool *success)
{
DoublyLinkedList *doublyLinkedList;
if(success) *success=false;
doublyLinkedList=(DoublyLinkedList *)malloc(sizeof(DoublyLinkedList));
if(doublyLinkedList==NULL) return NULL;
doublyLinkedList->start=NULL;
doublyLinkedList->end=NULL;
doublyLinkedList->size=0;
if(success) *success=true;
return doublyLinkedList;
}


//===================================ADD TO DLL==========================================

void addToDoublyLinkedList(DoublyLinkedList *doublyLinkedList,void *ptr,bool *success)
{
DoublyLinkedListNode *node;
if(success) *success=false;
if(doublyLinkedList==NULL) return;
node=(DoublyLinkedListNode *)malloc(sizeof(DoublyLinkedListNode));
if(node==NULL) return;
node->ptr=ptr;
node->next=NULL;
node->previous=NULL;
if(doublyLinkedList->start==NULL)
{
doublyLinkedList->start=node;
doublyLinkedList->end=node;
}
else
{
doublyLinkedList->end->next=node;
doublyLinkedList->end=node;
node->previous=doublyLinkedList->end;
}
doublyLinkedList->size++;
if(success) *success=true;
}

//=================================INSERT INTO DLL=======================================

void insertIntoDoublyLinkedList(DoublyLinkedList *doublyLinkedList,int index,void *ptr,bool *success)
{
DoublyLinkedListNode *p1,*p2,*node;
int x;
if(success) *success=false;
if(doublyLinkedList==NULL) return;
if(index<0 || index>doublyLinkedList->size) return;
if(index==doublyLinkedList->size) //ADD AT END
{
addToDoublyLinkedList(doublyLinkedList,ptr,success);
return;
}
node=(DoublyLinkedListNode *)malloc(sizeof(DoublyLinkedListNode));
node->ptr=ptr;
node->next=NULL;
node->previous=NULL;
if(node==NULL) return;
if(index==0)  //ADD AT START
{
node->next=doublyLinkedList->start;
doublyLinkedList->start=node;
doublyLinkedList->size++;
if(success) *success=true;
return;
}
p1=doublyLinkedList->start;
x=0;
while(x<index)
{
p2=p1;
p1=p1->next;
x++;
}
p2->next=node;
node->next=p1;
doublyLinkedList->size++;
if(success) *success=true;
return;
}


//===================================REMOVE FROM DLL=====================================

void *removeFromDoublyLinkedList(DoublyLinkedList *doublyLinkedList,int index,bool *success)
{
DoublyLinkedListNode *p1,*p2;
void *ptr;
int x=0;
if(success) *success=false;
if(doublyLinkedList==NULL) return NULL;
if(index<0 || index>doublyLinkedList->size) return NULL;
p1=doublyLinkedList->start;
x=0;
while(x<index)
{
p2=p1;
p1=p1->next;
x++;
}
ptr=p1->ptr;
if(doublyLinkedList->start==p1 && doublyLinkedList->end==p1)
{
doublyLinkedList->start=NULL;
doublyLinkedList->end=NULL;
}
else if(doublyLinkedList->end==p1)
{
doublyLinkedList->end=p2;
doublyLinkedList->end->next=NULL;
}
else p2->next=p1->next;
free(p1);
doublyLinkedList->size--;
if(success) *success=True;
return ptr;
}

//==================================APPEND TO DLL========================================

void appendToDoublyLinkedList(DoublyLinkedList *targetDoublyLinkedList,DoublyLinkedList *sourceDoublyLinkedList,bool *success)
{
bool done;
DoublyLinkedListNode *node,*s,*e,*t;
if(success) *success=false;
if(targetDoublyLinkedList==NULL) return; 
if(sourceDoublyLinkedList==NULL ||  sourceDoublyLinkedList->size==0)
{
if(success) *success=true;
return;
}
s=e=NULL;
done=true;
t=sourceDoublyLinkedList->start;
while(t!=NULL)
{
node=(DoublyLinkedListNode *)malloc(sizeof(DoublyLinkedListNode));
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
if(targetDoublyLinkedList->start==NULL)
{
targetDoublyLinkedList->start=s;
targetDoublyLinkedList->end=e;
targetDoublyLinkedList->size=sourceDoublyLinkedList->size;
}
else
{
targetDoublyLinkedList->end->next=s;
targetDoublyLinkedList->end=e;
targetDoublyLinkedList->size+=sourceDoublyLinkedList->size;
}
}

//=================================GET FROM DLL==========================================

void *getFromDoublyLinkedList(DoublyLinkedList *doublyLinkedList,int index,bool *success)
{
DoublyLinkedListNode *node;
int x;
if(success) *success=false;
if(doublyLinkedList==NULL) return NULL;
if(index<0 || index>doublyLinkedList->size) return NULL;
node=doublyLinkedList->start;
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


DoublyLinkedListIterator getDoublyLinkedListIterator(DoublyLinkedList *doublyLinkedList,bool *success)
{
DoublyLinkedListIterator doublyLinkedListIterator;
doublyLinkedListIterator.node=NULL;
if(success) *success=false;
if(doublyLinkedList==NULL) return doublyLinkedListIterator;
if(doublyLinkedList->start==NULL)
{
if(success) *success=true;
return doublyLinkedListIterator;
}
if(success) *success=true;
doublyLinkedListIterator.node=doublyLinkedList->start;
return doublyLinkedListIterator;
}

bool hasNextInDoublyLinkedList(DoublyLinkedListIterator *doublyLinkedListIterator)
{
if(doublyLinkedListIterator==NULL) return false;
if(doublyLinkedListIterator->node==NULL) return false;
return true;
}

void * getNextElementFromDoublyLinkedList(DoublyLinkedListIterator *doublyLinkedListIterator,bool *success)
{
if(success) *success=false;
void *ptr=NULL;
if(doublyLinkedListIterator==NULL || doublyLinkedListIterator->node==NULL) return ptr;
ptr=doublyLinkedListIterator->node->ptr;
doublyLinkedListIterator->node=doublyLinkedListIterator->node->next;
if(success) *success=true;
return ptr;
}

/*========================================REVERSE======================================*/

DoublyLinkedListReverseIterator getDoublyLinkedListReverseIterator(DoublyLinkedList *doublyLinkedList,bool *success)
{
DoublyLinkedListReverseIterator doublyLinkedListReverseIterator;
doublyLinkedListReverseIterator.mode=NULL;
if(success) *success=false;
if(doublyLinkedList==NULL)  return doublyLinkedListReverseIterator;
if(doublyLinkedList->start==NULL)
{
if(success) *success=true;
return doublyLinkedListReverseIterator;
}
if(success) *success=true;
doublyLinkedListReverseIterator.mode=doublyLinkedList->end;
return doublyLinkedListReverseIterator;
}

int hasPreviousInDoublyLinkedList(DoublyLinkedListReverseIterator *doublyLinkedListReverseIterator)
{
}



//=======================================SIZE============================================

int getSizeOfDoublyLinkedList(DoublyLinkedList *doublyLinkedList)
{
if(doublyLinkedList==NULL) return 0;
return doublyLinkedList->size;
}


//=====================================CLEAR DLL=========================================


void clearDoublyLinkedList(DoublyLinkedList *doublyLinkedList)
{
DoublyLinkedListNode *node;
if(doublyLinkedList==NULL) return;
node=doublyLinkedList->start;
while(doublyLinkedList->start!=NULL)
{
node=doublyLinkedList->start;
doublyLinkedList->start=doublyLinkedList->start->next;
free(node);
}
doublyLinkedList->end=NULL;
doublyLinkedList->size=0;
}

//===================================DESTROY DLL=========================================

void destroyDoublyLinkedList(DoublyLinkedList *doublyLinkedList)
{
if(doublyLinkedList==NULL) return;
clearDoublyLinkedList(doublyLinkedList);
free(doublyLinkedList);
}
#endif