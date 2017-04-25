/*队列中存储的为图中节点编号*/

#include<stdio.h>
#include<stdlib.h>

# define OK 1
# define ERROR 0
# define TURE 1
# define FALSE 0

struct qNode
{
    int vertexnodenum;
    qNode *next;
};

void initqNode(qNode *qnode)
{
    qnode->vertexnodenum = -1;
    qnode->next = NULL;
}

struct Queue
{
    qNode *front;
    qNode *rear;

    /*
    Queue()
    {
        front = rear = (qNode*)malloc(sizeof(qNode));
    }
    */

};

void initQueue(Queue *queuehead)
{
    queuehead->front = queuehead->rear = (qNode*)malloc(sizeof(qNode));
    initqNode(queuehead->front);
}

int enQueue(Queue *queuehead,int num)
{
    qNode *p = (qNode*)malloc(sizeof(qNode));
    /*
    if(!p)
    {
        printf("Overflow !\n");
        return (ERROR);
    }*/
    initqNode(p);
    p->vertexnodenum = num;
    p->next = NULL;
    queuehead->rear->next=p;
    queuehead->rear=p;
    return OK;
}

int deQueue(Queue *queuehead)
{
    qNode *p;
    int x;
    if(queuehead->front == queuehead->rear)
    {
        printf("It is empty!\n");
        return ERROR;
    }
    p = queuehead->front->next;
    x = p->vertexnodenum;
    if( queuehead->front->next == queuehead->rear )
    {
        queuehead->rear = queuehead->front;
        queuehead->front->next = NULL;
    }
    else
    {
        queuehead->front->next = p->next;
        p->next = NULL;
    }
    free(p);
    return x;
}

void prtQueue(Queue *queuehead)
{
    qNode *p;
    p = queuehead->front;
    if(queuehead->front == queuehead->rear)
    {
        printf("It is empty!\n");
    }
    else
    {
        printf("Queue : ");
        while(p != queuehead->rear)
        {
            p = p->next;
            printf("%d\t",p->vertexnodenum);
        }
        printf("\n");
    }
}

int lengthQueue(Queue *queuehead)
{
    qNode *p;
    int i = 0;
    p = queuehead->front;
    while(p->next != NULL)
    {
        i++;
        p = p->next;
    }
    return i;
}

int emptyQueue(Queue *queuehead)
{
    if(queuehead->front == queuehead->rear)
    {
        return TURE;
    }
    else
    {
        return FALSE;
    }
}

void destroyQueue(Queue *queuehead)
{
    while(queuehead->front)
    {
        queuehead->rear = queuehead->front->next;
        free(queuehead->front);
        queuehead->front = queuehead->rear;
    }
    free(queuehead);
    queuehead = NULL;
}

void clearQueue(Queue *queuehead)
{
    qNode *p,*q;
    queuehead->rear = queuehead->front;
    p = queuehead->front->next;
    queuehead->front->next = NULL;
    while(p)
    {
        q = p;
        p = p->next;
        free(q);
    }
}

int getheadQueue(Queue *queuehead)
{
    int x;
    qNode *p;
    if(queuehead->front == queuehead->rear)
    {
        return ERROR;
    }
    p = queuehead->front->next;
    x = p->vertexnodenum;
    return x;
}

void changedata(Queue *queuehead,Queue *queueheadt)
{
    qNode *p;
    p = queueheadt->front;
    while(p->next != NULL)
    {
        p = p->next;
        enQueue(queuehead,p->vertexnodenum);
    }
}

/*
int testqueue()
{
    Queue *queuehead = new Queue;
    Queue *queueheadt = new Queue;
    int i = 0;



    for(i=0;i<10;i++)
    {
        enQueue(queuehead,i);
    }
    prtQueue(queuehead);
    for(i=0;i<10;i++)
    {
        enQueue(queueheadt,i);
    }
    prtQueue(queueheadt);
    changedata(queuehead,queueheadt);
    prtQueue(queuehead);

    item = emptyQueue(queuehead);
    printf("Empty is %d\n",item);
    item = emptyQueue(queuehead);
    printf("Empty is %d\n",item);
    p = deQueue(queuehead);
    printf("Data is :%d\n",p);
    prtQueue(queuehead);
    clearQueue(queuehead);
    item = emptyQueue(queuehead);
    printf("Empty is %d\n",item);
    printf("front address is %p\n",queuehead->front);
    printf("rear address is %p\n",queuehead->rear);
    destroyQueue(queuehead);
    item = emptyQueue(queuehead);
    printf("Empty is %d\n",item);
    printf("front address is %p\n",queuehead->front);
    printf("rear address is %p\n",queuehead->rear);

    return 0;
}  */
