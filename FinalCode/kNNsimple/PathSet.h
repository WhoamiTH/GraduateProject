/*
此头文件中，用于表示路径下的边的集合结构
包括边节点结构体的定义
*/

#include <stdio.h>
#include<stdlib.h>

#define DEBUG
# define OK 1
# define ERROR 0
# define TURE 1
# define FALSE 0

/*结构体声明，边结构体，节点结构体，以及图邻接表结构体*/



struct PathSetNode                                   //边构体，存储路径中边的信息
{
    int footnote;                               //脚标，用于确定位置
	int source;                                 //边起点
	int target;                                 //边终点
	float weight;                               //连通概率
	PathSetNode *nextpathsetnode;                         //下一个节点的指针

	/*
	PathSetNode()
	{
	    footnote = 0;
		source = -1;
		target = -1;
		weight = 0;
		nextpathsetnode = NULL;
	}
	*/
};

void initPathSetNode(PathSetNode *pathsetnode)
{
    pathsetnode->footnote = 0;
    pathsetnode->source = -1;
    pathsetnode->target = -1;
    pathsetnode->weight = 0;
    pathsetnode->nextpathsetnode = NULL;
}

struct PathSet
{
    PathSetNode *front;
    PathSetNode *rear;
    int length;
    /*
    PathSet()
    {
        front = rear = new PathSetNode;
        length = 0;
    }
    */
};

void initPathSet(PathSet *pathset)
{
    pathset->front = pathset->rear = (PathSetNode *)malloc(sizeof(PathSetNode));
    initPathSetNode(pathset->front);
    pathset->length = 0;
}

int existPathSet(PathSet *pathsethead,int sourcenum,int targetnum)
{
    PathSetNode *p = pathsethead->front;
    while(p->nextpathsetnode != NULL)
    {
        p = p->nextpathsetnode;
        if( (p->source == sourcenum) && (p->target == targetnum) )
        {
            return p->footnote;
        }
    }
    return FALSE;
}

void enPathSet(PathSet *pathsethead,int sourcenum,int targetnum,float weight)
{
    //PathSetNode *p = new PathSetNode;
    PathSetNode *p = (PathSetNode *)malloc(sizeof(PathSetNode));
    initPathSetNode(p);

    p->source = sourcenum;
    p->target = targetnum;
    p->weight = weight;
    p->footnote = pathsethead->rear->footnote + 1;
    pathsethead->rear->nextpathsetnode = p;
    pathsethead->rear = pathsethead->rear->nextpathsetnode;
    pathsethead->length = pathsethead->length + 1;
}

void prtPathSet(PathSet *pathsethead)
{
    PathSetNode *p;
    p = pathsethead->front;
    //if(pathsethead->front == pathsethead->rear)
    //{
        //printf("It is empty!\n");
    //}
    if(pathsethead->length == 0 )
    {
        printf("It is empty!\n");
    }
    else
    {
        printf("PathSet length is %d \n",pathsethead->length);
        printf("PathSet : \n");
        while(p != pathsethead->rear)
        {
            p = p->nextpathsetnode;
            //printf("%d %d %f\n",p->source,p->target,p->weight);
            printf("%d %d %d %f\n",p->footnote,p->source,p->target,p->weight);
        }
    }
}

void destroyPathSet(PathSet *pathsethead)
{
    while(pathsethead->front)
    {
        pathsethead->rear = pathsethead->front->nextpathsetnode;
        free(pathsethead->front);
        pathsethead->front = pathsethead->rear;
    }
    pathsethead->front = NULL;
    pathsethead->rear = NULL;
    free(pathsethead);
    pathsethead = NULL;
}
