////////////////////////////////////////////////////////////////////////////////
// Copyright(C) GreyGrolics 2004
//
// Filename: exampleLL.c
// Description: Example of how to use the generic Doubly Linked List
//              First a list is created then sorted using quick sort you can use
//              merge sort as well. If you want to have an always sorted list
//              you can create new add and delete node function
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Includes and external references
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include "example.h"

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
//   Name:          LL_Search
//
//   Type:          Function
//
//   Description:   Search a Node
//
//   Inputs:        number -  the number in the data
//                  head - head of the list
//
//   Outputs:       P_Node - the node containing the number
//
////////////////////////////////////////////////////////////////////////////////
P_Node LL_Search(int number, P_Node head)
{
    while (head != NULL && ((Num *)head->data)->number != number)
    {
        head = head->right;
    }

    return head;
}

////////////////////////////////////////////////////////////////////////////////
//
//   Name:          LL_Draw
//
//   Type:          Function
//
//   Description:   Draw the list
//
//   Inputs:        nn -  the head of the list
//
//   Outputs:       void
//
////////////////////////////////////////////////////////////////////////////////
void LL_Draw (P_Node nn)
{
    while (nn != NULL)
    {
        printf("%d->",((Num *)nn->data)->number);
        nn = nn->right;
    }
}

////////////////////////////////////////////////////////////////////////////////
//
//   Name:          main
//
//   Type:          Function
//
//   Description:   Ask user to key in numbers for the nodes, sort the nodes,
//                  and then ask user to choose which node to delete
//
//   Inputs:        void
//
//   Outputs:       int - return value
//
////////////////////////////////////////////////////////////////////////////////

int main(void)
{
    List MyLinkedList;
    P_Node node = NULL;
    int number = 0;

    MyLinkedList.Functions.pCompFunc = CompNum;
	MyLinkedList.Functions.pDelFunc = DelNum;
    MyLinkedList.Functions.pCreateFunc = CreateNum;

	MyLinkedList.head = NULL;

    printf("Enter negative to break\n");

    // ask user to input numbers, then add to the list
    while(number >= 0)
    {
        printf("Enter a number to add : ");
        scanf("%d",&number);
		fflush(stdin);

        if (number >= 0)
        {
            node = LL_CreateNode(&(MyLinkedList.Functions));
            ((Num *)node->data)->number = number;
            if (MyLinkedList.head == NULL)
                MyLinkedList.head = node;
            else
            {
                LL_AddNode(node,MyLinkedList.head);
            }
        }
    }

    LL_Draw(MyLinkedList.head);
    printf ("\n");

    // sort the list
    QuickSort(&(MyLinkedList.Functions),&(MyLinkedList.head),0,100,1);
    //MyLinkedList.head = MergeSort(&(MyLinkedList.Functions),MyLinkedList.head,0,100,0);

    LL_Draw(MyLinkedList.head);
    printf ("\n");

    number = 0;
    while(number >= 0)
    {
        printf("Enter a number to delete : ");
        scanf("%d",&number);
		fflush(stdin);

        if ((node = LL_Search(number,MyLinkedList.head)) != NULL)
        {
            printf("delete\n");
            if (node == MyLinkedList.head)
                MyLinkedList.head = MyLinkedList.head->right;
            LL_DeleteNode(&(MyLinkedList.Functions),node, REMOVE_ALL);
            LL_Draw(MyLinkedList.head);
            printf ("\n");
        }
    }

	LL_DestroyList(&(MyLinkedList.Functions), MyLinkedList.head);
}
