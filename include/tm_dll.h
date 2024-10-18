#ifndef __TM_DLL__H
#define __TM_DLL__H 123
#include<tm_common.h>
typedef struct __$_tm_dll_node
{
void *ptr;
struct __$_tm_dll_node *next;
struct __$_tm_dll_node *previous;
}DoublyLinkedListNode;

typedef struct __$_tm_dll
{
DoublyLinkedListNode *start;
DoublyLinkedListNode *end;
int size;
}DoublyLinkedList;

typedef struct __$_tm_dll_iterator
{
DoublyLinkedListNode *node;
}DoublyLinkedListIterator;

typedef struct __$_tm_dll_reverse_iterator
{
DoublyLinkedListNode *mode;
}DoublyLinkedListReverseIterator;


DoublyLinkedList *createDoublyLinkedList(bool *success);
void destroyDoublyLinkedList(DoublyLinkedList *doublyLinkedList);
int getSizeOfDoublyLinkedList(DoublyLinkedList *doublyLinkedList);
void addToDoublyLinkedList(DoublyLinkedList *doublyLinkedList,void *ptr,bool *success);
void insertIntoDoublyLinkedList(DoublyLinkedList *doublyLinkedList,int index,void *ptr,bool *success);
void * removeFromDoublyLinkedList(DoublyLinkedList *doublyLinkedList,int index,bool *success);
void clearDoublyLinkedList(DoublyLinkedList *doublyLinkedList);
void appendToDoublyLinkedList(DoublyLinkedList *target,DoublyLinkedList *source,bool *success);
void *getFromDoublyLinkedList(DoublyLinkedList *doublyLinkedList,int index,bool *success);

DoublyLinkedListIterator getDoublyLinkedListIterator(DoublyLinkedList *doublyLinkedList,bool *success);
bool hasNextInDoublyLinkedList(DoublyLinkedListIterator *doublyLinkedListIterator);
void * getNextElementFromDoublyLinkedList(DoublyLinkedListIterator *doublyLinkedListIterator,bool *success);

DoublyLinkedListReverseIterator getDoublyLinkedListReverseIterator(DoublyLinkedList *doublyLinkedList,bool *success);
bool hasPreviousInDoublyLinkedList(DoublyLinkedListReverseIterator *doublyLinkedListReverseIterator);
void * getPreviousElementFromDoublyLinkedList(DoublyLinkedListReverseIterator *doublyLinkedListReverseIterator,bool *success);
#endif
