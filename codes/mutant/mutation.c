#include"define.h"

void mutant(void)//after_select[island][index of the selected]
{
	int interval;
	int pos1, pos2, temp;//position
	int i, j, k;

	//qsort_after_select();
	pos1 = pos2 = temp = 0;
	interval = MutantRange;
	
	for (i=0;i<ISLAND;i++)
	{	j = after_select[i][0];//for(k=0;j!=-1;j=after_select[i][++k])
		for (k=0;j<MAXnum&&j!=-1;j=after_select[i][++k])
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
}


