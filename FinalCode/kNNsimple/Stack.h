#include<stdio.h>
#include<stdlib.h>

struct Stack                //栈结构体，用于存储生成的序列
{
    int *stackarray;        //数组空间，用于存储序列
    int top;                //栈顶位置
    int sizenum;            //栈的大小
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
