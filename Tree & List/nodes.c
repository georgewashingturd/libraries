////////////////////////////////////////////////////////////////////////////////
// Copyright(C) GreyGrolics 2004
//
// Filename: nodes.c
// Description: Contains generic variable(s) and function(s) that will bw used
//              in Balanced Search Tree and Doubly Linked List
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
//   Name:          CreateNode
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
P_Node CreateNode(void)
{
    P_Node tempNode;

    tempNode = (P_Node)malloc(sizeof(Node));
    tempNode->left = NULL;
    tempNode->right = NULL;

    return tempNode;
}
