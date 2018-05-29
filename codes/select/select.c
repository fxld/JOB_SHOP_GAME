#include"define.h"

static GENE ** Offspring_allocator(int size_of_element[])
{
	GENE **temp = NULL;
	temp = (GENE **)malloc((ISLAND + 1) * sizeof(GENE *));
	if (temp != NULL)
	{
		for (int i = 0; i < ISLAND+1; i++)
			temp[i] = (GENE*)malloc((size_of_element[i] + 1) * sizeof(GENE));
	}
	return temp;
}

static int ** tournament_allocator(void)
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

void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void init_random_pair(GENE *initgen)
{
	int i,j,k;
	k = 0;
	for (i = 0; i < Element; i++)
		for (j = 0; j < Machine && data[i][j].line != -1; j++)
			(*initgen).gene[k++] = i;
}

void tournament_generate(int **tournament)//tournament[ISLAND][nelite_size]
{
	int i, j, k;
	for (i = 0; i < ISLAND; i++)
		for (j = elite_size,k=0; k < nelite_size; j++,k++)
			tournament[i][k] = j;
	for (i = 0; i < ISLAND; i++)
		for (k = nelite_size - 1; k >= 1; k--)
			swap(&tournament[i][k], &tournament[i][rand() % k]);
}

void randomize(GENE * pair)
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

void select(GENE ***o1,GENE ***o2)//select(&offspring_eselect,&offspring_tselect,index_of_island)
{
	int i, j, k;
	int selected;
	int **tournament=NULL;
	static int o1_size[ISLAND],o2_size[ISLAND];
	static int first = 1;
	//static int num_random_generate;

	if (first)
	{
		first = 0;
		//num_random_generate = MAXnum - elite_size - TSIZE * max_operate_num;
		for (i=0;i<TSIZE;i++)
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
			(*o1)[i][j]=island[i][j];

	/********ELITE SELECT END*****************/

	selected = elite_size;
	/********TOURNAMENT SELECT BEGIN**********/

	tournament = tournament_allocator();
	tournament_generate(tournament);

	for (i=0;i<ISLAND;i++)
		for (j = 0; j < max_operate_num; j++)
		{
			//if (rand() <= TournamentRange)
				(*o2)[i][j] = island[i][tournament[i][2 * j]].makespan <= island[i][tournament[i][2 * j + 1]].makespan ? island[i][tournament[i][2 * j]] : island[i][tournament[i][2 * j + 1]];
			//else
			//	(*o2)[i][j] = island[i][tournament[i][2 * j]].makespan <= island[i][tournament[i][2 * j + 1]].makespan ? island[i][tournament[i][2 * j + 1]] : island[i][tournament[i][2 * j]];
		}

	for (i=0;i<ISLAND;i++)
		for (j=max_operate_num; j < nelite_size; j++)
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
	here:		for (k = 0; k < TSIZE; k++)
			{
				randomize(&random_pair[k]);
				decode(&random_pair[k]);
			}
			min= random_pair[0].makespan <= random_pair[1].makespan ? random_pair[0].makespan : random_pair[1].makespan;
			find++;
			if (min > (int)(island[0][0].makespan*1.15)&&find<5)
				goto here;
			//if (rand() <= TournamentRange)
				(*o2)[i][j] = random_pair[0].makespan <= random_pair[1].makespan ? random_pair[0] : random_pair[1];
			//else
			//	(*o2)[i][j] = random_pair[0].makespan <= random_pair[1].makespan ? random_pair[1] : random_pair[0];
			
		}

	free(tournament);
	/**********TOURNAMENT SELECT END******************/

}