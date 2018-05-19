#include"define.h"

int Get_Range(void)//获取一个区间[0,n],n∈(0,RAND_MAX),并且n/RAND_MAX=突变概率
{
	return (int)(RAND_MAX*MUTATION);
}

int cmp(const void *a, const void *b)
{
	return *(int*)b - *(int*)a;//当元素1-元素2大于0时降序
}

void qsort_after_select(void)//对after_select降序排序，使after_select[i][j]=-1排在后面
{
	for (int i = 0; i < ISLAND; i++)
		qsort(after_select[i], MAXnum, sizeof(int), *cmp);
}

int mutant(void)//after_select[island][index of the selected]
{
	int interval;
	int pos1, pos2, temp;//position
	int i, j, k;

	qsort_after_select();
	j = after_select[i][0];
	pos1 = pos2 = temp = 0;
	interval = Get_Range();
	
	for (i=0;i<ISLAND;i++)
		for(k=0;j!=-1;j=after_select[i][++k])
			if (rand() <= interval)
			{
				pos1 = rand() % Job;
				while ((pos2==pos1)||(island[i][j].gene[pos1]==island[i][j].gene[pos2]))
					pos2 = rand() % Job;

				temp = island[i][j].gene[pos1];
				island[i][j].gene[pos1] = island[i][j].gene[pos2];
				island[i][j].gene[pos2] = temp;
				/***********FOR DEBUG***************
				*	循环外：
				*	int m=0;    
				*	for (int i=0;i<ISLAND;i++)	
				*		memset(mutanted[i],-1,sizeof(mutanted[i]));
				*	循环内（加在注释上一行）：
				*	mutanted[i][m++]=j;
				*/
			}
}


