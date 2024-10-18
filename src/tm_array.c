#ifndef __TM_ARRAY__C
#define __TM_ARRAY__C 123
#include<tm_array.h>
#include<tm_common.h>
#include<stdlib.h>


Array * createArray(int *success)
{
Array *array;
if(success) *success=false;
array=(Array *)malloc(sizeof(Array));
if(array==NULL) return array;
if(success) *success=true;
array->size=0;
array->rows=0;
array->x=NULL;
return array;
}

void setElementOfArray(Array *array,int index,void *element,int *success)
{
int rowIndex,colIndex;
void ***tmp;
int sp,ep,i;
rowIndex=index/10;
colIndex=index%10;
if(rowIndex>=array->rows)
{
if(array->x!=NULL)
{
tmp=(void ***)calloc(rowIndex+1,sizeof(void **));
if(tmp==NULL) return;
sp=0;
ep=array->rows-1;
for(i=sp;i<=ep;i++) tmp[i]=array->x[i];
free(array->x);
array->x=tmp;
array->rows=rowIndex+1;
}
else
{
array->x=(void ***)calloc(rowIndex+1,sizeof(void **));
array->rows=rowIndex+1;
}
}
if(array->x[rowIndex]==NULL) array->x[rowIndex]=(void **)calloc(10,sizeof(void *));
array->x[rowIndex][colIndex]=element;
if(index>=array->size) array->size=index+1;
if(success) *success=true;
}

void * getElementOfArray(Array *array,int index)
{
int rowIndex,columnIndex;
if(array==NULL) return NULL;
if(array->x==NULL) return NULL;
rowIndex=index/10;
if(rowIndex>=array->rows) return NULL;
if(array->x[rowIndex]==NULL) return NULL;
columnIndex=index%10;
return array->x[rowIndex][columnIndex];
}

int getSizeOfArray(Array *array)
{
if(array==NULL) return 0;
return array->size;
}

void destroyArray(Array *array)
{
int i;
if(array==NULL) return;
if(array->x==NULL)
{
free(array);
return;
}
for(i=0;i<array->rows;i++)
{
if(array->x[i]!=NULL) free(array->x[i]);
}
free(array->x);
free(array);
}
#endif