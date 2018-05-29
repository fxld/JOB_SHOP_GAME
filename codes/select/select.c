#include"define.h"

static GENE ** Offspring_allocator(int size_of_element[])	//为子代申请内存空间 [island][size of island]
{
	GENE **temp = NULL;
	temp = (GENE **)malloc((ISLAND) * sizeof(GENE *));
	if (temp != NULL)
	{
		for (int i = 0; i < ISLAND; i++)
			temp[i] = (GENE*)malloc((size_of_element[i] + 1) * sizeof(GENE));
	}
	return temp;
}

static int ** tournament_allocator(void)	//为竞技场申请内存空间	tournament[ISLAND][size of tournament]
{
	int **temp = NULL;
	temp = (int **)malloc((ISLAND + 1) * sizeof(int *));
	if (temp != NULL)
	{
		for (int i = 0; i < ISLAND+1; i++)
			temp[i] = (int*)malloc((nelite_size + 1) * sizeof(int));
	}
	return temp;
}

void swap(int *a, int *b)	//交换数组元素
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void init_random_pair(GENE *initgen)	//随机染色体对的初始化 initgen.gene[Job]={0，0，1，1，...，Element-1，...}
{
	int i,j,k;
	k = 0;
	for (i = 0; i < Element; i++)
		for (j = 0; j < Machine && data[i][j].line != -1; j++)
			(*initgen).gene[k++] = i;
}

void tournament_generate(int **tournament)//生成竞技场，内容为对下标的映射
{
	int i, j, k;
	for (i = 0; i < ISLAND; i++)
		for (j = elite_size,k=0; k < nelite_size; j++,k++)
			tournament[i][k] = j;
	for (i = 0; i < ISLAND; i++)
		for (k = nelite_size - 1; k >= 1; k--)
			swap(&tournament[i][k], &tournament[i][rand() % k]);
}

void randomize(GENE * pair)	//随机化染色体对
{
	int i,k,temp;
	for (i = Job - 1; i >= 1; i--)
	{
		k = rand() % i;
		temp = (*pair).gene[i];
		(*pair).gene[i] = (*pair).gene[k];
		(*pair).gene[k] = temp;
	}
	//	swap(&(*pair).gene[i], &(*pair).gene[rand()%i]);
	//int temp = *a;
	//*a = *b;
	//*b = temp;
}

void select(GENE ***o1, GENE ***o2)//select(&offspring_eselect,&offspring_tselect,index_of_island)
{
	int i, j, k;
	int selected;	//记录选出的个体的数量
	int **tournament = NULL;	//竞技场 tournament[ISLAND][index of offsprings]
	static int o1_size[ISLAND], o2_size[ISLAND];	//o1与o2的种群规模
	static int first = 1;	//记录函数是否为初次运行
	//int TournamentRange = (int)(((double)RAND_MAX)*TRANGE)*(1.0 - 1.0 / (2.0 * (clock() / 750) + 6.0));
	//static int num_random_generate;

	if (first)	//首次运行时进行各项初始化
	{
		first = 0;
		//num_random_generate = MAXnum - elite_size - TSIZE * max_operate_num;
		for (i = 0; i < TSIZE; i++)
			init_random_pair(&(random_pair[i]));
		for (i = 0; i < ISLAND; i++)
		{
			o1_size[i] = elite_size;
			o2_size[i] = nelite_size;
		}

		*o1 = Offspring_allocator(o1_size);
		*o2 = Offspring_allocator(o2_size);
	}

	selected = 0;
	/*******ELITE SELECT BEGIN**************/

	for (i = 0; i < ISLAND; i++)
		for (j = 0; j < elite_size; j++)
			(*o1)[i][j] = island[i][j];

	/********ELITE SELECT END*****************/

	selected = elite_size;
	/********TOURNAMENT SELECT BEGIN**********/

	tournament = tournament_allocator();
	tournament_generate(tournament);

	for (i = 0; i < ISLAND; i++)
		for (j = 0; j < max_operate_num; j++)
		{
			//if (rand() <= TournamentRange)
			(*o2)[i][j] = island[i][tournament[i][2 * j]].makespan <= island[i][tournament[i][2 * j + 1]].makespan ? island[i][tournament[i][2 * j]] : island[i][tournament[i][2 * j + 1]];
			//else
			//	(*o2)[i][j] = island[i][tournament[i][2 * j]].makespan <= island[i][tournament[i][2 * j + 1]].makespan ? island[i][tournament[i][2 * j + 1]] : island[i][tournament[i][2 * j]];
		}

	for (i = 0; i < ISLAND; i++)
		for (j = max_operate_num; j < nelite_size; j++)
		{
			/*
			int find = 0;
			while (find++<10)
			{
				randomize(&random_pair[0]);
				decode(&random_pair[0]);
				if (random_pair[0].makespan <= (int)(island[0][0].makespan*1.1))
					break;
			}
			(*o2)[i][j] = random_pair[0];
			*/

			int min;
			int find = 0;
		here:		for (k = 0; k < TSIZE; k++)	//随机生成染色体，补充到种群中
		{
			randomize(&random_pair[k]);
			decode(&random_pair[k]);
		}
		//if (clock() / 1000.0 < 250)
		{
			min = random_pair[0].makespan <= random_pair[1].makespan ? random_pair[0].makespan : random_pair[1].makespan;
			find++;
			if (min > (int)(island[0][0].makespan*1.15) && find < 5)	//控制解的质量
				goto here;
		}
		//if (rand() <= TournamentRange)
		(*o2)[i][j] = random_pair[0].makespan <= random_pair[1].makespan ? random_pair[0] : random_pair[1];
		//else
		//	(*o2)[i][j] = random_pair[0].makespan <= random_pair[1].makespan ? random_pair[1] : random_pair[0];

		}

	for (int i = 0; i < ISLAND + 1; i++)
		free(tournament[i]);
	free(tournament);
	tournament = NULL;
	/**********TOURNAMENT SELECT END******************/

}