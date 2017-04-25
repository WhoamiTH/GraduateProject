#include<stdio.h>
#include<stdlib.h>

struct Stack                //ջ�ṹ�壬���ڴ洢���ɵ�����
{
    int *stackarray;        //����ռ䣬���ڴ洢����
    int top;                //ջ��λ��
    int sizenum;            //ջ�Ĵ�С
};

void initstack(Stack *stackhead,int n)
{
    stackhead->sizenum = n;
    stackhead->stackarray = (int *)malloc(n*sizeof(int));
    //stackthead->top = stackthead->base = 0;
    stackhead->top = 0;
}

void pushStack(Stack *stackhead,int num)
{
    if(stackhead->top > stackhead->sizenum)
    {
        printf("error!\n");
        printf("there is not enough memery!\n");
        exit(0);
    }
    stackhead->stackarray[stackhead->top++] = num;
}

int popStack(Stack *stackhead)
{
    int num;
    if(stackhead->top == 0)
    {
        printf("The Stack is NULL\n");
        exit(0);
    }
    num = stackhead->stackarray[--stackhead->top];
    return num;
}

void prtStack(Stack *stackhead)
{
    int i=0;
    while( i < stackhead->top )
    {
        printf("%d",stackhead->stackarray[i]);
        i++;
    }
    printf("\n");
}

void destroyStack(Stack *stackhead)
{
    free(stackhead->stackarray);
    free(stackhead);
    stackhead = NULL;
}
