/*
��ͷ�ļ��У������ڽӱ��ʾ��ͼ�ṹ
�����ڵ�ṹ�壬�߽ṹ�壬ͼ�ṹ��Ķ���
���Ұ�������ͼ�ĸ������ܺ����������������ݣ������ڽӱ��
*/



#include <stdio.h>
#include<stdlib.h>

#define DEBUG
//#define MAXVEX 6           //��󶥵��� 36692 9
//#define TOTALVEX 6             //�������� 36692 9
//#define TOTALEDGE 12             //�ߵ����� 367658 28

#define MAXVEX 36692           //��󶥵��� 36692 9
#define TOTALVEX 36692             //�������� 36692 9
#define TOTALEDGE 367658             //�ߵ����� 367658 28

typedef int VertexType;         //��������Ӧ���û�����
typedef float EdgeType;           //���ϵ�Ȩֵ����Ӧ���û�����

/*�ṹ���������߽ṹ�壬�ڵ�ṹ�壬�Լ�ͼ�ڽӱ�ṹ��*/

struct EdgeNode         //�߽ṹ��
{
	int adjvex;                 //�ڽӵ��򣬴洢�ö����Ӧ���±�
	EdgeType weigth;            //���ڴ洢Ȩֵ���ȱ��ϵ���ͨ����
	struct EdgeNode *next;      //ָ�룬ָ����һ���ڽӵ�



	/*
	EdgeNode()					//��ʼ���ṹ�壬�����ڽ����ڽӱ�ṹ
	{
		adjvex = -1;
		weigth = 0;
		next = NULL;
	}
	*/

};

void initEdgNode(EdgeNode *edgenode)
{
    edgenode->adjvex = -1;
    edgenode->weigth = 0;
    edgenode->next = NULL;
}

struct VertexNode       //�����ṹ
{
	VertexType data;            //�����򣬴洢������Ϣ
	EdgeNode *firstedge;        //�߱�ͷָ��

	/*
	VertexNode()
	{
		data = -1;
		firstedge = (EdgeNode *)malloc(sizeof(EdgeNode));
		firstedge->adjvex = -1;
		firstedge->weigth = 0;
		firstedge->next = NULL;
	}
	*/
};

void initVertexNode(VertexNode *vertexnode)
{
    vertexnode->data = -1;
    vertexnode->firstedge = (EdgeNode *)malloc(sizeof(EdgeNode));
    initEdgNode(vertexnode->firstedge);
}

struct GraphList
{
	//VertexNode adjList[MAXVEX];
	VertexNode *adjList;
	int numVertexes, numEdges;  //ͼ�е�ǰ�������ͱ���
};

void initGraphList(GraphList *g)
{
    int i=0;
    g->numVertexes = MAXVEX;
    g->numEdges = TOTALEDGE;
    g->adjList = (VertexNode *)malloc(MAXVEX*sizeof(VertexNode));
    while(i<MAXVEX)
    {
        //printf("i is %d\n",i);
        initVertexNode(&g->adjList[i]);
        i++;
    }
}

/*�������ܺ���*/

//����ͼ���ڽӱ�ṹ
void CreateGraph(GraphList *g)
{
    int  v1, v2;
    float pro;
    EdgeNode *p,*q;
    FILE *fp;   //����һ������fp�ļ�ָ��
    fp = fopen("Text.txt", "r");  //�жϰ�����ʽ��һ���ļ��Ƿ�ʧ�� testtext.txt
    if (fp == NULL)            //�򿪲������ɹ� E://graduationproject//code//123.txt
    {
        printf("The file can not be opened.\n");
        exit(1);
    }
    //�����߱�
    while (!feof(fp))
    {
        fscanf(fp, "%d %d %f", &v1, &v2,&pro);
#ifdef DEBUG
        //printf("the number are v1: %d,v2: %d,p: %f \n", v1, v2,pro);
#endif
        //���ڴ�����ռ䣬���ɱ߱���
        p = (EdgeNode *)malloc(sizeof(EdgeNode));
        if (p == NULL)        //����ռ�ʧ��
        {
            printf("Can not malloc space!!!\n");
            exit(1);
        }
        //�ڽ����Ϊv2,���ñ���Ϣ
        p->adjvex = v2;
        p->weigth = pro;
        p->next = NULL;
        //�ҵ�v1�ڵ��ĩβ������µı���Ϣ
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
