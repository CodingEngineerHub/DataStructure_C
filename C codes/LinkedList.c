#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void RemoveFirstNode();

// Node  structure
struct node {
    int number;
    struct node* nextNode;
};

struct node* startNode = NULL;

struct node* createNode(int number)
{
    //Memory Allocation for new node
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->number = number;
    newNode->nextNode = NULL;

    return newNode;
}


void AddNewLastNode(int number)
{
    struct node* NewLastNode = createNode(number);
    //If there is no node, we add it to the beginning 
    if (startNode == NULL)
    {
        startNode = NewLastNode;
    }
    else
    {
        struct node* temp = startNode;
        //Do traverse operation to find previous last node
        while (temp->nextNode != NULL)
        {
            temp = temp->nextNode;
        }
        temp->nextNode = NewLastNode;
    }
}


void AddHead(int number)
{
    struct node* newHeadNode = createNode(number);
    //If there is no node, we add it to the beginning directly 
    if (startNode == NULL)
    {
        startNode = newHeadNode;
        return;
    }

    struct node* previousHeadNode = startNode;
    startNode = newHeadNode;
    startNode->nextNode = previousHeadNode;
}



void AddNodeAfterPosition(int pos, int number)
{
    struct node* InsertNode = createNode(number);
    
    if (pos == 0)
    {
        AddHead(number);
        return;
    }

    struct node* temp = startNode;
    int counter = 0;
    
    while (temp != NULL)
    {
        //search until find entering position
        if (counter == pos - 1)
            break;
        temp = temp->nextNode;
        counter++;
    }
  
    if (counter + 1 != pos)
    {
        printf("\n entering position outside the boundary  ");
        return;
    }

    if (temp->nextNode == NULL)
    {
        AddNewLastNode(number);
        return;
    }
    //we have to store previous next node
    struct node* tempNextNode = temp->nextNode;
    temp->nextNode = InsertNode;
    InsertNode->nextNode = tempNextNode;

}


void RemoveLastNode()
{
    if (startNode == NULL)
    {
        printf("\n No node found \n");
        return;
    }
    struct node* temp = startNode;
    if (temp->nextNode == NULL)
    {
        RemoveFirstNode();
        return;
    }
    while (temp->nextNode->nextNode != NULL)
        temp = temp->nextNode;

    temp->nextNode = NULL;
    //free(temp->nextNode);
    //temp = NULL;
}


void RemoveFirstNode()
{
    if (startNode == NULL)
    {
        printf("\nNo node found\n");
        return;
    }
    if (startNode->nextNode == NULL)
    {
        startNode = NULL;
        return;
    }

    struct node* NewFirstNode = startNode->nextNode;
    free(startNode);
    startNode = NewFirstNode;
}

//burası yanlış olabilir
void deleteNode(int number)
{
    if (startNode == NULL)
    {
        printf("\n No node found ");
        return;
    }

    if (startNode->number == number)
    {
        RemoveFirstNode();
        return;
    }

    struct node* temp = startNode;
    int check = 0;
    while (temp->nextNode != NULL)
    {
        if (temp->nextNode->number == number)
        {
            check = 1;
            break;
        }

        temp = temp->nextNode;
    }
    if (check == 0)
    {
        printf("\n No Node Found");
        return;
    }
    struct node* temp2 = temp->nextNode->nextNode;
    free(temp->nextNode);
    temp->nextNode = temp2;
}


void ReverseLinkListIterative()
{
    
    struct node* currentNode = startNode;
    struct node* previousNode = NULL;
    struct node* nextNode = NULL;

    while (currentNode != NULL)
    {
        nextNode = currentNode->nextNode;
        currentNode->nextNode = previousNode;

        /* temp = temp->nextNode */
        previousNode = currentNode;
        currentNode = nextNode;
    }
    startNode = previousNode;
}


struct node* ReverseLinkListRecursive(struct node* currentNode)
{
   
    if (currentNode == NULL)
        return;
    
    if (currentNode->nextNode == NULL)
    {
        startNode = currentNode;         
        return currentNode;
    }

    struct node* DUGUM = ReverseLinkListRecursive(currentNode->nextNode);

    DUGUM->nextNode = currentNode;
    currentNode->nextNode = NULL;
    return currentNode;

}


void printLinkList()
{
    struct node* temp = startNode;

    printf("\nPrinting All Nodes");
    
    while (temp != NULL)
    {
        printf(" %d  ", temp->number);
        temp = temp->nextNode;
    }
}

int main()
{
    int secim=0, number, pos;
    
    while (secim!=9)
    {
        printf("\n ****** which operation do you want to do  ******");
        printf("\n 1- Add last ");
        printf("\n 2- Add Start ");
        printf("\n 3- Add A node after specific position ");
        printf("\n 4- Remove last node ");
        printf("\n 5- Remove start node ");
        printf("\n 6- Remove a node ");
        printf("\n 7- Reverse Link List with Iterative method ");
        printf("\n 8- Reverse Link List with Recursive method ");
        printf("\n 9- Exit \n");
        scanf_s("%d", &secim);

        switch (secim)
        {
        case 1:
            printf("\n Enter the number you want to add last:");
            scanf_s("%d", &number);
            AddNewLastNode(number);
            printLinkList();
            break;
        case 2:
            printf("\n Enter the number you want to add start:");
            scanf_s("%d", &number);
            AddHead(number);
            printLinkList();
            break;
        case 3:
            printf("\n Enter the number you want to add:");
            scanf_s("%d", &number);
            printf("\n Whick position do you want to add? ");
            scanf_s("%d", &pos);
            AddNodeAfterPosition(pos, number);
            printLinkList();
            break;
        case 4:
            RemoveLastNode();
            printLinkList();
            break;
        case 5:
            RemoveFirstNode();
            printLinkList();
            break;
        case 6:
            printf("\n Which number do you want to remove? ");
            scanf_s("%d", &number);
            deleteNode(number);
            printLinkList();
            break;
        case 7:
            printf("\n Starting Reverse LinkList with iterative method...\n ");
            ReverseLinkListIterative();
            printLinkList();
            break;
        case 8:
            printf("\n startNode Dugumunden Baslaniyor %d", startNode->number);            
            ReverseLinkListRecursive(startNode);
            printLinkList();
            break;
        case 9:
            printLinkList();
            printf("\n Exit");             
            break;
        }

    }
}
