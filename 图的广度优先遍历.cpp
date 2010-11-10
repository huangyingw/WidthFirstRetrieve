// ͼ�Ĺ�����ȱ���.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<iostream>
using namespace std;
#define MaxVertexNum 100
typedef int VertexType;

typedef enum{FALSE,TRUE}Boolean;//FALSEΪ0��TRUEΪ1

Boolean visited[MaxVertexNum]; //���ʱ�־������ȫ����

#define QueueSize 100   //Ӧ���ݾ�����������ֵ

//typedef char Queue DataType;  //DataType�����������ھ����Ӧ��
//#define DataType int

typedef int Queue, DataType;  //DataType�����������ھ����Ӧ��
typedef struct Sturet
{               
	int front;  //ͷָ�룬�ӷǿ�ʱָ���ͷԪ��            
    int rear;  //βָ�룬�ӷǿ�ʱָ���βԪ�ص���һλ��             
	int count;  //����������¼����Ԫ������
    DataType data[QueueSize];
}CirQueue;

typedef struct node
{	
	int adjvex; 
	struct node *next;
	//��Ҫ��ʾ���ϵ�Ȩ����Ӧ����һ��������
}EdgeNode;

typedef struct vnode
{
	//�������
	VertexType vertex; //������
	EdgeNode *firstedge;//�߱�ͷָ��
}VertexNode;

typedef VertexNode AdjList[MaxVertexNum];//AdjList���ڽӱ�����

typedef struct ALGraph
{
	AdjList adjlist;//�ڽӱ�
	int n; //ͼ�е�ǰ������
	int e;//ͼ�е�ǰ���� 
}Graphic; //���ڼ򵥵�Ӧ�ã����붨������ͣ���ֱ��ʹ��AdjList���͡� 

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
    Q->count=0;     //��������0
}

int QueueEmpty(CirQueue *Q)
{
	return Q->count==0;  //������Ԫ��Ϊ��
}

int QueueFull(CirQueue *Q)
{
	return Q->count==QueueSize;  //����Ԫ�ظ�������QueueSizeʱ����
}

void Error(char* message)
{
	cout<<message<<endl;
}

void EnQueue(CirQueue *Q,DataType x)
{
	if(QueueFull(Q))                   
		Error("Queue overflow");     //��������
	Q->count++;                        //����Ԫ�ظ�����1
	Q->data[Q->rear]=x;                 //��Ԫ�ز����β
	Q->rear=(Q->rear+1)%QueueSize;      //ѭ�������½�βָ���1
}

DataType DeQueue(CirQueue *Q)
{
	DataType temp;
    if(QueueEmpty(Q))
		Error("Queue underflow");     //�ӿ�����
	temp=Q->data[Q->front];
    Q->count--;                        //����Ԫ�ظ�����1
    Q->front=(Q->front+1)%QueueSize;   //ѭ�������µ�ͷָ���1
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
	cout<<"������ͼ�Ľ����"<<endl;
	cin>>G->n;
	cout<<"������ͼ�ı���"<<endl;
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
		cout<<"�������(vi,vj)�Ľ���"<<endl;
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
	cout<<"���ڿ�ʼ��ӡͼ��"<<endl;
	for(int i=0;i<G->n;i++)
	{
		p=G->adjlist[i].firstedge;
        while(p)
		{
			cout<<p->adjvex<<",";
			p=p->next; //��vi����һ�ڽӵ�
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
	cout<<"���ڷ��ʽ�㣺"<<k<<endl;
	visited[k]=TRUE;
	CirQueue *q=new CirQueue;
	InitQueue(q);
	EdgeNode *node=G->adjlist[k].firstedge;
	while(node!=NULL&&!visited[node->adjvex])
	{
		cout<<"���ڷ��ʽ�㣺"<<node->adjvex<<endl;
		EnQueue(q,node->adjvex);
		/*cout<<"���ڶ�����Ԫ�أ�"<<endl;
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

