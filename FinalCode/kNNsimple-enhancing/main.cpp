#include "Graph.h"
#include "Queue.h"
#include "Set.h"
#include "PathSet.h"
#include "Sequence.h"
#include "Stack.h"
#include<stdlib.h>

#define TURE 1
#define FALSE 0


int bfssearch(GraphList *g,Set *sethead,Set *setheaditem,int searchnum,int sourcenum)
{
	int mark[MAXVEX],k,source,itemnum;
	int distance = 0;
	//Queue *queuehead = new Queue;
	//Queue *queueitem = new Queue;
	//Set *setitem = new Set;
	//Set *setitem = (Set *)malloc(sizeof(Set));
	//initSet(setitem);
	Queue *queuehead = (Queue *)malloc(sizeof(Queue));
	Queue *queueitem = (Queue *)malloc(sizeof(Queue));
	EdgeNode *p;

	initQueue(queuehead);
	initQueue(queueitem);

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
            //printf("source is %d target is %d\n",source,p->adjvex);
            if( mark[p->adjvex] == 0 )
			{
                mark[p->adjvex] = 1;
                enQueue(queueitem,g->adjList[p->adjvex].data);
            }
            if( existSet(sethead,p->adjvex) == NULL )
            {
                //enSet(sethead,setitem,source,p->adjvex,p->weigth,sethead->rear->distance+1);
                enSet(sethead,setheaditem,source,p->adjvex,p->weigth,sethead->rear->distance+1);
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
                //linkSet(sethead,setitem);
                linkSet(sethead,setheaditem);
                clearQueue(queueitem);
            }
            else if(itemnum == searchnum)
            {
                //linkSet(sethead,setitem);
                linkSet(sethead,setheaditem);
                destroyQueue(queuehead);
                destroyQueue(queueitem);
                return 0;//搜索的数目与扩展的数目正好相同，不要用再排序挑选了
            }
            else
            {
                //linkSet(setheaditem,setitem);
                destroyQueue(queuehead);
                destroyQueue(queueitem);
                return searchnum;//节点数目足够，比需要的还多，需要返回还需要的数，用于之后排序后挑选
            }
        }
    }
    destroyQueue(queuehead);
    destroyQueue(queueitem);
    return searchnum;//节点不够了，没有可以搜索的节点了，返回应该需要的搜索数
}

int compareStackwithSequence(Sequence *sequencehead,Stack *stackhead)
{
    int r;
    int singalr,singals;
    int s,st;

    //prtStack(stackhead);
    //prtSequence(sequencehead);
    //printf("row is %d\n",sequencehead->row);


    for(r=0;r<sequencehead->row;r++)
    {
        singalr = 0;
        singals = 0;
        s = sequencehead->column * r;
        st = 0;
        singalr = recordoneSequence(sequencehead,r);
       // printf("singalr is %d\n",singalr);
        //printf("s is %d st is %d\n",s,st);
        //printf("stackhead->top is %d\n",stackhead->top);
        while(st < stackhead->top)
        {
            //printf("s is %d st is %d\n",s,st);
            //if(stackhead->top == 4)
            //{
                //system("pause");
            //}

            if( (sequencehead->sequencearray[s] == 1) && (stackhead->stackarray[st] == 1) )
            {
                singals++;
            }
            s++;
            st++;
        }
        if( singalr == singals )
        {
            return TURE;
        }
    }
    return FALSE;
}

float getpStack(PathSet *pathsethead,Stack *stackhead)
{
    float p = 1;
    PathSetNode *m = pathsethead->front;
    int i=0;

    while(i<stackhead->top)
    {
        m = m->nextpathsetnode;
        if( stackhead->stackarray[i++] == 1 )
        {
            p = p*m->weight;
        }
        else
        {
            p = p * (1 - m->weight);
        }
    }
    return p;
}

void createSequence(int n,Stack *stackhead,Sequence *pathsequence,PathSet *pathsethead,double &possibility)
{
    pushStack(stackhead,0);
    int t = n-1;

    //printf("asdfasdfsadfsdafsfsfsdf\n");
    //printf("n is %d t is %d\n",n,t);
    //prtStack(stackhead);
    if(t > 0)
    {
        createSequence(t,stackhead,pathsequence,pathsethead,possibility);
    }
    else
    {
        if( compareStackwithSequence(pathsequence,stackhead) )
        {
            //prtStack(stackhead);
            possibility += getpStack(pathsethead,stackhead);
        }
    }
    popStack(stackhead);
    pushStack(stackhead,1);
    if(t > 0)
    {
        createSequence(t,stackhead,pathsequence,pathsethead,possibility);
    }
    else
    {
        if( compareStackwithSequence(pathsequence,stackhead) )
        {
            //prtStack(stackhead);
            //prtSequence(m);
            possibility += getpStack(pathsethead,stackhead);
        }
    }
    popStack(stackhead);
}


void changePathtoSequence(PathNode *pathnodehead,PathSet *pathsethead,Sequence *pathsequence,int pathsetlength,int pathnum)
{
    PathNode *p = pathnodehead;
    PathEdgNode *n;
    int r=0;
    int x;

    while(p->nextpathnode != NULL)
    {
        p = p->nextpathnode;
        n = p->pathedgnodehead;
        while( n->nextpathedgnode != NULL )
        {
            n = n->nextpathedgnode;
            x = existPathSet(pathsethead,n->source,n->target);
            x = r*pathsetlength + x - 1;
            pathsequence->sequencearray[x] = 1;
        }
        r++;
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



void getpSetNodepractical(setNode *setnode,double &probability)
{
    //PathSet *pathsethead = new PathSet;
    PathSet *pathsethead = (PathSet *)malloc(sizeof(PathSet));
    Sequence *pathsequence = (Sequence *)malloc(sizeof(Sequence));
    Stack *stackhead = (Stack *)malloc(sizeof(Stack));
    PathEdgNode *optedghead = (PathEdgNode *)malloc(sizeof(PathEdgNode));
    double opt = 1;

    initPathEdgNode(optedghead);

    if( (setnode->distance > 2) && (setnode->pathnum > 1) )//如果距离大于2且路径数大于1时，才可能优化，否则不可能存在优化条件
    {
        //initPathEdgNode(optedghead);//初始化优化后存储相同节点的链表
        optimizing(setnode->pathnum,setnode->distance,setnode->pathhead,optedghead);//执行优化
        opt = getpopt(optedghead);
    }
    //prtEdge(optedghead);
    //printf("%f\n",opt);
    //prtPath(setnode->pathhead);

    initPathSet(pathsethead);
    changePathtoPathSet(setnode->pathhead,pathsethead);
    //printf("pathnum is %d length is %d\n",setnode->pathnum,pathsethead->length);
    initSequence(pathsequence,setnode->pathnum,pathsethead->length);


    //Stack *stackhead = new Stack(pathsethead->length);
    initstack(stackhead,pathsethead->length);




    changePathtoSequence(setnode->pathhead,pathsethead,pathsequence,pathsethead->length,setnode->pathnum);
    //printf("==s=-df=sadf=-sdf=-sa-=df=sadf-=sd-f=-sadf-=asdf\n");
    //printf("sequence is:");
    //prtSequence(pathsequence);
    createSequence(pathsethead->length,stackhead,pathsequence,pathsethead,probability);
    //printf("%f\n",probability);
    probability = probability * opt;
    //printf("%f\n",probability);


    destroyPathSet(pathsethead);
    destroySequence(pathsequence);
    destroyStack(stackhead);
    //destroySequenceList(pathlist);
}

void getpSet(Set *sethead)
{
    setNode *p = sethead->front;
    int x=0,t;

    while( p->next != NULL )
    {
        x++;
        t = x % 101;
        if(t == 100)
        {
            printf("We have a hard time in calculating!!!Please wait for a moment!!!\n");
        }
        p = p->next;
        getpSetNodepractical(p,p->probability);
        //printf("%d   %f\n",p->vertexnodenum,p->probability);
    }
}

int main()
{
    //Set *sethead = new Set;
    //Set *setheaditem = new Set;
    //GraphList *g = new GraphList;
    Set *sethead;
    Set *setheaditem;
    GraphList *g;
    int searchnum = 100;//20
    int sourcenum = 0;//4
    int need;

    g = (GraphList *)malloc(sizeof(GraphList));
    initGraphList(g);
    sethead = (Set *)malloc(sizeof(Set));
    initSet(sethead);
    setheaditem = (Set *)malloc(sizeof(Set));
    initSet(setheaditem);

	CreateGraph(g);
	printf("create graph completed!\n");
	/*
    printf("Please input the source number:");
	scanf("%d",&sourcenum);
	printf("Please input the search number:");
	scanf("%d",&searchnum);
	*/
    need = bfssearch(g,sethead,setheaditem,searchnum,sourcenum);
    printf("bfssearch graph completed!\n");
    //prtSet(sethead);
    getpSet(sethead);
    printf("getpSet sethead completed!\n");
    getpSet(setheaditem);
    printf("getpSet setheaditem completed!\n");

    //printf("%d\n",need);
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
            //quicksortSet(setheaditem);
            printf("bubblesortSet set completed!\n");
            //prtSet(setheaditem);
            //selectSet(setheaditem,need);
            need = 0;
        }
    }
    prtSettoFile(sethead,setheaditem,need);
    printf("printSettofile completed!\n");
    printf("mission completed!\n");
    return 0;
}
