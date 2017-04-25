/*
集合中存储的为图中节点编号
按距离进行扩展
当没有超过节点数目时，加入集合，否则按临时集合处理，所以不会涉及到结果集合的脚标更改问题
*/

#include<stdio.h>
#include<stdlib.h>

# define OK 1
# define ERROR 0
# define TURE 1
# define FALSE 0

struct PathEdgNode                              //边构体，存储路径中边的信息
{
	int source;                                 //边起点
	int target;                                 //边终点
	float weight;                               //连通概率
	PathEdgNode *nextpathedgnode;               //下一个节点的指针

	PathEdgNode()
	{
		source = -1;
		target = -1;
		weight = 0;
		nextpathedgnode = NULL;
	}
};

struct PathNode         //单一路径结构体
{
    //int pathnum;                                        //路径条数
	PathEdgNode *pathedgnodehead;                       //路径域，存储该顶点对应的一条路径
	PathNode *nextpathnode;                             //下一条路径的指针

	PathNode()					                        //初始化结构体
	{
	    //pathnum = 0;
		pathedgnodehead = new PathEdgNode;
		nextpathnode = NULL;
	}
};


struct setNode
{
    int footnote;           //脚标
    int vertexnodenum;      //节点编号
    int distance;           //距离
    float probability;      //概率
    int pathnum;            //路径数
    PathNode *pathhead;     //路径记录
    setNode *next;

    setNode()
    {
        footnote = 0;
        vertexnodenum = -1;
        distance = -1;
        probability = 0;
        pathnum = 0;
        pathhead = new PathNode;
        next = NULL;
    }
};

struct Set
{
    setNode *front;
    setNode *rear;
    int length;

    Set()
    {
        length = 0;
        //front = rear = (setNode*)malloc(sizeof(setNode));
        front = rear = new setNode;
        front->next = NULL;
    }
};

void setfront(Set *sethead,int sourcenum)
{
    PathNode *q;
    PathEdgNode *m;
    setNode *p = sethead->front;
    p->footnote = 0;
    p->vertexnodenum = sourcenum;
    p->distance = 0;
    p->probability = 1;
    p->pathnum = 1;
    q = p->pathhead;
    q->nextpathnode = new PathNode;
    q = q->nextpathnode;
    m = q->pathedgnodehead;
    m->nextpathedgnode = new PathEdgNode;
    m = m->nextpathedgnode;
    m->source = sourcenum;
    m->target = sourcenum;
    m->weight = 1;
    //q->pathnum++;
}

void linkSet(Set *sethead,Set *setheadt) //连接连个集合
{
    if(setheadt->front->next != NULL)
    {
        sethead->rear->next = setheadt->front->next;
        sethead->rear = setheadt->rear;
        sethead->length = sethead->length + setheadt->length;
        setheadt->rear = setheadt->front;
        setheadt->front->next = NULL;
        setheadt->length = 0;
    }
}

void prtPath(PathNode *pathhead)
{
    PathNode *pitem;
    PathEdgNode *qitem;

    pitem = pathhead;
    //printf("路径数为：%d  路径为：\n",pitem->pathnum);
    printf("路径为：\n");
    while(pitem->nextpathnode != NULL) //循环向下寻找
    {
        pitem = pitem->nextpathnode;
        //printf("路径数为：%d  路径为：\n",pitem->pathnum);
        qitem = pitem->pathedgnodehead;
        while(qitem->nextpathedgnode != NULL) //当路径条数不为空时，向后循环
        {
            qitem = qitem->nextpathedgnode;
                //printf("%d     ",mitem->target);
            printf("%d %d %f     ",qitem->source,qitem->target,qitem->weight);
        }
        printf("\n*******************************************\n");
        //pitem = pitem->nextpathnode;
    }
     printf("======================================================================= \n");
}

void prtSet(Set *sethead)
{
    setNode *p;
    p = sethead->front;
    if(sethead->front == sethead->rear)
    {
        printf("It is empty!\n");
    }
    else
    {
        printf("Set : \n");
        while(p->next != NULL)
        {
            p = p->next;
            printf("节点为：%d   距离为：%d 连通概率为：%f 路径数为：%d\n",p->vertexnodenum,p->distance,p->probability,p->pathnum);
            //printf("sdfsdf");
            prtPath(p->pathhead);
        }
    }
}

setNode *existSet(Set *sethead,int vernum)
{
    setNode *p;
    p = sethead->front;
    while(p != NULL)
    {
        if(p->vertexnodenum == vernum)
        {
            return p;
        }
        p = p->next;
    }
    return NULL;
}

void mathPath(PathNode *targethead,PathNode *sourcehead,int target,int source,float weight,int sornots)
{
    PathNode *p = targethead;
    PathNode *q = sourcehead;
    PathEdgNode *tt,*ts;//itemtarget,itemsource

    while( p->nextpathnode != NULL )
    {
        p = p->nextpathnode;
    }

    if( sornots == 1 )
    {
        p->nextpathnode = new PathNode;//源节点每有一条路径，均在目标节点尾部增加一个路径节点
        p = p->nextpathnode;
        tt = p->pathedgnodehead;
        tt->nextpathedgnode = new PathEdgNode;
        tt = tt->nextpathedgnode;
        tt->source = source;
        tt->target = target;
        tt->weight = weight;
        //p->pathnum++;
    }
    else
    {
        while(q->nextpathnode != NULL)
        {
            q = q->nextpathnode;
            ts = q->pathedgnodehead;
            p->nextpathnode = new PathNode;//源节点每有一条路径，均在目标节点尾部增加一个路径节点
            p = p->nextpathnode;
            tt = p->pathedgnodehead;
            while( ts->nextpathedgnode != NULL )
            {
                ts = ts->nextpathedgnode;
                tt->nextpathedgnode = new PathEdgNode;
                tt = tt->nextpathedgnode;
                tt->source = ts->source;
                tt->target = ts->target;
                tt->weight = ts->weight;
            }
            tt->nextpathedgnode = new PathEdgNode;
            tt = tt->nextpathedgnode;
            tt->source = source;
            tt->target = target;
            tt->weight = weight;
            //p->pathnum++;
        }
    }
}


void enSet(Set *sethead,Set *setheadt,int sourcenum,int targetnum,float weight,int distance)
{
    setNode *p;
    setNode *q;
    //    PathNode *m;
  //  PathNode *n;
    int sornots = 0;

    // if(targetnum == 7)
    //{
    //    printf("======================\n");
    //}

    p = existSet(sethead,sourcenum);
    q = existSet(setheadt,targetnum);
    if(sourcenum == sethead->front->vertexnodenum)
    {
        sornots = 1;
    }

    if( q == NULL )
    {
        q = new setNode;
        /*
        p=(setNode*)malloc(sizeof(setNode));
        if(!p)
        {
            printf("Overflow !\n");
            return (ERROR);
        }
        */
        q->footnote = setheadt->rear->footnote + 1;
        q->vertexnodenum = targetnum;
        q->distance = distance;

        //if(sourcenum == 1 && targetnum == 4)
        //{
        //    printf("1 4 ======================\n");
        //}
        //printf("%d %d %d %d %d\n",sourcenum,targetnum,distance,sornots,q->pathnum);
        if(sornots == 1)
        {
            //printf("sornots is 1");
            q->pathnum++;
        }
        else
        {
            q->pathnum = q->pathnum + p->pathnum;
        }
        //printf("%d\n",q->pathnum);
        mathPath(q->pathhead,p->pathhead,targetnum,sourcenum,weight,sornots);
        q->next = NULL;
        setheadt->rear->next=q;
        setheadt->rear = setheadt->rear->next;
        setheadt->length = setheadt->length + 1;
    }
    else
    {
        q->pathnum = q->pathnum + p->pathnum;
        //printf("exist %d %d %d %d\n",sourcenum,targetnum,distance,sornots);
        mathPath(q->pathhead,p->pathhead,targetnum,sourcenum,weight,sornots);
    }
}

void enSetNodetoSet(Set *sethead,setNode *setnode)
{
    sethead->rear->next = setnode;
    sethead->rear = sethead->rear->next;
    sethead->length++;
}

Set *bubblesortSet(Set *sethead,int need)
{
    Set *setheaditem = new Set;
    setNode *p,*q;
    int i;
    for(i=0;i<need;i++)
    {
        p = sethead->front->next;
        q = sethead->front;

        while(p->next != NULL)
        {

            if(p->next->probability > q->next->probability)
            {
                q = p;
            }
            p = p->next;
        }
        p = q->next;
        q->next = p->next;
        p->next = NULL;
        enSetNodetoSet(setheaditem,p);
    }
    return setheaditem;
}

void prtSettoFile(Set *sethead,Set *setheadt,int need)
{
    setNode *p = sethead->front;
    setNode *q = setheadt->front;
    printf("print the result set to file start.\n");

    FILE *fp;   //定义一个名叫fp文件指针
    //fp = fopen("result-1000-5000.txt","w");  //判断按读方式打开一个文件是否失败
    //fp = fopen("resulttestthecode.txt","w");
     fp = fopen("E://graduationproject//file//randomresult//testtheresult-100-10000-15.txt","w");  //判断按读方式打开一个文件是否失败
	if( fp == NULL )                                //打开操作不成功 E://graduationproject//code//123.txt
	{
	    printf("The file can not be opened.\n");
	    exit(1);
	}
    while(p->next != NULL)
	{
		p = p->next;
		fprintf(fp,"%5d\t%5d\t\t%d\t\t%f",sethead->front->vertexnodenum,p->vertexnodenum,p->distance,p->probability);
		if( p->next != NULL )
        {
            fprintf(fp,"\n");
        }
	}
	fprintf(fp,"\n\n");
	if(need > 0)   //节点不够，写入数据进行提醒
    {
        fprintf(fp,"there is not enough point!\n");
        fprintf(fp,"We have given you all points which we have found!\n ");
    }
    else        //节点够，输入到文件
    {
        while(q->next != NULL)
        {
            q = q->next;
            fprintf(fp,"%5d\t%5d\t\t%d\t\t%f",sethead->front->vertexnodenum,q->vertexnodenum,q->distance,q->probability);
            if( q->next != NULL )
            {
                fprintf(fp,"\n");
            }
        }
    }


     if( fclose(fp) != 0 )
    {
    	printf("The file can not be closed.\n");
    	exit(1);
    }
}

void destroySet(Set *sethead)
{
    while(sethead->front)
    {
        sethead->rear = sethead->front->next;
        free(sethead->front);
        sethead->front = sethead->rear;
    }
}
