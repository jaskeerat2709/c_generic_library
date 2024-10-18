#ifndef __TM_AVL_TREE__H
#define __TM_AVL_TREE__H 123
#include<tm_common.h>
#include<tm_stack.h>

typedef struct __$_tm_avl_tree_node
{
void *ptr;
struct __$_tm_avl_tree_node *left;
struct __$_tm_avl_tree_node *right;
}AVLTreeNode;

typedef struct __$_tm_avl_tree
{
int (*predicate)(void *,void *);
struct __$_tm_avl_tree_node *start;
int size;
}AVLTree;

typedef struct __$__tm_avl_tree_in_order_iterator
{
AVLTreeNode *node;
Stack *stack;
}AVLTreeInOrderIterator;

typedef struct __$__tm_avl_tree_pre_order_iterator
{
AVLTreeNode *node;
Stack *stack;
}AVLTreePreOrderIterator;

typedef struct __$__tm_avl_tree_post_order_iterator
{
AVLTreeNode *node;
Stack *stack;
}AVLTreePostOrderIterator;


AVLTree *createAVLTree(bool *success,int (*predicate)(void *,void *));
int getSizeOfAVLTree(AVLTree *avlTree);
void insertIntoAVLTree(AVLTree *avlTree,void *ptr,bool *success);
void * removeFromAVLTree(AVLTree *avlTree,void *ptr,bool *success);
void clearAVLTree(AVLTree *avlTree);
void destroyAVLTree(AVLTree *avlTree);
void * getFromAVLTree(AVLTree *avlTree,void *ptr,bool *success);
int getHeightOfAVLTree(AVLTreeNode *root);

AVLTreeInOrderIterator getAVLTreeInOrderIterator(AVLTree *avlTree,bool *success);
bool hasNextInOrderElementInAVLTree(AVLTreeInOrderIterator *avlTreeInOrderIterator);
void * getNextInOrderElementFromAVLTree(AVLTreeInOrderIterator *avlTreeInOrderIterator,bool *success);
void balanceAVLTree(AVLTree *avlTree,Stack *stack);

AVLTreePreOrderIterator getAVLTreePreOrderIterator(AVLTree *avlTree,bool *success);
bool hasNextPreOrderElementInAVLTree(AVLTreePreOrderIterator *avlTreePreOrderIterator);
void * getNextPreOrderElementFromAVLTree(AVLTreePreOrderIterator *avlTreePreOrderIterator,bool *success);

AVLTreePostOrderIterator getAVLTreePostOrderIterator(AVLTree *avlTree,bool *success);
bool hasNextPostOrderElementInAVLTree(AVLTreePostOrderIterator *avlTreePostOrderIterator);
void * getNextPostOrderElementFromAVLTree(AVLTreePostOrderIterator *avlTreePostOrderIterator,bool *success);
#endif
