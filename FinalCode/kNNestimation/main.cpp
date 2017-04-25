#include "Graph.h"
#include "Queue.h"
#include "Set.h"
#include "PathSet.h"
#include "Sequence.h"
#include<stdlib.h>
#include<windows.h>

#include<time.h>

#define TOTALPRONUM 50000
#define BACKGROND 100
#define SEARCHNUM 100

//int TOTALPRONUM;

int bfssearch(GraphList *g,Set *sethead,Set *setheaditem,int searchnum,int sourcenum)
{
	int mark[MAXVEX],k,source,itemnum;
	int distance = 0;
	Queue *queuehead = new Queue;
	Queue *queueitem = new Queue;
	Set *setitem = new Set;
	EdgeNode *p;

	//int nodenum=0;

	for(k=0;k<MAXVEX;k++) //对标记数组初始化
	{
		mark[k]=0;
	}
	mark[sourcenum] = 1;   			//对起始节点进行标注，并开始进行宽度优先搜索
    setfront(sethead,sourcenum);
    enQueue(queuehead,g->adjList[sourcenum].data); 		//当前结点编号入队q.ins_sq_Queue(k);
    while( !emptyQueue(queuehead) ) 				//队列不空时，循环扩展 不空时，emptyQueue返回0，空时返回1
    {
        source = deQueue(queuehead); 	//从队列中退出一个结点作为当前结点
        p = g->adjList[source].firstedge;
        while( p->next != NULL) 			//还有后件
        {
            p = p->next;
            if( mark[p->adjvex] == 0 )
			{
			    //nodenum++;//记得删除
                mark[p->adjvex] = 1;
                enQueue(queueitem,g->adjList[p->adjvex].data);
            }
            if( existSet(sethead,p->adjvex) == NULL )
            {
                enSet(sethead,setitem,source,p->adjvex,p->weigth,sethead->rear->distance+1);
            }
        }
        if( emptyQueue(queuehead) )
        {
            distance = distance + 1;
            itemnum = lengthQueue(queueitem);
            if(itemnum < searchnum)    //当节点数目少于或等于搜寻节点数目时
            {
                searchnum = searchnum - itemnum;    //更新搜寻节点数目
                changedata(queuehead,queueitem); //将节点临时队列中的信息添加到主队列中，准备下一轮的扩展搜索
                linkSet(sethead,setitem);
                clearQueue(queueitem);
            }
            else if(itemnum == searchnum)
            {
                linkSet(sethead,setitem);
                //printf("the node number is %d\n",nodenum);
                return 0;//搜索的数目与扩展的数目正好相同，不要用再排序挑选了
            }
            else
            {
                linkSet(setheaditem,setitem);
                //printf("the node number is %d\n",nodenum);
                return searchnum;//节点数目足够，比需要的还多，需要返回还需要的数，用于之后排序后挑选
            }
        }
    }
    //printf("the node number is %d\n",nodenum);
    return searchnum;//节点不够了，没有可以搜索的节点了，返回应该需要的搜索数
}

void changePathtoSequenceList(PathNode *pathnodehead,PathSet *pathsethead,SequenceList *pathlist,int length)
{
    PathNode *p = pathnodehead;
    PathEdgNode *n;
    Sequence *m;
    int x;

    while(p->nextpathnode != NULL)
    {
        p = p->nextpathnode;
        m = new Sequence;
        initSequence(m,length);
        n = p->pathedgnodehead;
        while( n->nextpathedgnode != NULL )
        {
            n = n->nextpathedgnode;
            x = existPathSet(pathsethead,n->source,n->target);
            setSequence(m,x);
        }
        enSequenceList(pathlist,m);
    }
}

void changePathtoPathSet(PathNode *pathnodehead,PathSet *pathsethead)
{
    PathNode *p = pathnodehead;
    PathEdgNode *t;

    while(p->nextpathnode != NULL)
    {
        p = p->nextpathnode;
        t = p->pathedgnodehead;
        while(t->nextpathedgnode != NULL)
        {
            t = t->nextpathedgnode;
            if( !existPathSet(pathsethead,t->source,t->target) )
            {
                enPathSet(pathsethead,t->source,t->target,t->weight);
            }
        }
    }
}

int createpossiblelistrandom(SequenceList *pathlist,PathSet *pathsethead)
{
    Sequence *sequenceitem = new Sequence;
    //SequenceNode *sequencenode;
    PathSetNode *p ;
    SequenceNode *q;
    int singal = 0;
    int i;
    float t;
    LARGE_INTEGER ct;
    LONGLONG seed;

    initSequence(sequenceitem,pathsethead->length);

    for(i=0;i<TOTALPRONUM;i++)  //产生可能世界数
    {
        p = pathsethead->front;
        q = sequenceitem->front;
        QueryPerformanceCounter(&ct);
        seed = ct.QuadPart;
        srand( seed );
        while(p->nextpathsetnode != NULL)
        {
            p = p->nextpathsetnode;
            //sequencenode = new SequenceNode;
            q = q->nextsequencenode;
            t = ( float )(rand()%(BACKGROND+1)) / BACKGROND;
            if( t <= p->weight ) //小于，则证明存在
            {
               q->data = 1;
            }
            else
            {
                q->data = 0;
            }
            //enSequence(sequenceitem,sequencenode);
        }
        if( compareSequencewithSequenceList(pathlist,sequenceitem) )
        {
            singal++;
        }

    }
    destroySequence(sequenceitem);
    sequenceitem=NULL;
    return singal;
}

void getpSetNoderandom(setNode *setnode,float &probability)
{
    PathSet *pathsethead = new PathSet;
    SequenceList *pathlist = new SequenceList;
    int score;

    changePathtoPathSet(setnode->pathhead,pathsethead);
    changePathtoSequenceList(setnode->pathhead,pathsethead,pathlist,pathsethead->length);
    score = createpossiblelistrandom(pathlist,pathsethead);
    probability = (float) score / TOTALPRONUM ;
    destroyPathSet(pathsethead);
    delete(pathsethead);
    pathsethead = NULL;
    destroySequenceList(pathlist);
    delete(pathlist);
    pathlist = NULL;
}

void getpSet(Set *sethead)
{
    setNode *p = sethead->front;
    int x=0,t;
    while( p->next != NULL )
    {
        p = p->next;
        x++;
        t = x % 501;
        if(t == 500)
        {
            printf("We have a hard time in calculating!!!Please wait for a moment!!!\n");
        }
        getpSetNoderandom(p,p->probability);
    }
}

int main()
{
    Set *sethead = new Set;
    Set *setheaditem = new Set;
    GraphList *g = new GraphList;
    int searchnum;  //10000;//20= SEARCHNUM;
    int sourcenum; //4= 0;
    int need;

    searchnum = 100;
    sourcenum = 0;
	CreateGraph(g);
	/*
	printf("create graph completed!\n");
	printf("Please input the source number:");
	scanf("%d",&sourcenum);
	printf("Please input the search number:");
	scanf("%d",&searchnum);
    */

    need = bfssearch(g,sethead,setheaditem,searchnum,sourcenum);
    printf("bfssearch graph completed!\n");
    getpSet(sethead);
    printf("getpSet sethead completed!\n");
    getpSet(setheaditem);
    printf("getpSet setheaditem completed!\n");
    if(need > 0)
    {
        if( setheaditem->front->next == NULL ) //节点不够
        {
            printf("there is not enough point!\n");
            printf("We have given you all points which we have found!\n ");
            //system("pause");
        }
        else //节点数目够
        {
            setheaditem = bubblesortSet(setheaditem,need);
            printf("bubblesortSet set completed!\n");
            //quicksortSet(setheaditem);
            //printf("quicksortSet set completed!\n");
            //prtSet(setheaditem);
            need = 0;
        }
    }
    prtSettoFile(sethead,setheaditem,need);
    printf("printSettofile completed!\n");
    printf("mission completed!\n");
    return 0;
}
