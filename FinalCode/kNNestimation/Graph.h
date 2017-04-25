/*
此头文件中，用于邻接表表示的图结构
包括节点结构体，边结构体，图结构体的定义
并且包括建立图的各个功能函数，包括读入数据，建立邻接表等
*/



#include <stdio.h>
#include<stdlib.h>

#define DEBUG
//#define MAXVEX 9           //最大顶点数 36692 9
//#define TOTALVEX 9             //顶点总数 36692 9
//#define TOTALEDGE 28             //边的总数 367658 28

#define MAXVEX 36692           //最大顶点数 36692 9
#define TOTALVEX 36692             //顶点总数 36692 9
#define TOTALEDGE 367658             //边的总数 367658 28

typedef int VertexType;         //顶点类型应由用户定义
typedef float EdgeType;           //边上的权值类型应由用户定义

/*结构体声明，边结构体，节点结构体，以及图邻接表结构体*/

struct EdgeNode         //边结构体
{
	int adjvex;                 //邻接点域，存储该顶点对应的下标
	EdgeType weigth;            //用于存储权值，既边上的连通概率
	struct EdgeNode *next;      //指针，指向下一个邻接点



	/*
	EdgeNode()					//初始化结构体，有利于建立邻接表结构
	{
		adjvex = -1;
		weigth = 0;
		next = NULL;
	}
	*/

};

struct VertexNode       //顶点表结构
{
	VertexType data;            //顶点域，存储顶点信息
	EdgeNode *firstedge;        //边表头指针

	VertexNode()
	{
		data = -1;
		firstedge = (EdgeNode *)malloc(sizeof(EdgeNode));
		firstedge->adjvex = -1;
		firstedge->weigth = 0;
		firstedge->next = NULL;

	}
};

struct GraphList
{
	VertexNode adjList[MAXVEX];
	int numVertexes, numEdges;  //图中当前顶点数和边数
};

/*各个功能函数*/

int Locate(GraphList *g, char ch)
{
    int i;
    for (i = 0; i < MAXVEX; i++)
    {
        if (ch == g->adjList[i].data)
        {
            break;
        }
    }
    if (i >= MAXVEX)
    {
        printf("there is no vertex.\n");
        return -1;
    }
    return i;
}

//建立图的邻接表结构
void CreateGraph(GraphList *g)
{
    int  v1, v2;
    float pro;
    EdgeNode *p,*q;
    FILE *fp;   //定义一个名叫fp文件指针
    fp = fopen("Text.txt", "r");  //判断按读方式打开一个文件是否失败 testtext.txt
    if (fp == NULL)            //打开操作不成功 E://graduationproject//code//123.txt
    {
        printf("The file can not be opened.\n");
        exit(1);
    }
    //建立边表
    while (!feof(fp))
    {
        fscanf(fp, "%d %d %f", &v1, &v2,&pro);
#ifdef DEBUG
        //printf("the number are v1: %d,v2: %d,p: %f \n", v1, v2,pro);
#endif
        //向内存申请空间，生成边表结点
        p = (EdgeNode *)malloc(sizeof(EdgeNode));
        if (p == NULL)        //申请空间失败
        {
            printf("Can not malloc space!!!\n");
            exit(1);
        }
        //邻接序号为v2,设置边信息
        p->adjvex = v2;
        p->weigth = pro;
        p->next = NULL;
        //找到v1节点的末尾，添加新的边信息
        g->adjList[v1].data = v1;
        q = g->adjList[v1].firstedge;
#ifdef DEBUG
        //printf("q is %p\n", q->next);
#endif
        while (q->next != NULL)
        {
            q = q->next;
        }
        q->next = p;

    }
    if (fclose(fp) != 0)
    {
        printf("The file can not be closed.\n");
        exit(1);
    }
}


void printGraph(GraphList *g)
{
    int i = 0;
#ifdef DEBUG
    printf("printGraph() start.\n");
#endif
    for (i = 0; i<MAXVEX; i++)
    {
        printf("Vertexnode is :%d  ", i);
        EdgeNode *p = NULL;
        p = g->adjList[i].firstedge;
#ifdef DEBUG
        //printf("p->adjvex is %d ,p->weigh is %d\n",p->adjvex,p->weigth);
#endif
        while (p->next != NULL)
        {
            p = p->next;
            printf("%d  ", p->adjvex);
        }
        printf("\n");
    }
}


int testgraph()
{
    GraphList *g = new GraphList;
	CreateGraph(g);
	printGraph(g);
	return 0;
}
