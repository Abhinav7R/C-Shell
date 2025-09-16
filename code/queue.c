#include "headers.h"

void Push(Queue head,int val, char* name)
{
    head->val++;
    if(head->next==NULL)
    {
        head->next=(Queue)malloc(sizeof(Q));
        head->next->next=head->next;
        head->next->previous=head->next;
        head->next->val=val;
        head->next->name=name;
        return;
    }
    if(head->next->next==head->next)
    {
        head->next->next=(Queue)malloc(sizeof(Q));
        head->next->next->next=head->next;
        head->next->next->previous=head->next;
        head->next->next->val=val;
        head->next->next->name=name;
        head->next->previous=head->next->next;
        return;

    }
    else
    {
        Queue temp=head->next->previous;
        head->next->previous->next=(Queue)malloc(sizeof(Q));
        head->next->previous->next->previous=temp;
        head->next->previous->next->next=head->next;
        head->next->previous->next->val=val;
        head->next->previous->next->name=name;
        head->next->previous=temp->next;

    }
}

poppedelement Pop(Queue head)
{
    poppedelement popped;

    if(head->next==NULL)
    {
        popped.val=-1;
        popped.name=NULL;
        return popped;
    }
    head->val--;
    if(head->next->next==head->next)
    {
        int r=head->next->val;
        char* name=head->next->name;
        popped.name=name;
        popped.val=r;
        head->next=NULL;
        return popped;
    }
    else
    {
        int r=head->next->val;
        char* name=head->next->name;
        popped.name=name;
        popped.val=r;

        Queue temp=head->next;
        head->next=head->next->next;
        head->next->previous=temp->previous;
        temp->previous->next=head->next;

        return popped;
    }
}

int find_by_val(Queue head, int val)
{
    int n=head->val;
    if(n==0)
    {
        return 0;
    }
    Queue temp=head->next;
    while(n--)
    {
        if(temp->val==val)
        {
            return 1;
        }
        temp=temp->next;
    }
    return 0;
}