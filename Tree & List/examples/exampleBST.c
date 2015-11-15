////////////////////////////////////////////////////////////////////////////////
// Copyright(C) GreyGrolics 2004
//
// Filename: exampleBST.c
// Description: Example of how to use the generic Balanced BST
//              the BST can be used as balanced or not
//              in this example the BST is first created than balanced
//              Create new add node and delete node functions if you want the
//              BST to be balanced BST all the time (call balance tree after
//              adding or deleting a node)
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Includes and external references
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <time.h>
#include "example.h"

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
//   Name:          BST_Search
//
//   Type:          Function
//
//   Description:   Search a Node
//
//   Inputs:        number -  the number in the data
//                  head - root of the tree
//
//   Outputs:       P_Node - the node containing the number
//
////////////////////////////////////////////////////////////////////////////////
P_Node BST_Search(int number, P_Node head)
{
    if (head == NULL)
        return NULL;

    if (((Num *)head->data)->number == number)
        return head;
    else if (((Num *)head->data)->number > number)
        return BST_Search(number,head->left);
    else
        return BST_Search(number,head->right);
}

////////////////////////////////////////////////////////////////////////////////
//
//   Name:          BST_Draw
//
//   Type:          Function
//
//   Description:   Draw the tree
//
//   Inputs:        nn -  the head of the list
//
//   Outputs:       void
//
////////////////////////////////////////////////////////////////////////////////
void BST_Draw(P_Node nn)
{
    if (nn==NULL)
        return;

    printf("%d(%d):->",((Num *)nn->data)->number,nn);
    if (nn->left==NULL && nn->right==NULL)
    {
        printf("\n");
        return;
    }
    if (nn->left!=NULL)
    {
        printf("left :%d(%d)",((Num *)nn->left->data)->number,nn->left);
    }
    if (nn->right!=NULL)
    {
        printf(" right :%d(%d)",((Num *)nn->right->data)->number,nn->right);
    }
    printf("\n");
    BST_Draw(nn->left);
    BST_Draw(nn->right);
}

////////////////////////////////////////////////////////////////////////////////
//
//   Name:          main
//
//   Type:          Function
//
//   Description:   Ask user to key in numbers for the nodes, balance the tree,
//                  and then ask user to choose which node to delete
//
//   Inputs:        void
//
//   Outputs:       int - return value
//
////////////////////////////////////////////////////////////////////////////////

int main(void)
{
    P_Node node;

	List MyTree;
    int number = 0;
	int height = SAFE_HEIGHT;

	MyTree.Functions.pCompFunc = CompNum;
	MyTree.Functions.pDelFunc = DelNum;
    MyTree.Functions.pCreateFunc = CreateNum;

	MyTree.head = NULL;

    // ask user to input numbers, then add to the tree
    while(number < 30000)
    {
		printf("%d%c",number,13);

		node = BST_CreateNode(&(MyTree.Functions));
		
        ((Num *)node->data)->number = number;

        if (MyTree.head == NULL)
            MyTree.head = node;
        else
        {
			height = BST_AddNode(&(MyTree.Functions),node,MyTree.head);
        }

		if (height == CRITICAL_HEIGHT)
			MyTree.head = BST_BalanceTree(&(MyTree.Functions),MyTree.head);
		number++;
		
    }

    // Balance the tree
    MyTree.head = BST_BalanceTree(&(MyTree.Functions),MyTree.head);

    number = 0;
    while(number >= 0)
    {
        printf("Enter a number to search : ");
        scanf("%d",&number);
		fflush(stdin);

		node = BST_Search(number,MyTree.head);
        
		if (node != NULL)
        {
			printf("Found: %d\n",((Num*)node->data)->number);
        }
    }

	BST_DestroyTree(&(MyTree.Functions),MyTree.head);
	return 0;
}
