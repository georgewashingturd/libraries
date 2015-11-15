#include "stdafx.h"

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
//   Name:          MergeSort
//
//   Type:          Function
//
//   Description:   To do a merge sort
//
//   Inputs:        pThisNode -  the head of the list to be sorted
//                  start - the starting index
//                  finish - the end index
//                  Dir - sort ascending or descending
//
//   Outputs:       void
//
////////////////////////////////////////////////////////////////////////////////
P_Node MergeSort (NodeFunctions *LLFunctions, P_Node pThisNode, int start, int finish, unsigned char Dir)
{
    P_Node pTempNode = NULL;

    if (pThisNode == NULL)
        return pTempNode;

    if (start >= finish)
        return pThisNode;

    pTempNode = SplitList(pThisNode,start,finish/2);

    if (finish - start == 1)
        return Merge(LLFunctions,pTempNode,pThisNode,Dir);

    return Merge(LLFunctions,
				MergeSort(LLFunctions,pThisNode,start,finish/2, Dir),
                MergeSort(LLFunctions,pTempNode,(finish/2) + 1,finish, Dir),
                Dir);
}

////////////////////////////////////////////////////////////////////////////////
//
//   Name:          SplitList
//
//   Type:          Function
//
//   Description:   Split the list according to the pivot
//
//   Inputs:        pThisNode -  the head of the list
//                  start - the start index
//                  finish - the end index
//
//   Outputs:       void
//
////////////////////////////////////////////////////////////////////////////////
P_Node SplitList (P_Node pThisNode, int start, int finish)
{
    int counter = start;
    P_Node pTempNode = pThisNode, pResNode = NULL;

    while (counter < finish && pTempNode != NULL)
    {
        pTempNode = pTempNode->right;
        counter ++;
    }

    if (pTempNode != NULL)
        pResNode = pTempNode->right;

    if (pResNode != NULL)
        pResNode->left = NULL;

    if (pTempNode != NULL)
        pTempNode->right = NULL;

    return pResNode;
}

////////////////////////////////////////////////////////////////////////////////
//
//   Name:          Merge
//
//   Type:          Function
//
//   Description:   Combine two sorted list
//
//   Inputs:        pNode1 - the first sorted list
//                  pNode2 - the second sorted list
//                  Dir - sort ascending or descending
//
//   Outputs:       void
//
////////////////////////////////////////////////////////////////////////////////
P_Node Merge (NodeFunctions *LLFunctions, P_Node pNode1, P_Node pNode2, unsigned char Dir)
{
    P_Node pNode3 = NULL;
    P_Node pTempNode3 = NULL;
    P_Node pTempNode = NULL;

    while (pNode1 != NULL && pNode2 != NULL)
    {
        if (LLFunctions->pCompFunc(pNode1->data, pNode2->data) <= 0)
        {
            if (Dir == 0)       //Ascending
            {
                pTempNode = pNode1;
                pNode1 = pNode1->right;
            }
            else                //Descending
            {
                pTempNode = pNode2;
                pNode2 = pNode2->right;
            }
        }
        else
        {
            if (Dir == 1)
            {
                pTempNode = pNode1;
                pNode1 = pNode1->right;
            }
            else
            {
                pTempNode = pNode2;
                pNode2 = pNode2->right;
            }
        }

        if (pNode3 == NULL)
        {
            pTempNode->left = NULL;
            pNode3 = pTempNode;
            pTempNode3 = pNode3;
        }
        else
        {
            pTempNode->left = pTempNode3;
            pTempNode3->right = pTempNode;
            pTempNode3 = pTempNode3->right;
        }
    }

    if (pNode1 != NULL)
    {
        if (pTempNode3 != NULL)
        {
            pTempNode3->right = pNode1;
            pNode1->left = pTempNode3;
        }
        else
            pNode3 = pNode1;
    }
    else if (pNode2 != NULL)
    {
        if (pTempNode3 != NULL)
        {
            pTempNode3->right = pNode2;
            pNode2->left = pTempNode3;
        }
        else
            pNode3 = pNode2;
    }

    return pNode3;
}

////////////////////////////////////////////////////////////////////////////////
//
//   Name:          CountNodes
//
//   Type:          Function
//
//   Description:   To Count the number of nodes in the list
//
//   Inputs:        pThisNode -  the head of the list
//
//   Outputs:       void
//
////////////////////////////////////////////////////////////////////////////////
unsigned int CountNodes(P_Node pThisNode)
{
    P_Node pTempNode = pThisNode;
    unsigned int counter = 1;

    if (pThisNode == NULL)
        return 0;

    while (pTempNode != NULL)
    {
        counter++;
        pTempNode = pTempNode->right;
    }

    return counter;
}
