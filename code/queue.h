#ifndef __QUEUE_H__
#define __QUEUE_H__


typedef struct Q
{
    int val;
    char* name;
    struct Q* next;
    struct Q* previous;
}Q;

typedef struct poppedelement
{
    int val;
    char* name;
}poppedelement;

typedef Q* Queue;

void Push(Queue head,int val, char* name);
poppedelement Pop(Queue head);
int find_by_val(Queue head, int val);

#endif
