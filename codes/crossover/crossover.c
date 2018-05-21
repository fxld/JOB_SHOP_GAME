#include"define.h"

int* GetSubsets(void)//elements
{
	int i;
	int len = rand() % Element;
	int *temp = NULL;
	int *random = NULL;
	temp = (int *)malloc((len + 1) * sizeof(int));
	random = (int *)malloc(Element * sizeof(int));
	for (i = 0; i < len; i++)
		random[i] = i+1;
	for (i = len - 1; i >= 1; i--)
		swap(&random[i], &random[rand() % i]);
	for (i = 0; i < len; i++)
		temp[i] = random[i];
	temp[i] = -1;
	free(random);
	return &temp;
}

/*
int Get_Crossover_Range(void)
{
	return (int)(((double)RAND_MAX)*CROSS);
}
*/

int Num_Selected(int island,int start,int end,int val)
{
	if (start > end)
		return -1;

	int mid = start + (end - start) / 2;

	if (after_select[island][mid] > val)
		return Num_Selected(island, mid + 1, end, val);
	else if (after_select[island][mid] < val)
		return Num_Selected(island, start, mid - 1, val);
	else
		return mid;
}

int cmp(const void *a, const void *b)
{
	return *(int*)b - *(int*)a;//当元素1-元素2大于0时降序
}

void swap(int *a, int *b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

int * GetTempGene(void)//job
{
	int *temp = NULL;
	temp = (int *)calloc(0, Job * sizeof(int));
	return &temp;
}

void crossover(void)
{
	int i, j, k,l;
	int g1,g2;//gene1,gene2
	int map1, map2;
	int interval;
	int *subset = NULL;
	int *temp[2] = { NULL };
	int operation_num[ISLAND];
	int selected[ISLAND];

	for (i = 0; i < ISLAND; i++)
	{
		qsort(after_select[i], MAXnum, sizeof(int), *cmp);
		selected[i] = Num_Selected(i, 0, MAXnum - 1, 0)+1;
		operation_num[i] = selected[i] / 2;
	}
	//interval = Get_Crossover_Range();
	interval = CrossoverRange;
	srand((unsigned int)time(0));

	for (i = 0; i < ISLAND; i++)
		for (j = 0; j < operation_num[i]; j++)
			if (rand() <= interval)
			{
				map1 = rand() % selected[i];
				map2 = rand() % selected[i];
				while (map1 == map2)
					map2 = rand() % selected[i];
				g1 = after_select[i][map1];
				g2 = after_select[i][map2];

				subset = GetSubsets();
				temp[0] = GetTempGene();
				temp[1] = GetTempGene();

				for (k = 0; k < Job; k++)
					for (l = 0; subset[l] != -1; l++)
						if (island[i][g1].gene[k] == subset[l])
						{
							temp[0][k] = island[i][g1].gene[k];
							island[i][g1].gene[k] = 0;
							break;
						}
				for (k = 0; k < Job; k++)
					for (l = 0; subset[l] != -1; l++)
						if (island[i][g2].gene[k] == subset[l])
						{
							temp[1][k] = island[i][g2].gene[k];
							island[i][g2].gene[k] = 0;
							break;
						}

				for (k=0,l=0;k<Job;k++)
					if (island[i][g1].gene[k] != 0)
					{
						while (temp[0][l] != 0)
							l++;
						temp[1][l] = island[i][g1].gene[k];
					}
				for (k = 0, l = 0; k<Job; k++)
					if (island[i][g2].gene[k] != 0)
					{
						while (temp[0][l] != 0)
							l++;
						temp[0][l] = island[i][g2].gene[k];
					}

				memcpy(island[i][g1].gene, temp[0], Job * sizeof(int));
				memcpy(island[i][g2].gene, temp[1], Job * sizeof(int));

				after_select[i][map1] = -1;
				after_select[i][map2] = -1;
				swap(&after_select[i][map1], &after_select[i][selected[i]--]);
				swap(&after_select[i][map2], &after_select[i][selected[i]--]);

				for (i = 0; i < 2; i++)
					free(temp[i]);
				free(subset);
			}
}