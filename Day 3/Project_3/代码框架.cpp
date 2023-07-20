#include<stdio.h>
#include<mem.h>

#define OK 1
#define ERROR 0
#define MAX_SIZE 100

typedef int Status;

typedef struct{
	int nums[3];
	int id;
	int operation;
	int parentId;
	int level;	
}ElemType;


int cmpArray(int a[], int b[], int n)
{
	int i;
	for(i=0;i<n;i++)
		if(a[i] != b[i])
			return false;
	
	return true;
}


void BFS(int start[3], int end[3])
{
	ElemType openTable[MAX_SIZE];
	int openFront = 0;
	int openRear = 0;
	
	ElemType CloseTable[MAX_SIZE];
	int closeLen=0;
	
	
	bool isSuccess = false;
	ElemType tmpElem;
	int count;
	
	for(int i=0;i<3;i++)
		tmpElem.nums[i] = start[i];
//	memcpy(tmpElem.nums, start, sizeof(start));
	printf("%d %d %d\n", tmpElem.nums[0],tmpElem.nums[1],tmpElem.nums[2]); 
	tmpElem.level = 1;
	tmpElem.parentId = -1;
	tmpElem.operation = -1;
	
	openTable[openRear] = tmpElem;
	openRear = (openRear + 1) % MAX_SIZE;
	
	while(openRear != openFront)
	{
		tmpElem = openTable[openFront];
		openFront = (openFront + 1)%MAX_SIZE;

		printf("[%d %d %d], %c,  %d\n", tmpElem.nums[0],
									tmpElem.nums[1]	,
									tmpElem.nums[2],
									tmpElem.operation,
									tmpElem.level );	
		
		if(cmpArray(tmpElem.nums, end, 3) && tmpElem.level == 4)
		{
			isSuccess = true;
			break;
		}
		else if(tmpElem.level >= 4)
		{
			break;
		}
		
		ElemType childElem;
		
		for(int i=0;i<3;i++)
		{
			if(tmpElem.operation != 'a'+i)
			{
				count++;	
				for(int i=0;i<3;i++)
					childElem.nums[i] = tmpElem.nums[i];
			
				childElem.operation = 'a' + i;
//				memcpy(childElem.nums, tmpElem.nums, sizeof(tmpElem.nums));
				childElem.nums[i] = (childElem.nums[i] + 1) % 2;
				childElem.parentId = tmpElem.id;
				childElem.id = count;
				childElem.level = tmpElem.level + 1;
				
				openTable[openRear] = childElem;
				
				openRear = (openRear + 1)%MAX_SIZE;
			}
		}
	}
	
	if(isSuccess)
	{
		
		printf("success!");
		
	}
	else
	{
		printf("failed");
	}
	
}


int main()
{
	int a[3]={0,1,0};
	int b[3]={1,1,1};
	int c[3] = {0,0,0};
	
	
	BFS(a,b);

	return 0;		
}
 
