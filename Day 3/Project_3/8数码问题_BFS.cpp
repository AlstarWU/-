//采用广度优先搜索

//开始状态
/*
  [2,8,3,
  1,0,4,
  7,6,5]
  X=15
 */

//目标状态
/*
  [1,2,3,
  8,0,4,
  7,6,5]
  X=11
 */

//初始状态的逆序数与目标状态的逆序数都是奇数，八数码问题有解

#include<stdio.h>
#include<stdlib.h>
//结点数据结构
typedef struct Node{
	int a[9];           //当前的状态
	struct Node *next;  //队列中指向下一个结点的指针
	struct Node *before;//指向父结点的指针
}LinkNode;

//Open表与Close表的数据结构
typedef struct Queue{
	//两个结点结构的指针指向我们的结点
	LinkNode *front;
	LinkNode *rear;
}QueueTable;
//创建结点
LinkNode* CreateNode(int arr[]){
	LinkNode *node;
	node=(LinkNode*)malloc(sizeof(LinkNode));
	for(int i=0;i<9;i++)
		node->a[i]=arr[i];
	node->next=NULL;
	node->before=NULL;
	
	return node;
}
//初始化队列
void Initial(QueueTable *&q){
	q=(QueueTable *)malloc(sizeof(QueueTable));
	q->front=NULL;
	q->rear=NULL;
	
}
//判断队列是否为空
int is_Empty(QueueTable *q){
	if(q->front==NULL)
		return 1;
	else
		return 0;
}
//入队操作,尾进头出
void EnQueue(QueueTable *&q,int arr[]){
	LinkNode *t;
	t=CreateNode(arr);
	if(is_Empty(q)){
		q->front=t;
		q->rear=t;
		q->rear->next=NULL;
	}
	else{
		q->rear->next=t;
		q->rear=t;
		q->rear->next=NULL;
	}
}
//出队列操作
void DeQueue(QueueTable *&q){
	if(q->front!=NULL)
		q->front=q->front->next;
}
//判断队列中是否出现目标状态或者判断是否已经出现了状态，有就返回真
bool Equal(QueueTable *q,LinkNode*node){
	LinkNode *t=(LinkNode *)malloc(sizeof(LinkNode));
	t=q->front;
	while(t!=NULL){
		for(int i=0;i<9;i++){
			if(node->a[i]!=t->a[i])
				break;
			else if(i==8)
				return true;
		}
		t=t->next;
	}
	return false;
}
//扩展结点，加入Open表
void ExtendTable(QueueTable *&open,LinkNode *node,QueueTable *&close){
	//注意连接父结点
	//对于当前结点node，进行扩展，子结点加入Open表，当前结点进入Close表
	int arr[9]={0};
	int spacePosition=0;
	//记录空格的下标
	for(int i=0;i<9;i++)
		if(node->a[i]==0){
			spacePosition=i;
			break;
		}
	//可向上移动
	if(spacePosition-3>=0){
		for(int i=0;i<9;i++)
			arr[i]=node->a[i];
		
		LinkNode *unode;
		int t=arr[spacePosition];
		arr[spacePosition]=arr[spacePosition-3];
		arr[spacePosition-3]=t;
		unode=CreateNode(arr);
		
		//如果没有再Open表或者Close表中出现，就加入Open表
		if(Equal(open,unode)==0 && Equal(close,unode)==0){
			EnQueue(open,unode->a);
			open->rear->before=node;
		}
	}
	//可向下移动
	if(spacePosition+3<=8){
		for(int i=0;i<9;i++)
			arr[i]=node->a[i];
		
		LinkNode *dnode;
		int t=arr[spacePosition];
		arr[spacePosition]=arr[spacePosition+3];
		arr[spacePosition+3]=t;
		dnode=CreateNode(arr);
		
		//如果没有再Open表或者Close表中出现，就加入Open表
		if(Equal(open,dnode)==0 && Equal(close,dnode)==0){
			EnQueue(open,dnode->a);
			open->rear->before=node;
		}
	}
	//可向左移动
	if(spacePosition%3!=0){
		for(int i=0;i<9;i++)
			arr[i]=node->a[i];
		
		LinkNode *lnode;
		int t=arr[spacePosition];
		arr[spacePosition]=arr[spacePosition-1];
		arr[spacePosition-1]=t;
		lnode=CreateNode(arr);
		
		//如果没有再Open表或者Close表中出现，就加入Open表
		if(Equal(open,lnode)==0 && Equal(close,lnode)==0){
			EnQueue(open,lnode->a);
			open->rear->before=node;
		}
	}
	//可向右移动
	if( (spacePosition+1)%3!=0){
		for(int i=0;i<9;i++)
			arr[i]=node->a[i];
		
		LinkNode *rnode;
		int t=arr[spacePosition];
		arr[spacePosition]=arr[spacePosition+1];
		arr[spacePosition+1]=t;
		rnode=CreateNode(arr);
		
		//如果没有再Open表或者Close表中出现，就加入Open表
		if(Equal(open,rnode)==0 && Equal(close,rnode)==0){
			EnQueue(open,rnode->a);
			open->rear->before=node;
		}
	}
	
	//将当前结点从open表出队，进入close表入队
	EnQueue(close,open->front->a);
	DeQueue(open);
}
//得出是否有解
int ReverseNum(int a[],int size){
	int Count=0;
	
	for(int i=1;i<size;i++){
		for(int j=0;j<i;j++)
			if (a[j]>a[i])
				Count++;
	}
	return Count;
}
//找出出现的结点,求出解路径
LinkNode* LookforNode(QueueTable *q,LinkNode *node){
	while(q->front!=NULL){
		for(int i=0;i<9;i++)
			if(node->a[i]!=q->front->a[i])
				break;
		//找到当前结点，寻找解路径
		else if(i==8){
			return q->front;
		}
		q->front=q->front->next;
	}
	return NULL;
}
void Print(QueueTable *q){
	LinkNode *t=(LinkNode *)malloc(sizeof(LinkNode));
	t=q->front;
	while(t!=NULL){
		for(int i=0;i<9;i++){
			printf("%4d",t->a[i]);
			if(i==2 || i==5 || i==8)
				printf("\n");
		}
		printf("\n");
		t=t->next;
	}
}
void PrintData(LinkNode *node){
	if(node->before!=NULL)
		PrintData(node->before);
	for(int i=0;i<9;i++){
		printf("%4d",node->a[i]);
		if(i==2 || i==5 || i==8)
			printf("\n");
	}
	printf("\n");
}
int main(){
	int begin[9]={2,8,3,1,0,4,7,6,5};
	int goal[9]={1,2,3,8,0,4,7,6,5};
	int temp[9]={0};
	
	LinkNode *bnode,*gnode,*tnode;
	QueueTable *Open,*Close;
	
	Initial(Open);
	Initial(Close);
	bnode=CreateNode(begin);
	gnode=CreateNode(goal);
	tnode=CreateNode(temp);
	//开始点入队列
	EnQueue(Open,bnode->a);
	
	if(ReverseNum(begin,9)%2 == ReverseNum(goal,9)%2){
		//当Open表不为空
		while(is_Empty(Open)==0){
			if(Equal(Open,gnode))
				break;
			//扩展Open表
			ExtendTable(Open,Open->front,Close);
		}
		printf("Close表当前的数据：\n");
		Print(Close);
		printf("******************************************\n");
		printf("Open表当前的数据：\n");
		Print(Open);
		printf("*********************************\n");
		printf("解路径：\n");
		tnode=LookforNode(Open,gnode);
		PrintData(tnode);
	}
	else
		printf("当前问题无解！");
	return 0;
}
