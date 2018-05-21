#include"define.h"
void sort(int x,int y,GENE *island,GENE *temporary)//从x到y的并归排序，需申请一个临时数组
{
	if (y - x > 1)
	{
		int m = x + (y - x) / 2;
		int p = x, q = m, i = x;
		sort(x, m, island, temporary);
		sort(m, y, island, temporary);
		while (p < m || q < y)
		{
			if (q >= y || (p < m && island[p].makespan <= island[q].makespan))
			{
				temporary[i++] = island[p++];
			}
			else
			{
				temporary[i++] = island[q++];
			}
		}
		for (i = x; i < y; i++)
		{
			island[i] = temporary[i];
		}
	}
}

double test(void)//test
{
	int i, j;
	clock_t start, end;
	srand((unsigned int)time(0));
	for (i = 0; i < ISLAND; i++)
		for (j = 0; j < MAXnum; j++)
		{
			island[i][j].makespan = rand();
			island[i][j].fitness = (double)j;
		}
	/*
	for (i = 0; i < ISLAND; i++)
	for (j = 0; j < MAXnum; j++)
	printf("%d\t%.2lf\n", island[i][j].makespan, island[i][j].fitness);
	*/
	start = clock();
	for (i = 0; i < ISLAND; i++)
	{
		GENE *temporary = NULL;//临时空间
		temporary = (GENE*)malloc(MAXnum * sizeof(GENE));
		sort(0, MAXnum, island[i], temporary);//排序
		free(temporary);
	}
	end = clock();
	/*
	for (i = 0; i < ISLAND; i++)
	for (j = 0; j < MAXnum; j++)
	printf("%d\t%.2lf\n", island[i][j].makespan,island[i][j].fitness);
	*/
	//printf("%lf secs.\n", ((double)(end - start)) / CLOCKS_PER_SEC);
	return ((double)(end - start)) / CLOCKS_PER_SEC;
}

int main(void)
{
	double sum=0.0;
	for (int x=0;x<20;x++)
		for (int m = 0; m < MAXage; m++)
			sum+=test();
	printf("%lf secs", sum/20.0);
	return 0;
}
