#include"define.h"

static void swap(int *a, int *b)	//交换两个元素（int []）
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void generate_mutant_map(int *map,int group)
{
	int i,j;
	for (i = 0, j = 1; i < nelite_size; i++)
		if (crossovered[group][i] == 0)
			map[j++] = i;
	map[0] = j;
	//for (i = j - 2; i >= 1; i--)
	//	swap(&(*map)[i], &(*map)[(rand() % i) + 1]);
}

void mutant(GENE *o2, int group)//after_select[island][index of the selected]
{
	int interval;
	int mutant_map[MAXnum + 1];
	int pos1, pos2, temp;
	int map_len;
	int present;
	int i;

	generate_mutant_map(mutant_map, group);

	//qsort_after_select();
	pos1 = pos2 = temp = 0;
	map_len = mutant_map[0];
	interval = MutantRange;

	for (i = 1; i < map_len; i++)
	{
		if (rand() <= interval)
		{
			present = mutant_map[i];
			pos1 = rand() % Job;
			pos2 = rand() % Job;
			while ((pos2 == pos1) || o2[present].gene[pos1] == o2[present].gene[pos2])
				pos2 = rand() % Job;

			temp = o2[present].gene[pos1];
			o2[present].gene[pos1] = o2[present].gene[pos2];
			o2[present].gene[pos2] = temp;
		}
	}
	/*for (k=0;j<MAXnum&&j!=-1;j=after_select[i][++k])
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


