#ifndef __TM_ARRAY__H
#define __TM_ARRAY__H 123
#include<tm_common.h>


typedef struct __array__
{
int rows;
void ***x;
int size;
}Array;

Array * createArray(int *success);
void setElementOfArray(Array *array,int index,void *element,int *success);
void * getElementOfArray(Array *array,int index);
int getSizeOfArray(Array *array);
void destroyArray(Array *);
#endif