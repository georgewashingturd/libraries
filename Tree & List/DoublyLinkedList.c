////////////////////////////////////////////////////////////////////////////////
// Copyright(C) GreyGrolics 2004
//
// Filename: DoublyLinkedList.c
// Description: Generic Doubly Linked List Data Structures, can be used with 
//              any data
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Includes and external references
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
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
//   Name:          LL_CreateNode
//
//   Type:          Function
//
//   Description:   Create a Node
//
//   Inputs:        void
//
//   Outputs:       Pointer to a newly created Node
//
////////////////////////////////////////////////////////////////////////////////
P_Node LL_CreateNode(NodeFunctions *LLFunctions)
{
    P_Node tempNode;

	tempNode = CreateNode();

	if (tempNode != NULL)
		LLFunctions->pCreateFunc(tempNode);

    return tempNode;
}

////////////////////////////////////////////////////////////////////////////////
//
//   Name:          LL_AddNodeAt
//
//   Type:          Function
//
//   Description:   Add a Node at certain position
//
//   Inputs:        pThisNode -  the Node to be added
//                  pParentNode - the Node before or after the Node to be added
//                  Dir - Node to be added before or after the pParentNode
//
//   Outputs:       void
//
////////////////////////////////////////////////////////////////////////////////
void LL_AddNodeAt (P_Node pThisNode, P_Node pParentNode, unsigned char Dir)
{
    if (pThisNode == NULL || pParentNode == NULL)
        return;

    if (Dir == 0)   // Add after pParentNode
    {
        pThisNode->right = pParentNode->right;
        pThisNode->left = pParentNode;
        pParentNode->right = pThisNode;
    }
    else
    {
        pThisNode->right = pParentNode;
        pThisNode->left = pParentNode->left;
        pParentNode->left = pThisNode;
    }
}

////////////////////////////////////////////////////////////////////////////////
//
//   Name:          LL_AddNode
//
//   Type:          Function
//
//   Description:   Add a Node at the beginning of the list
//
//   Inputs:        pThisNode -  the Node to be added
//                  pParentNode - the head of the list
//
//   Outputs:       void
//
////////////////////////////////////////////////////////////////////////////////
void LL_AddNode (P_Node pThisNode, P_Node pParentNode)
{
    P_Node pTempNode;

    if (pThisNode == NULL || pParentNode == NULL)
        return;

	pTempNode = pParentNode->right;
	if (pTempNode != NULL)
	{
		pTempNode->left = pThisNode;
	}
	pThisNode->right = pTempNode;
	pThisNode->left = pParentNode;
	pParentNode->right = pThisNode;
}

////////////////////////////////////////////////////////////////////////////////
//
//   Name:          LL_DeleteNode
//
//   Type:          Function
//
//   Description:   Delete a Node
//
//   Inputs:        pThisNode -  the Node to be deleted
//					Destroy - 1 free the memory, 0 don't free the memory
//
//   Outputs:       void
//
////////////////////////////////////////////////////////////////////////////////
void LL_DeleteNode (NodeFunctions *LLFunctions, P_Node pThisNode, unsigned char Mode)
{
    if (pThisNode->left != NULL)
        pThisNode->left->right = pThisNode->right;
    if (pThisNode->right != NULL)
        pThisNode->right->left = pThisNode->left;

	if (Mode == REMOVE_ALL)
	{
		LLFunctions->pDelFunc(pThisNode);
		free(pThisNode);
	}
	else
	{
		pThisNode->left = NULL;
		pThisNode->right = NULL;
	}
}

////////////////////////////////////////////////////////////////////////////////
//
//   Name:          LL_DestroyList
//
//   Type:          Function
//
//   Description:   Destroy a list
//
//   Inputs:        pThisNode -  the head of the list
//
//   Outputs:       void
//
////////////////////////////////////////////////////////////////////////////////
void LL_DestroyList (NodeFunctions *LLFunctions, P_Node pThisNode)
{
    P_Node pTempNode;

    while (pThisNode != NULL)
    {
        pTempNode = pThisNode;
        pThisNode = pThisNode->right;

		LL_DeleteNode(LLFunctions, pTempNode, REMOVE_ALL);
    }
}
