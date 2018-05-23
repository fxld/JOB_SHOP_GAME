#include"define.h"

/*
	使用的全局变量：Job,island[ISLAND][MAXnum],**data,Element,Machine
*/

GENE code(GENE inigen)//传入一个初始染色体，返回一个新的染色体
{
	int temp;
	int key;
	for (int i = Job - 1; i > 0; i--)
	{
		temp = inigen.gene[i];
		key = rand() % i;
		inigen.gene[i] = inigen.gene[key];
		inigen.gene[key] = temp;
	}
}

void InitGen()//生成初始种群
{
	int i, j, k = 0;
	GENE inigen;
	srand((unsigned int)time(NULL));
	for (i = 0; i < Element; i++)//按顺序直接生成第一条
	{
		for (j = 0; j < Machine && data[i][j].line != -1; j++)
		{
			inigen.gene[k++] = i;
		}
	}

	for (i = 0; i < ISLAND; i++)//生成整个岛屿
	{
		for (j = 0; j < MAXnum; j++)
		{
			island[i][j] = code(inigen);
			inigen = island[i][j];
		}
	}
}