#include"define.h"

//使用的全局变量：Element,Machine,data

static int choose(void)	//返回值:1代表文件输入，2代表键盘输入
{
	int choice;

	printf("请输入选择：\n");
	printf("1.文件输入\n2.键盘输入\n");

	scanf("%d", &choice);
	while (choice != 1 && choice != 2)
	{
		printf("请输入有效的选择。\n");
		scanf("%d", &choice);
	}

	return choice;
}

static DATA ** memory_allocator(int col, int row)
{
	DATA **temp = NULL;
	temp = (DATA**)malloc((row+1) * sizeof(DATA*));
	if (temp != NULL)
		for (int i = 0; i < row+1; i++)
			temp[i] = (DATA *)malloc((col+1) * sizeof(DATA));
	return temp;
}

void input(void)
{
	int ElementId;
	int len,line;
	char buffer = '\0';
	int i;
	len = ElementId = line = 0;
	/***************input with file**********
	if (choose() == 1)
	{
		if (freopen("input.txt", "r", stdin) == NULL)
		{
			printf("目录下不存在合法的输入文件，程序将退出。\n");
			system("pause");
			exit(EXIT_FAILURE);
		}
	}
	*/
	scanf("%d%d", &Element, &Machine);
	data = memory_allocator(Machine, Element);

	/***************按任务书要求的输入********************
	while (ElementId != -1)
	{
		
		order = 0;
		scanf("%d", &ElementId);
		while (getchar(buffer) != '\n')
		{
			scanf("(%d,%d)", &data[ElementId][order].time, &data[ElementId][order].line);
			len++;
			order++;
		}
		if (order < Machine&&ElementId != -1)
			for (int i = order; i < Machine; i++)
			{
				data[ElementId][order].line = -1;
				data[ElementId][order].time = -1;
			}
		
	}
	*******/
	while (ElementId < Element)
	{
		for (i = 0; i < Machine; i++)
			scanf("%d %d", &data[ElementId][i].line, &data[ElementId][i].time);
		data[ElementId][i].line = -1;
		data[ElementId][i].time = -1;
		ElementId++;
	}
	//Job = len;
	Job = Element * Machine;
}

/**********************TEST*******************
int main(void)
{
	input();
	return 0;
}

/*
2
3 3
0 (7,0) (3,1) (15,2)
1 (10,1) (17,0)
2 (7,0) (22,1)
-1
*/