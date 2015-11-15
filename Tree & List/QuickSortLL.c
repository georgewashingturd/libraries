////////////////////////////////////////////////////////////////////////////////
// Copyright(C) GreyGrolics 2004
//
// Filename: MergeSortLL.c
// Description: Merge Sort for Doubly Linked List
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Includes and external references
////////////////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include "nodes.h"

////////////////////////////////////////////////////////////////////////////////
// Defs
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Prototypes
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
//   Name:          QuickSort
//
//   Type:          Function
//
//   Description:   To do a quick sort
//
//   Inputs:        pThisNode -  the head of the list to be sorted
//                  start - the starting index
//                  finish - the end index
//                  Dir - sort ascending or descending
//
//   Outputs:       void
//
////////////////////////////////////////////////////////////////////////////////
void QuickSort(NodeFunctions *LLFunctions, P_Node *pThisNode, int low, int high, unsigned char Dir)
{
    int pivot;
    P_Node pPivot;

    if (pThisNode == NULL)
        return;

    if (*pThisNode == NULL)
        return;

    if (high > low)
    {
        pivot = Partition(LLFunctions, pThisNode, &pPivot, low, high, Dir);

        QuickSort(LLFunctions, pThisNode, low, pivot, Dir);
        QuickSort(LLFunctions, &(pPivot->right),pivot+1,high, Dir);
    }
}

////////////////////////////////////////////////////////////////////////////////
//
//   Name:          Partition
//
//   Type:          Function
//
//   Description:   Partition a list into less than, pivot, more than or
//                  more than, pivot, less than
//
//   Inputs:        pThisNode - the head of the list
//                  pPivot - the pointer to the pivot node
//                  low - starting index
//                  high - end index
//                  Dir - sort ascending or descending
//
//   Outputs:       void
//
////////////////////////////////////////////////////////////////////////////////
int Partition(NodeFunctions *LLFunctions, P_Node *pThisNode, P_Node *pPivot, int low, int high, unsigned char Dir)
{
    P_Node pTempNode;
    P_Node pNextNode;
    int pivot = 0;
    int counter = low;

    if (pThisNode == NULL)
        return -1;

    if (*pThisNode == NULL)
        return -1;

    *pPivot = *pThisNode;

    pTempNode = (*pThisNode)->right;

    while (counter <= high && pTempNode != NULL)
    {
        if ((LLFunctions->pCompFunc(pTempNode->data,(*pPivot)->data) <=0 && Dir == 0) // Ascending
            || (LLFunctions->pCompFunc(pTempNode->data,(*pPivot)->data) > 0 && Dir == 1)) // Descending
        {
            // found a node to be put at the left side of the pivot
            // delete the node
            if (pTempNode->left != NULL)
            pTempNode->left->right = pTempNode->right;
            if (pTempNode->right != NULL)
            pTempNode->right->left = pTempNode->left;

            // save the pointer to the next node to be examined
            pNextNode = pTempNode->right;

            // put the found node to the left of the pivot
            pTempNode->right = (*pThisNode);
            pTempNode->left = (*pThisNode)->left;
			(*pThisNode)->left = pTempNode;

            // update the head of the list
            *pThisNode = pTempNode;

            // move to the next node
            pTempNode = pNextNode;

            pivot++;
        }
        else
            pTempNode = pTempNode->right;

        counter++;
    }

    return pivot;
}
