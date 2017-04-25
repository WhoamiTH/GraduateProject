/*
��ͷ�ļ��У����ڱ�ʾ·���µıߵļ��Ͻṹ
�����߽ڵ�ṹ��Ķ���
*/

#include <stdio.h>
#include<stdlib.h>
#include<math.h>

#define DEBUG
# define OK 1
# define ERROR 0
# define TURE 1
# define FALSE 0

/*�ṹ���������߽ṹ�壬�ڵ�ṹ�壬�Լ�ͼ�ڽӱ�ṹ��*/



struct SequenceNode                                   //�߹��壬�洢·���бߵ���Ϣ
{
    int footnote;                                   //�ű꣬����ȷ��λ��
	int data;                                       //���ڴ��0/1���ݣ�ȷ���Ƿ����
	SequenceNode *nextsequencenode;                     //��һ���ڵ��ָ��

	SequenceNode()
	{
	    footnote = 0;
		data = 0;
		nextsequencenode = NULL;
	}
};

struct Sequence
{
    SequenceNode *front;
    SequenceNode *rear;
    Sequence *nextsequence;

    Sequence()
    {
        front = rear = new SequenceNode;
        nextsequence = NULL;
    }
};

struct SequenceList
{
    Sequence *frontseq;
    Sequence *rearseq;
    int length;

    SequenceList()
    {
        frontseq = rearseq = new Sequence;
        length = 0;
    }
};
/*print function print Sequence and SequenceList*/
void prtSequence(Sequence *sequencehead)
{
    SequenceNode *p = sequencehead->front;
    while( p->nextsequencenode != NULL )
    {
        p = p->nextsequencenode;
        printf("%d",p->data);
    }
    printf("\n");
}

void prtSequenceList(SequenceList *sequencelisthead)
{
    Sequence *p = sequencelisthead->frontseq;
    while(p->nextsequence != NULL)
    {
        p = p->nextsequence;
        prtSequence(p);
    }
}
/*record the num of 1*/
int recordoneSequence(Sequence *sequencehead)
{
    SequenceNode *p = sequencehead->front;
    int singal = 0;
    while( p->nextsequencenode != NULL )
    {
        p = p->nextsequencenode;
        if( p->data == 1 )
        {
            singal++;//singal = singal + 1;
        }
    }
    return singal;
}

void enSequence(Sequence *sequencehead,SequenceNode *sequencenode)
{
    sequencenode->footnote = sequencehead->rear->footnote + 1;
    sequencehead->rear->nextsequencenode = sequencenode;
    sequencehead->rear = sequencehead->rear->nextsequencenode;
}

/*copy function copySequence */

void copySequence(Sequence *motherset,Sequence *copyversion)
{
    SequenceNode *p = motherset->front;
    SequenceNode *q;
    while( p->nextsequencenode != NULL)
    {
        p = p->nextsequencenode;
        q = new SequenceNode;
        q->footnote = p->footnote;
        q->data = p->data;
        enSequence(copyversion,q);
    }
}

void enSequenceList(SequenceList *sequencelisthead,Sequence *thesequence)
{

    sequencelisthead->length++;
    sequencelisthead->rearseq->nextsequence = thesequence;
    sequencelisthead->rearseq = sequencelisthead->rearseq->nextsequence;
    /*
    sequencelisthead->rearseq->nextsequence = new Sequence;
    sequencelisthead->rearseq = sequencelisthead->rearseq->nextsequence;
    copySequence(thesequence,sequencelisthead->rearseq);
    */
}




/*compare function there are three kinds of comparing function*/
int compareSequencewithSequence(Sequence *compared,Sequence *comparing)
{
    SequenceNode *m,*n;
    int singal = 0;

    m = compared->front;
    n = comparing->front;      //�ص��ȶ����е�ͷ�ڵ�
    while(m->nextsequencenode != NULL)
    {
        m = m->nextsequencenode;
        n = n->nextsequencenode;
        if( (m->data == n->data) && (m->data == 1) )
        {
            singal++;//signal = signal + 1;         //�����ڲ�ͬ��ʱ���ź�����1������ͬ����������
        }
    }
    return singal;                   //ѭ�������ϣ����ز�����
}

int compareSequencewithSequenceList(SequenceList *sequencelisthead,Sequence *sequencehead)
{
    Sequence *p = sequencelisthead->frontseq;
    int singalr,singalc;
    while(p->nextsequence != NULL)
    {
        p = p->nextsequence;
        singalr = recordoneSequence(p);
        singalc = compareSequencewithSequence(p,sequencehead);
        if( singalc == singalr )
        {
            return TURE;
        }
    }
    return FALSE;
}

SequenceList *compareSequenceListwithSequenceList(SequenceList *compared,SequenceList *comparing)
{
    SequenceList *resulthead = new SequenceList;
    Sequence *p = comparing->frontseq;
    Sequence *q;
    while( p->nextsequence != NULL )
    {
        p = p->nextsequence;
        if( compareSequencewithSequenceList(compared,p) )
        {
            q = new Sequence;
            copySequence(p,q);
            enSequenceList(resulthead,q);
            //mathp!!!!!!!!!!!!!!!!!!
            //prtSequence(p);
            // printf("\n");
        }
    }
    //printf("the possiblelist length is %d\n",resulthead->length);
    return resulthead;
}


void setSequence(Sequence *sequencehead,int site)
{
    SequenceNode *p = sequencehead->front;
    while(p->nextsequencenode != NULL)
    {
        p = p->nextsequencenode;
        if(p->footnote == site)
        {
            break;
        }
    }
    p->data = 1;
}

void initSequence(Sequence *sequencehead,int num) //num����ȫ������Ϊ0���ȴ�����
{
    SequenceNode *p;
    int i;

    for(i=0;i<num;i++)
    {
        p = new SequenceNode;
        p->footnote = i + 1;
        sequencehead->rear->nextsequencenode = p;
        sequencehead->rear = sequencehead->rear->nextsequencenode;
    }
}


/*
void destroySequenceNode(SequenceNode *sequencenodehead)
{
    SequenceNode *p;
    while(sequencenodehead)
    {
        p = sequencenodehead->nextsequencenode;
        delete(sequencenodehead);
        sequencenodehead = p;
    }
    //sequencenodehead = NULL;
}
*/

void destroySequenceNode(SequenceNode *sequencenodehead)
{
    SequenceNode *p,*q;
    p = sequencenodehead->nextsequencenode;
    while(p)
    {
        q = p->nextsequencenode;
        delete(p);
        p = q;
    }
    //sequencenodehead = NULL;
}



/*
void destroySequence(Sequence *sequencehead)
{
    while(sequencehead->front)
    {
        sequencehead->rear = sequencehead->front->nextsequencenode;
        destroySequenceNode(sequencehead->front);
        sequencehead->front = sequencehead->rear;
    }
    sequencehead->front = NULL;
    sequencehead->rear = NULL;
    delete(sequencehead);
}
*/

void destroySequence(Sequence *sequencehead)
{
    while(sequencehead->front)
    {
        sequencehead->rear = sequencehead->front->nextsequencenode;
        //destroySequenceNode(sequencehead->front);
        delete(sequencehead->front);
        sequencehead->front = sequencehead->rear;
    }
    sequencehead->front = NULL;
    sequencehead->rear = NULL;
    //delete(sequencehead);
}

void destroySequenceList(SequenceList *sequencelisthead)
{
    while(sequencelisthead->frontseq)
    {
        sequencelisthead->rearseq = sequencelisthead->frontseq->nextsequence;
        destroySequence(sequencelisthead->frontseq);
        sequencelisthead->frontseq = sequencelisthead->rearseq;
    }
    sequencelisthead->frontseq = NULL;
    sequencelisthead->rearseq = NULL;
    //sequencelisthead = NULL;
}
