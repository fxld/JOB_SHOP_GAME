#include"define.h"

//用到的全局变量有：Job，CrossoverRange

static void swap(int *a, int *b)	//交换两个元素（int []）
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

static int* GetSubsets(void)	//subset of Elements
{
	int i;
	int len = rand() % Element+1;	//确定该子集的基数
	int *temp = NULL;	//临时数组
	int *random = NULL;	//生成随机数列
	temp = (int *)malloc((len + 1) * sizeof(int));	//temp[]长度为len+1,temp[len]=-1表示到达数组尾部
	random = (int *)malloc((Element+1) * sizeof(int));	//random[]长度为Element
	if (random != NULL && temp != NULL)
	{
		for (i = 0; i < Element; i++)	//顺序填充random[]
			random[i] = i;
		for (i = Element-1; i >= 1; i--)	//随机交换random中两个元素的位置（可能重复），保证随机数列中的元素两两不同
			swap(&random[i], &random[rand() % i]);
		for (i = 0; i < len; i++)	//取random[]前len个作为子集的元素
			temp[i] = random[i];
		temp[i] = -1;	//标记结尾
		free(random);
		random = NULL;
		/*
		printf("the subset:");
		for (int i = 0; i < len; i++)
			printf("%d,", temp[i]);
		printf("\n");
		*/
		return temp;
	}
	
	else
		return NULL;
}

int *map_allocator(int len)	//为映射图申请内存并生成映射图
{
	int *temp = NULL;
	int i;
	temp = (int *)malloc((len + 1) * sizeof(int));
	if (temp != NULL)
	{
		for (i = 0; i < len; i++)
			temp[i] = i;
		for (i = len - 1; i >= 1; i--)
			swap(&temp[i], &temp[rand() % i]);			
	}
	return temp;
}
/*
static int cmp(const void *a, const void *b)	//用于qsort的比较函数
{
	return *(int*)b - *(int*)a;	//当元素1-元素2大于0时降序
}
*/
static int * GetTempGene(void)	//为子代基因申请临时存放空间
{
	int *temp = NULL;
	temp = (int *)malloc((Job + 1) *sizeof(int));	//长度为Job
	if (temp!=NULL)
		memset(temp, -1, (Job + 1) * sizeof(int));
	return temp;
}

void crossover(GENE *o2,int group)
{
	int i, j, k, l;
	int g1,g2;	//gene1,gene2
	int *map = NULL;//映射表(包含随机化的o2的下标)	map[index of offspring]
	int interval;	//意义同CrossoverRange
	int *subset = NULL;	//存放生成的工件的子集 subset[random length(less than Element)]
	int *temp[2] = { NULL };	//存放交叉获得的gene	temp[island][length of gene]
	int operation_num;//获取种群的最大交叉操作数量
	int selected;//存放种群的中被选择出的数量

	//qsort(after_select[group], MAXnum, sizeof(int), *cmp);
	memset(crossovered[group], 0, MAXnum*sizeof(int));
	selected = nelite_size;
	operation_num = selected / 2;
	interval = CrossoverRange;
	map = map_allocator(selected);

	for (j = 0; j < operation_num; j++)
		if (rand() <= interval)
		{
			g1 = map[2 * j];
			g2 = map[2 * j + 1];
			crossovered[group][g1] = 1;
			crossovered[group][g2] = 1;

			subset = GetSubsets();
			temp[0] = GetTempGene();
			temp[1] = GetTempGene();

			/*dbg
			for (int i = 0; i < 2; i++)
			{
				for (int j = 0; j < Job; j++)
					printf("%d ", temp[i][j]);
				printf("\n");
			}
			*/

			for (k = 0; k < Job; k++)	//将亲本中属于subset的元素传给对应下一代
				for (l = 0; subset[l] != -1; l++)
					if (o2[g1].gene[k] == subset[l])
					{
						temp[0][k] = o2[g1].gene[k];
						o2[g1].gene[k] = -1;
						break;
					}
			for (k = 0; k < Job; k++)
				for (l = 0; subset[l] != -1; l++)
					if (o2[g2].gene[k] == subset[l])
					{
						temp[1][k] = o2[g2].gene[k];
						o2[g2].gene[k] = -1;
						break;
					}

			/*dbg
			for (int i = 0; i < 2; i++)
			{
			for (int j = 0; j < Job; j++)
			printf("%d ", temp[i][j]);
			printf("\n");
			}
			*/

			for (k = 0, l = 0; k < Job; k++)	//将亲本中不属于subset的元素依次插入子代的基因中
				if (o2[g1].gene[k] != -1)
				{
					while (temp[1][l] != -1)
						l++;
					temp[1][l] = o2[g1].gene[k];
					/*dbg
					for (int i = 0; i < 2; i++)
					{
					for (int j = 0; j < Job; j++)
					printf("%d ", temp[i][j]);
					printf("\n");
					}
					*/
				}
			for (k = 0, l = 0; k < Job; k++)
				if (o2[g2].gene[k] != -1)
				{
					while (temp[0][l] != -1)
						l++;
					temp[0][l] = o2[g2].gene[k];
				}

			/*dbg
			for (int i = 0; i < 2; i++)
			{
			for (int j = 0; j < Job; j++)
			printf("%d ", temp[i][j]);
			printf("\n");
			}
			*/


			memcpy(o2[g1].gene, temp[0], Job * sizeof(int));	//覆盖
			memcpy(o2[g2].gene, temp[1], Job * sizeof(int));

			for (i = 0; i < 2; i++)
			{
				free(temp[i]);
				temp[i] = NULL;
			}
			free(subset);
			subset = NULL;
		}
	free(map);
}