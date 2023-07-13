#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define OK 1
#define ERROR 0
#define MAX_SIZE 100

typedef int Status;

typedef struct {
	int nums[9];       // 存储棋盘状态
	int id;            // 节点ID
	int operation;     // 操作符
	int parentId;      // 父节点ID
	int level;         // 节点层级
} ElemType;

int cmpArray(int a[], int b[], int n)
{
	for (int i = 0; i < n; i++)
	{
		if (a[i] != b[i])
			return false;
	}
	
	return true;
}

bool isSolvable(int nums[])
{
	int inversions = 0;
	for (int i = 0; i < 9; i++)
	{
		if (nums[i] == 0) continue;
		
		for (int j = 0; j < i; j++)
		{
			if (nums[j] > nums[i])
				inversions++;
		}
	}
	
	return inversions % 2 == 0;
}

void swap(int nums[], int i, int j)
{
	int temp = nums[i];
	nums[i] = nums[j];
	nums[j] = temp;
}

void BFS(int start[], int end[])
{
	ElemType openTable[MAX_SIZE];
	int openFront = 0;
	int openRear = 0;
	
	ElemType CloseTable[MAX_SIZE];
	int closeLen = 0;
	
	bool isSuccess = false;
	ElemType tmpElem;
	int count = 0;
	
	memcpy(tmpElem.nums, start, sizeof(tmpElem.nums));
	tmpElem.level = 1;
	tmpElem.parentId = -1;
	tmpElem.operation = -1;
	
	openTable[openRear] = tmpElem;
	openRear = (openRear + 1) % MAX_SIZE;
	
	while (openRear != openFront)
	{
		tmpElem = openTable[openFront];
		openFront = (openFront + 1) % MAX_SIZE;
		
		printf("[%d %d %d %d %d %d %d %d %d], %c, %d\n", tmpElem.nums[0], tmpElem.nums[1], tmpElem.nums[2], tmpElem.nums[3], tmpElem.nums[4], tmpElem.nums[5], tmpElem.nums[6], tmpElem.nums[7], tmpElem.nums[8], tmpElem.operation, tmpElem.level);
		
		if (cmpArray(tmpElem.nums, end, 9))
		{
			isSuccess = true;
			break;
		}
		
		ElemType childElem;
		int blankIndex;
		for (int i = 0; i < 9; i++)
		{
			if (tmpElem.nums[i] == 0)
			{
				blankIndex = i;
				break;
			}
		}
		
		int row = blankIndex / 3;
		int col = blankIndex % 3;
		
		// 将空格向上移动
		if (row > 0 && tmpElem.operation != 'd')
		{
			count++;
			memcpy(childElem.nums, tmpElem.nums, sizeof(tmpElem.nums));
			childElem.operation = 'u';
			swap(childElem.nums, blankIndex, blankIndex - 3);
			childElem.parentId = tmpElem.id;
			childElem.id = count;
			childElem.level = tmpElem.level + 1;
			openTable[openRear] = childElem;
			openRear = (openRear + 1) % MAX_SIZE;
		}
		
		// 将空格向下移动
		if (row < 2 && tmpElem.operation != 'u')
		{
			count++;
			memcpy(childElem.nums, tmpElem.nums, sizeof(tmpElem.nums));
			childElem.operation = 'd';
			swap(childElem.nums, blankIndex, blankIndex + 3);
			childElem.parentId = tmpElem.id;
			childElem.id = count;
			childElem.level = tmpElem.level + 1;
			openTable[openRear] = childElem;
			openRear = (openRear + 1) % MAX_SIZE;
		}
		
		// 将空格向左移动
		if (col > 0 && tmpElem.operation != 'r')
		{
			count++;
			memcpy(childElem.nums, tmpElem.nums, sizeof(tmpElem.nums));
			childElem.operation = 'l';
			swap(childElem.nums, blankIndex, blankIndex - 1);
			childElem.parentId = tmpElem.id;
			childElem.id = count;
			childElem.level = tmpElem.level + 1;
			openTable[openRear] = childElem;
			openRear = (openRear + 1) % MAX_SIZE;
		}
		
		// 将空格向右移动
		if (col < 2 && tmpElem.operation != 'l')
		{
			count++;
			memcpy(childElem.nums, tmpElem.nums, sizeof(tmpElem.nums));
			childElem.operation = 'r';
			swap(childElem.nums, blankIndex, blankIndex + 1);
			childElem.parentId = tmpElem.id;
			childElem.id = count;
			childElem.level = tmpElem.level + 1;
			openTable[openRear] = childElem;
			openRear = (openRear + 1) % MAX_SIZE;
		}
	}
	
	if (isSuccess)
	{
		printf("成功！\n");
		printf("步数：%d\n", tmpElem.level - 1);
		printf("路径：\n");
		
		ElemType path[MAX_SIZE];
		int pathLen = 0;
		while (tmpElem.parentId != -1)
		{
			path[pathLen] = tmpElem;
			pathLen++;
			tmpElem = openTable[tmpElem.parentId];
		}
		
		for (int i = pathLen - 1; i >= 0; i--)
		{
			printf("[%d %d %d %d %d %d %d %d %d], %c\n", path[i].nums[0], path[i].nums[1], path[i].nums[2], path[i].nums[3], path[i].nums[4], path[i].nums[5], path[i].nums[6], path[i].nums[7], path[i].nums[8], path[i].operation);
		}
	}
	else
	{
		printf("失败\n");
	}
}

int main()
{
	int start[9];
	int end[9];
	
	printf("请输入初始状态（以空格分隔，共9个数字）：\n");
	for (int i = 0; i < 9; i++)
	{
		scanf("%d", &start[i]);
	}
	
	printf("请输入目标状态（以空格分隔，共9个数字）：\n");
	for (int i = 0; i < 9; i++)
	{
		scanf("%d", &end[i]);
	}
	
	if (!isSolvable(start) || !isSolvable(end))
	{
		printf("该谜题无解。\n");
		return 0;
	}
	
	BFS(start, end);
	
	return 0;
}
