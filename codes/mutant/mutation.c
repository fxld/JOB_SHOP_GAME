#include"define.h"

static void swap(int *a, int *b)	//交换两个元素（int []）
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void generate_mutant_map(int *map,int group)	//生成变异操作的映射表 map[index of offspring]
{
	int i,j;
	for (i = 0, j = 1; i < nelite_size; i++)
		if (crossovered[group][i] == 0)
			map[j++] = i;
	map[0] = j;
	//for (i = j - 2; i >= 1; i--)
	//	swap(&(*map)[i], &(*map)[(rand() % i) + 1]);
}

void mutant(GENE *o2, int group)
{
	int interval;	//发生变异的区间	rand()<interval时变异
	int mutant_map[MAXnum + 1];	//变异操作的映射表 map[index of offspring]
	int pos1, pos2;	//变异基因上的不同位置chromosome.gene[position]
	int temp;	//用于交换pos1,pos2上的元素
	int map_len;//映射表的长度
	int present;//正在变异的染色体的下标

	generate_mutant_map(mutant_map, group);

	//qsort_after_select();
	pos1 = pos2 = temp = 0;
	map_len = mutant_map[0];
	interval = MutantRange;

	for (int i = 1; i < map_len; i++)
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


