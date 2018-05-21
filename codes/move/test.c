#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define SIZE 2000

struct test 
{
	int id;
	float num;
};
struct test a[SIZE];

int cmp(const void *a, const void *b)
{
	return ((*(struct test *)a).num - (*(struct test*)b).num);
}

/*
void elapsed_time(void)
{
	printf("Elapsed time:%u secs.\n", clock() / CLOCKS_PER_SEC);
}
*/


int main(void)
{
	int i;
	clock_t start, finish;
	double duration;
	start = clock();
	srand((unsigned int)time(0));
	//printf("BEFORE SORT\n");
	for (i = 0; i < SIZE; i++)
	{
		(a + i)->id = i;
		(a + i)->num = (float)rand();
		//printf("%d\t%.2f\n", (a + i)->id, (a + i)->num);
	}
	qsort(a, SIZE, sizeof(struct test), *cmp);
	//printf("AFTER SORT\n");
	//for (i = 0; i < SIZE; i++)
	//	printf("%d\t%.2f\n", (a + i)->id, (a + i)->num);
	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("%lf secs\n", duration);
	//elapsed_time();
	//system("pause");
	return 0;
}