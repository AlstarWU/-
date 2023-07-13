//采用深度优先搜索

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

/*
  用栈来存储结点，将初始点压入栈。
  取出栈顶元素，看是否是目标，若不是，如果当前栈顶元素的深度==4，不用将栈顶元素的子结点入栈，直接当栈顶元素出栈
  若栈顶元素的深度<4，将栈顶元素的子结点压入栈。直到找到目标状态
 */

#include<stdio.h>
#include<stdlib.h>
#define NUM 9
//结点的数据结构
typedef struct Node{
	int a[9];
	int deep;
	struct Node *before;
	struct Node *next;
}LinkNode;
//open表与close表的数据结构 栈
typedef struct Stack{
	LinkNode *top;
}StackTable;
//创建一个结点
LinkNode *CreateNode(int arr[]){
	LinkNode *node=(LinkNode *)malloc(sizeof(LinkNode));
	for(int i=0;i<NUM;i++)
		node->a[i]=arr[i];
	node->next=NULL;
	node->before=NULL;
	node->deep=1;
	
	return node;
}
//初始化栈
void Initial(StackTable *&s){
	s=(StackTable*)malloc(sizeof(StackTable));
	s->top=NULL;
}
//判断栈是否为空
bool is_Empty(StackTable *s){
	if(s->top==NULL)
		return true;
	return false;
}
//入栈
void EnStack(StackTable *&s,LinkNode *node){
	if(is_Empty(s)){
		s->top=node;
		s->top->next=NULL;
	}
	else{
		node->next=s->top;
		s->top=node;
	}
}
//出栈
void DeStack(StackTable *&s){
	//当当前栈不为空的时候，栈顶元素出栈
	if(is_Empty(s)==0)
		s->top=s->top->next;
}
//判断Open栈或者Close栈中是否出现了目标状态
bool is_Exist(StackTable *s,LinkNode *node){
	LinkNode *t=(LinkNode*)malloc(sizeof(LinkNode));
	t=s->top;
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
void ExtendTable(StackTable *&open,LinkNode *node,StackTable *&close){
	int arr[9]={0};
	int spacePosition=0;
	//记录空格的下标
	for(int i=0;i<9;i++)
		if(node->a[i]==0){
			spacePosition=i;
			break;
		}
	//open栈栈顶元素弹出，压入close栈
	DeStack(open);
	EnStack(close,node);
	//如果栈顶元素的深度<4，将栈顶元素的子结点压入栈
	if(node->deep<5){
		//可向上移动
		if(spacePosition-3>=0){
			for(int i=0;i<9;i++)
				arr[i]=node->a[i];
			LinkNode *unode;
			int t=arr[spacePosition];
			arr[spacePosition]=arr[spacePosition-3];
			arr[spacePosition-3]=t;
			unode=CreateNode(arr);
			unode->deep=node->deep+1;
			unode->before=node;
			
			//如果没有再Open表或者Close表中出现，就加入Open表
			if(is_Exist(open,unode)==0 && is_Exist(close,unode)==0){
				EnStack(open,unode);
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
			dnode->deep=node->deep+1;
			dnode->before=node;
			
			//如果没有再Open表或者Close表中出现，就加入Open表
			if(is_Exist(open,dnode)==0 && is_Exist(close,dnode)==0){
				EnStack(open,dnode);
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
			lnode->deep=node->deep+1;
			lnode->before=node;
			
			//如果没有再Open表或者Close表中出现，就加入Open表
			if(is_Exist(open,lnode)==0 && is_Exist(close,lnode)==0){
				EnStack(open,lnode);
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
			rnode->deep=node->deep+1;
			rnode->before=node;
			
			//如果没有再Open表或者Close表中出现，就加入Open表
			if(is_Exist(open,rnode)==0 && is_Exist(close,rnode)==0){
				EnStack(open,rnode);
			}
		}
	}
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
LinkNode* LookforNode(StackTable *s,LinkNode *node){
	while(s->top!=NULL){
		for(int i=0;i<9;i++)
			if(node->a[i]!=s->top->a[i])
				break;
		//找到当前结点，寻找解路径
		else if(i==8){
			return s->top;
		}
		s->top=s->top->next;
	}
	return NULL;
}
void Print(StackTable *q){
	LinkNode *t=(LinkNode *)malloc(sizeof(LinkNode));
	t=q->top;
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
	int temp[9]={};
	
	LinkNode *bnode,*gnode,*tnode;
	StackTable *Open,*Close;
	
	Initial(Open);
	Initial(Close);
	bnode=CreateNode(begin);
	gnode=CreateNode(goal);
	tnode=CreateNode(temp);
	
	//初始结点入栈
	EnStack(Open,bnode);
	if(ReverseNum(begin,9)%2 == ReverseNum(goal,9)%2){
		while(is_Empty(Open)==0){
			if(is_Exist(Open,gnode))
				break;
			//取出栈顶元素，栈顶元素的子结点入栈
			ExtendTable(Open,Open->top,Close);
		}
		printf("%d",is_Empty(Open)==0);
		//此时Open表已经出现了目标状态
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
	else{
		printf("当前问题无解！");
	}
	return 0;
}
