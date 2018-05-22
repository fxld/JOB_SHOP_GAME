#include"define.h"


int choose(void)	//返回值:1代表文件输入，2代表键盘输入
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

DATA ** memory_allocator(int col, int row)
{
	DATA **temp = NULL;
	temp = (DATA**)malloc(row * sizeof(DATA*));
	if (temp != NULL)
		for (int i = 0; i < row; i++)
			temp[i] = (DATA *)malloc(col * sizeof(DATA));
	return temp;
}

void input(void)
{
	int ElementId;
	int order;
	char buffer = '\0';

	if (choose() == 1)
	{
		if (freopen("input.txt", "r", stdin) == NULL)
		{
			printf("目录下不存在合法的输入文件，程序将退出。\n");
			system("pause");
			exit(EXIT_FAILURE);
		}
	}

	scanf("%d%d", &Element, &Machine);
	data = memory_allocator(Machine, Element);

	ElementId = 0;
	while (ElementId != -1)
	{
		order = 0;
		scanf("%d", &ElementId);
		while (getchar(buffer) != '\n')
		{
			scanf("(%d,%d)", &data[ElementId - 1][order].time, &data[ElementId - 1][order].line);
			order++;
		}
	}
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
1 (7,1) (3,2) (15,3)
2 (10,2) (17,1)
3 (7,1) (22,2)
-1
*/