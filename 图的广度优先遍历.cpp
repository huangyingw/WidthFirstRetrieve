// 图的广度优先遍历.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
using namespace std;
#define MaxVertexNum 100
typedef int VertexType;

typedef enum{FALSE,TRUE}Boolean;//FALSE为0，TRUE为1

Boolean visited[MaxVertexNum]; //访问标志向量是全局量

#define QueueSize 100   //应根据具体情况定义该值

//typedef char Queue DataType;  //DataType的类型依赖于具体的应用
//#define DataType int

typedef int Queue, DataType;  //DataType的类型依赖于具体的应用
typedef struct Sturet
{               
	int front;  //头指针，队非空时指向队头元素            
    int rear;  //尾指针，队非空时指向队尾元素的下一位置             
	int count;  //计数器，记录队中元素总数
    DataType data[QueueSize];
}CirQueue;

typedef struct node
{	
	int adjvex; 
	struct node *next;
	//若要表示边上的权，则应增加一个数据域
}EdgeNode;

typedef struct vnode
{
	//顶点表结点
	VertexType vertex; //顶点域
	EdgeNode *firstedge;//边表头指针
}VertexNode;

typedef VertexNode AdjList[MaxVertexNum];//AdjList是邻接表类型

typedef struct ALGraph
{
	AdjList adjlist;//邻接表
	int n; //图中当前顶点数
	int e;//图中当前边数 
}Graphic; //对于简单的应用，无须定义此类型，可直接使用AdjList类型。 

void BFS(ALGraph*G,int k);
int QueueEmpty(CirQueue *Q);
void Error(char* message);

DataType QueueFront(CirQueue *Q)
{
	if(QueueEmpty(Q))
		Error("Queue if empty.");
	return Q->data[Q->front];
}

void InitQueue(CirQueue *Q)
{
	Q->front=Q->rear=0;
    Q->count=0;     //计数器置0
}

int QueueEmpty(CirQueue *Q)
{
	return Q->count==0;  //队列无元素为空
}

int QueueFull(CirQueue *Q)
{
	return Q->count==QueueSize;  //队中元素个数等于QueueSize时队满
}

void Error(char* message)
{
	cout<<message<<endl;
}

void EnQueue(CirQueue *Q,DataType x)
{
	if(QueueFull(Q))                   
		Error("Queue overflow");     //队满上溢
	Q->count++;                        //队列元素个数加1
	Q->data[Q->rear]=x;                 //新元素插入队尾
	Q->rear=(Q->rear+1)%QueueSize;      //循环意义下将尾指针加1
}

DataType DeQueue(CirQueue *Q)
{
	DataType temp;
    if(QueueEmpty(Q))
		Error("Queue underflow");     //队空下溢
	temp=Q->data[Q->front];
    Q->count--;                        //队列元素个数减1
    Q->front=(Q->front+1)%QueueSize;   //循环意义下的头指针加1
    return temp; 
}

void CreateGraphic(ALGraph *G,int dim,int* data)
{
	EdgeNode *edgenode;
	for(int i=0;i<dim;i++)
	{
		G->adjlist[i].firstedge=NULL;
		G->adjlist[i].vertex=i;
		for(int j=0;j<dim;j++)
		{
			if(data[dim*i+j]==1)
			{
				edgenode=new EdgeNode;
				edgenode->adjvex=j;
				edgenode->next=G->adjlist[i].firstedge;
				G->adjlist[i].firstedge=edgenode;
			}
		}
	}
}

void CreateGraphic(ALGraph *G)
{
	cout<<"请输入图的结点数"<<endl;
	cin>>G->n;
	cout<<"请输入图的边数"<<endl;
	cin>>G->e;
	EdgeNode *edgenode;
	for(int k=0;k<G->n;k++)
	{
		G->adjlist[k].firstedge=NULL;
		G->adjlist[k].vertex=k;
	}
	for(int k=0;k<G->e;k++)
	{
		int i,j;
		cout<<"请输入边(vi,vj)的结点号"<<endl;
		cin>>i>>j;
		edgenode=new EdgeNode;
		edgenode->adjvex=j;
		edgenode->next=G->adjlist[i].firstedge;
		G->adjlist[i].firstedge=edgenode;
		edgenode=new EdgeNode;
		edgenode->adjvex=i;
		edgenode->next=G->adjlist[j].firstedge;
		G->adjlist[j].firstedge=edgenode;
	}
}

void PrintGraphic(ALGraph *G)
{
	EdgeNode *p;
	cout<<"现在开始打印图："<<endl;
	for(int i=0;i<G->n;i++)
	{
		p=G->adjlist[i].firstedge;
        while(p)
		{
			cout<<p->adjvex<<",";
			p=p->next; //找vi的下一邻接点
		}
		cout<<endl;
	}
}

void BFSTraverse(ALGraph *G)
{ 
	int i;
	for(i=0;i<G->n;i++)
		visited[i]=FALSE;
	for(i=0;i<G->n;i++)
	{
		if(!visited[i])
		{
			BFS(G,i);
		}
	}
}

void CreateGraphic(ALGraph *G,int* data,int dim)
{
	for(int i=0;i<dim;i++)
	{
		G->adjlist[i].firstedge=NULL;
		for(int j=i+1;j<dim;j++)
		{
			if(data[i*dim+j]!=0)
			{
				EdgeNode *edgeNode=new EdgeNode;
				edgeNode->adjvex=j;
				edgeNode->next=G->adjlist[i].firstedge;
				G->adjlist[i].firstedge=edgeNode;
			}
		}
	}
}

void BFS(ALGraph*G,int k)
{
	cout<<"现在访问结点："<<k<<endl;
	visited[k]=TRUE;
	CirQueue *q=new CirQueue;
	InitQueue(q);
	EdgeNode *node=G->adjlist[k].firstedge;
	while(node!=NULL&&!visited[node->adjvex])
	{
		cout<<"现在访问结点："<<node->adjvex<<endl;
		EnQueue(q,node->adjvex);
		/*cout<<"现在队列中元素："<<endl;
		for(int i=q->front;i<q->rear;i++)
			cout<<q->data[i]<<",";
		cout<<endl;*/
		visited[node->adjvex]=TRUE;
		node=node->next;
	}
	if(!QueueEmpty(q))
	{
		k=DeQueue(q);
		if(!visited[k])
		{
			BFS(G,k);
		}
	}
	else
	{
		return;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	Graphic Create;
	Create.n=4;
	int data[4][4]={{0,1,1,1},{1,0,1,1},{1,1,0,0},{1,1,0,0}};
	CreateGraphic(&Create,*data,4);
	BFSTraverse(&Create);
	return 0;
}

