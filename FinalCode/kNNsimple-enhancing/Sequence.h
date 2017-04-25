/*
��ͷ�ļ��У����ڱ�ʾ·���µıߵļ��Ͻṹ
�����߽ڵ�ṹ��Ķ���
*/

#include <stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<math.h>

#define DEBUG
# define OK 1
# define ERROR 0
# define TURE 1
# define FALSE 0

/*�ṹ���������߽ṹ�壬�ڵ�ṹ�壬�Լ�ͼ�ڽӱ�ṹ��*/

struct Sequence
{
    int *sequencearray;
    int row;
    int column;
    int top;
};

void initSequence(Sequence *sequence,int r,int c)
{
    int i=0;
    int sum;
    sum = r*c;
    sequence->row = r;
    sequence->column = c;
    sequence->top = sum;
    sequence->sequencearray = (int *)malloc(sum*sizeof(int));

    //sequence->sequencearray = (int *)colloc(sum*sizeof(int));
    while( i < sum )
    {
        //printf("init i is %d\n",i);
        sequence->sequencearray[i++] = 0;
        //printf("the data is %d\n",sequence->sequencearray[i]);
        //i++;
    }



}

void enSequence(Sequence *sequence,int n)
{
    sequence->sequencearray[sequence->top++] = n;
}

/*record the num of 1*/
int recordoneSequence(Sequence *sequence,int row)
{
    int start = sequence->column * row;
    int endnum = sequence->column * (row+1);
    int singal = 0;

    while(start < endnum)
    {
        if(sequence->sequencearray[start] == 1)
        {
            singal++;
        }
        start++;
    }
    return singal;
}

void prtSequence(Sequence *sequence)
{
    int i=0;
    int t = sequence->column;

    //printf("column is %d\n",sequence->column);
    //printf("top is %d\n",sequence->top);
    while( i < sequence->top )
    {
        printf("%d",sequence->sequencearray[i++]);
        if( (i%sequence->column) == t)
        {
            printf("\n");
        }
    }
}

void destroySequence(Sequence *sequencehead)
{
    free(sequencehead->sequencearray);
    free(sequencehead);
    sequencehead = NULL;
}
