////////////////////////////////////////////////////////////////////////////////
// Copyright(C) GreyGrolics 2004
//
// Filename: nodes.h
// Description: header file for generic linked and binary tree
////////////////////////////////////////////////////////////////////////////////

#ifndef _NODES_H
#define _NODES_H

////////////////////////////////////////////////////////////////////////////////
// Defs
////////////////////////////////////////////////////////////////////////////////

#define CRITICAL_HEIGHT	4599
#define SAFE_HEIGHT		0
#define REMOVE_ALL		1

typedef struct iNode
{
    struct iNode *left;     // prev for linked list
    struct iNode *right;    // next for linked list
    void *data;
}
Node, * P_Node;

typedef int (*P_COMPARE_FUNCTION)(void * , void *);
typedef void (*P_NODE_FUNCTION)(void *);

typedef struct
{
	P_COMPARE_FUNCTION pCompFunc;
	P_NODE_FUNCTION pDelFunc;
	P_NODE_FUNCTION pCreateFunc;
} NodeFunctions;

typedef struct
{
	P_Node head;
	NodeFunctions Functions;
} List;

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Prototypes
////////////////////////////////////////////////////////////////////////////////

P_Node CreateNode(void);

//==================================For BST====================================
P_Node BST_CreateNode(NodeFunctions *BSTFunctions);
int BST_AddNode(NodeFunctions *BSTFunctions, P_Node pThisNode, P_Node pParentNode);
P_Node BST_DeleteNode (NodeFunctions *BSTFunctions, P_Node pThisNode, P_Node pParentNode, unsigned char Mode);
P_Node BST_FindBiggestNode(P_Node pThisNode);
P_Node BST_FindSmallestNode(P_Node pThisNode);
P_Node BST_FindParentNode(NodeFunctions *BSTFunctions, P_Node pThisNode, P_Node pParentNode);
void BST_DestroyTree (NodeFunctions *BSTFunctions, P_Node pThisNode);
// Balanced BST Functions
void BST_TreeToVine (P_Node pThisNode);
P_Node BST_Compress(P_Node pThisNode, unsigned int level);
unsigned int BST_CountNodes(P_Node pThisNode);
P_Node BST_VineToTree(P_Node pThisNode);
P_Node BST_BalanceTree (NodeFunctions *BSTFunctions, P_Node pThisNode);

//==============================For Linked List================================
P_Node LL_CreateNode(NodeFunctions *LLFunctions);
void LL_AddNodeAt (P_Node pThisNode, P_Node pParentNode, unsigned char Dir);
void LL_AddNode (P_Node pThisNode, P_Node pParentNode);
void LL_DeleteNode (NodeFunctions *LLFunctions, P_Node pThisNode, unsigned char Mode);
void LL_DestroyList (NodeFunctions *LLFunctions, P_Node pThisNode);
// For Merge Sort
P_Node MergeSort (NodeFunctions *LLFunctions, P_Node pThisNode, int start, int finish, unsigned char Dir);
P_Node SplitList (P_Node pThisNode, int start, int finish);
P_Node Merge (NodeFunctions *LLFunctions, P_Node pNode1, P_Node pNode2, unsigned char Dir);
// For Quick Sort
void QuickSort(NodeFunctions *LLFunctions, P_Node *pThisNode, int low, int high, unsigned char Dir);
int Partition(NodeFunctions *LLFunctions, P_Node *pThisNode, P_Node *pPivot, int low, int high, unsigned char Dir);
unsigned int CountNodes(P_Node pThisNode);

#endif
