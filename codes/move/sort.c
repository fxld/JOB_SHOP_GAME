#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define ISLAND 2
#define MAXnum 1000
typedef struct chromosome
{
	int makespan;
}GENE;

int cmp(const void *a, const void *b)
{
	return (*(GENE*)a).makespan - (*(GENE*)b).makespan;
}

int main(void)
{
	GENE m[ISLAND][MAXnum];
	int i, j;
	srand((unsigned int)time(0));
	for (i=0;i<ISLAND;i++)
		for (j = 0; j < MAXnum; j++)
			m[i][j].makespan = rand();
	for (i=0;i<ISLAND;i++)
		qsort(m[i], MAXnum, sizeof(GENE), *cmp);
	for (i = 0; i < ISLAND; i++)
		for (j = 0; j < MAXnum; j++)
			printf("%d\t%d\n", i, m[i][j]);
	system("pause");
	return 0;
}