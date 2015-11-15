////////////////////////////////////////////////////////////////////////////////
// Copyright(C) GreyGrolics 2004
//
// Filename: BalancedBST.c
// Description: Generic Binary Search Tree Data Structures, can be used with any data
//              can be used as ordinary Binary Search Tree or a Balanced BST
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
//   Name:          BST_CreateNode
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
P_Node BST_CreateNode(NodeFunctions *BSTFunctions)
{
    P_Node tempNode;

	tempNode = CreateNode();

	if (tempNode != NULL)
		BSTFunctions->pCreateFunc(tempNode);

    return tempNode;
}

////////////////////////////////////////////////////////////////////////////////
//
//   Name:          BST_AddNode
//
//   Type:          Function
//
//   Description:   Add a Node to a tree
//
//   Inputs:        pThisNode - the node to be added
//                  pParentNode - the root of the tree
//
//   Outputs:       void
//
////////////////////////////////////////////////////////////////////////////////
int BST_AddNode(NodeFunctions *BSTFunctions, P_Node pThisNode, P_Node pParentNode)
{
	static int height = 0;

	height++;

    if (pThisNode == NULL || pParentNode == NULL)
        return SAFE_HEIGHT;

    if (BSTFunctions->pCompFunc(pThisNode->data,pParentNode->data) <=0 ) // pThisNode <= pParentNode
    {
        if (pParentNode->left == NULL)
        {
            pParentNode->left = pThisNode;
			if (height >= CRITICAL_HEIGHT)
			{
				height = 0;
				return CRITICAL_HEIGHT;
			}
			else
			{
				height = 0;
				return SAFE_HEIGHT;
			}
        }
        else
            return BST_AddNode(BSTFunctions,pThisNode,pParentNode->left);
    }
    else
    {
        if (pParentNode->right == NULL)
        {
            pParentNode->right = pThisNode;
			if (height >= CRITICAL_HEIGHT)
			{
				height = 0;
				return CRITICAL_HEIGHT;
			}
			else
			{
				height = 0;
				return SAFE_HEIGHT;
			}
        }
        else
            return BST_AddNode(BSTFunctions,pThisNode,pParentNode->right);
    }
}

////////////////////////////////////////////////////////////////////////////////
//
//   Name:          BST_DeleteNode
//
//   Type:          Function
//
//   Description:   Delete a Node from the tree
//
//   Inputs:        pThisNode - the node to be deleted
//                  pParentNode - the root of the tree
//					Destroy - 1 free the memory, 0 don't free the memory
//
//   Outputs:       void
//
////////////////////////////////////////////////////////////////////////////////
P_Node BST_DeleteNode (NodeFunctions *BSTFunctions, P_Node pThisNode, P_Node pParentNode, unsigned char Mode)
{
    P_Node tempNode = NULL;
    P_Node tempParentNode = NULL;

    if (pThisNode == NULL)
        return NULL;

    // if the Node is a leaf
    if (pThisNode->left == NULL && pThisNode->right == NULL)
    {
        tempParentNode = BST_FindParentNode(BSTFunctions, pThisNode, pParentNode);

        if (tempParentNode != NULL)
        {
            if (tempParentNode->left == pThisNode)
                tempParentNode->left = NULL;
            else
                tempParentNode->right = NULL;
        }
        else    // if the node is the only node in the tree
            pParentNode = NULL;
    }
    else // node is not a leaf (a sub-root)
    {
        if (pThisNode->left != NULL) // find the biggest in the left subtree
        {
            // find a node to replace the sub-root
            tempNode = BST_FindBiggestNode(pThisNode->left);
            if (tempNode != NULL)
            {
                tempParentNode = BST_FindParentNode(BSTFunctions,tempNode,pParentNode);
                // update the parent of the node with the children of the node
                if (tempParentNode != NULL)
                {
                    if (tempParentNode->right == tempNode)
                        tempParentNode->right = tempNode->left;
                    else
                        tempParentNode->left = tempNode->left;
                }
            }
        }
        else // find the smallest node in the right subtree
        {
            // find a node to replace the sub-root
            tempNode = BST_FindSmallestNode(pThisNode->right);
            if (tempNode != NULL)
            {
                tempParentNode = BST_FindParentNode(BSTFunctions,tempNode,pParentNode);
                // update the parent of the node with the children of the node
                if (tempParentNode != NULL)
                {
                    if (tempParentNode->left == tempNode)
                        tempParentNode->left = tempNode->right;
                    else
                        tempParentNode->right = tempNode->right;
                }
            }
        }

        // update the parent of the sub-root
        tempParentNode = BST_FindParentNode(BSTFunctions,pThisNode,pParentNode);
        if (tempParentNode != NULL)
        {
            if (tempParentNode->right == pThisNode)
               tempParentNode->right = tempNode;
            else
               tempParentNode->left = tempNode;
        }

        // if the deleted node is the root
        if (pThisNode == pParentNode)
            pParentNode = tempNode;

        tempNode->left = pThisNode->left;
        tempNode->right = pThisNode->right;
    }

	if (Mode == REMOVE_ALL)
	{
		BSTFunctions->pDelFunc(pThisNode);
		free(pThisNode);
	}
	else
	{
		pThisNode->left = NULL;
		pThisNode->right = NULL;
	}

    return pParentNode;
}

////////////////////////////////////////////////////////////////////////////////
//
//   Name:          BST_FindBiggestNode
//
//   Type:          Function
//
//   Description:   Find the biggest node in the tree
//
//   Inputs:        pThisNode - the root of the tree
//
//   Outputs:       Pointer to the biggest node in the tree
//
////////////////////////////////////////////////////////////////////////////////
P_Node BST_FindBiggestNode(P_Node pThisNode)
{
    if (pThisNode == NULL)
        return NULL;

    if (pThisNode->right == NULL)
        return pThisNode;

    return BST_FindBiggestNode(pThisNode->right);
}

////////////////////////////////////////////////////////////////////////////////
//
//   Name:          BST_FindSmallestNode
//
//   Type:          Function
//
//   Description:   Find the smallest Node in the tree
//
//   Inputs:        pThisNode -  the root of the tree
//
//   Outputs:       Pointer to the smallest node in the tree
//
////////////////////////////////////////////////////////////////////////////////
P_Node BST_FindSmallestNode(P_Node pThisNode)
{
    if (pThisNode == NULL)
        return NULL;

    if (pThisNode->left == NULL)
        return pThisNode;

    return BST_FindSmallestNode(pThisNode->left);
}

////////////////////////////////////////////////////////////////////////////////
//
//   Name:          BST_FindParentNode
//
//   Type:          Function
//
//   Description:   Find a parent of a Node
//
//   Inputs:        pThisNode - the node whose parent is searced
//                  pParentNode - the root of the tree
//
//   Outputs:       Pointer to the parent of the Node
//
////////////////////////////////////////////////////////////////////////////////
P_Node BST_FindParentNode(NodeFunctions *BSTFunctions, P_Node pThisNode, P_Node pParentNode)
{
    P_Node pTempNode = NULL;
    int comp;
    
    if (pThisNode == NULL || pParentNode == NULL)
        return NULL;

    if (pParentNode->left == pThisNode || pParentNode->right == pThisNode)
        return pParentNode;

    comp = BSTFunctions->pCompFunc(pThisNode->data,pParentNode->data);
    if (comp <= 0) // pThisNode <= pParentNode
    {
        if (pParentNode->left != NULL)
            pTempNode = BST_FindParentNode(BSTFunctions, pThisNode, pParentNode->left);
    }
    
    if (comp > 0 || (comp == 0 && pTempNode == NULL))
    {
        if (pParentNode->right != NULL)
            pTempNode = BST_FindParentNode(BSTFunctions, pThisNode, pParentNode->right);
    }
    
    return pTempNode;
}

////////////////////////////////////////////////////////////////////////////////
//
//   Name:          BST_TreeToVine
//
//   Type:          Function
//
//   Description:   Change the tree to a vine using left rotation
//                  for balancing the tree
//
//   Inputs:        pThisNode -  the root of the tree
//
//   Outputs:       void
//
////////////////////////////////////////////////////////////////////////////////
void BST_TreeToVine (P_Node pThisNode)
{
    P_Node pTempNode;
    P_Node pParentNode;

    if (pThisNode == NULL)
        return;

    pParentNode = pThisNode;

    pTempNode = pParentNode->left;

    // do left rotation
    while (pTempNode != NULL)
    {
        if (pTempNode->right == NULL)
        {
            pParentNode = pTempNode;
            pTempNode = pTempNode->left;
        }
        else
        {
            pParentNode->left = pTempNode->right;
            pTempNode->right = pTempNode->right->left;
            pParentNode->left->left = pTempNode;
            pTempNode = pParentNode->left;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
//
//   Name:          BST_Compress
//
//   Type:          Function
//
//   Description:   Change a vine into a tree using right rotation
//
//   Inputs:        pThisNode - the root of the tree
//                  level - how many level to go
//
//   Outputs:       Pointer to the root of the newly created tree
//
////////////////////////////////////////////////////////////////////////////////
P_Node BST_Compress(P_Node pThisNode, unsigned int level)
{
    P_Node pTempNode = NULL;
    P_Node pGrandParentNode = NULL;
    P_Node pParentNode = pThisNode;

    if (pThisNode == NULL || level <= 0)
        return pThisNode;

    pTempNode = pParentNode->left;

    pThisNode = pThisNode->left;

    while (level > 0 && pParentNode!=NULL && pTempNode!=NULL)
    {
        pParentNode->left = pTempNode->right;
        pTempNode->right = pParentNode;

        if (pGrandParentNode != NULL)
            pGrandParentNode->left = pTempNode;

        pGrandParentNode = pTempNode;

        pParentNode = pTempNode->left;

        if (pParentNode != NULL)
            pTempNode = pParentNode->left;

        level--;
    }

    return pThisNode;
}

////////////////////////////////////////////////////////////////////////////////
//
//   Name:          BST_CountVineNodes
//
//   Type:          Function
//
//   Description:   Count the number Nodes in the tree
//
//   Inputs:        pThisNode - the root of the tree
//
//   Outputs:       unsigned int - number of nodes
//
////////////////////////////////////////////////////////////////////////////////
unsigned int BST_CountVineNodes(P_Node pThisNode)
{
    unsigned int counter = 0;
    P_Node pTempNode = pThisNode;

    if (pThisNode == NULL)
        return 0;

    while (pTempNode != NULL)
    {
        pTempNode = pTempNode->left;
        counter++;
    }

    return counter;
}

////////////////////////////////////////////////////////////////////////////////
//
//   Name:          BST_VineToTree
//
//   Type:          Function
//
//   Description:   Create a tree from a vine
//
//   Inputs:        pThisNode - the root of the tree
//
//   Outputs:       void - pThisNode will point to the root of the newly balanced
//                  tree
//
////////////////////////////////////////////////////////////////////////////////
P_Node BST_VineToTree(P_Node pThisNode)
{
    unsigned int Nodes;
    unsigned long next = 1;

    Nodes = BST_CountVineNodes(pThisNode);

    if (Nodes <=1)
        return pThisNode;

    for (;Nodes - (next - 1) > (next - 1);)
    {
        next *= 2;
    }

    next--;

    // Compress Nodes-next
    pThisNode = BST_Compress(pThisNode,Nodes - next);

    while (next > 0)
    {
        next /= 2;
        pThisNode = BST_Compress(pThisNode,next);
    }

    return pThisNode;
}

////////////////////////////////////////////////////////////////////////////////
//
//   Name:          BST_BalanceTree
//
//   Type:          Function
//
//   Description:   To balance a tree
//
//   Inputs:        pThisNode - the root of the tree
//
//   Outputs:       void -  pThisNode will point to the root of the newly balanced
//                  tree
//
////////////////////////////////////////////////////////////////////////////////
P_Node BST_BalanceTree (NodeFunctions *BSTFunctions, P_Node pThisNode)
{
    P_Node pTempNode;

    if (pThisNode == NULL)
        return pThisNode;

    pTempNode = BST_CreateNode(BSTFunctions);

    pTempNode->left = pThisNode;
    BST_TreeToVine(pTempNode);

    pThisNode = pTempNode->left;

    pTempNode->left = NULL;
    pTempNode->right = NULL;
    BST_DestroyTree(BSTFunctions, pTempNode);

    return (BST_VineToTree(pThisNode));
}

////////////////////////////////////////////////////////////////////////////////
//
//   Name:          BST_DestroyTree
//
//   Type:          Function
//
//   Description:   Destroy a tree
//
//   Inputs:        pThisNode -  the root of the tree
//
//   Outputs:       void
//
////////////////////////////////////////////////////////////////////////////////
void BST_DestroyTree (NodeFunctions *BSTFunctions, P_Node pThisNode)
{
    if (pThisNode == NULL)
        return;

    BST_DestroyTree(BSTFunctions, pThisNode->left);
    BST_DestroyTree(BSTFunctions, pThisNode->right);

    BSTFunctions->pDelFunc(pThisNode);
    free(pThisNode);
    return;
}
