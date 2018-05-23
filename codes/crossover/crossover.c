#include"define.h"

//用到的全局变量有：Job，CrossoverRange

static int* GetSubsets(void)	//subset of Elements
{
	int i;
	int len = rand() % Element;	//确定该子集的基数
	int *temp = NULL;	//临时数组
	int *random = NULL;	//生成随机数列
	temp = (int *)malloc((len + 1) * sizeof(int));	//temp[]长度为len+1,temp[len]=-1表示到达数组尾部
	random = (int *)malloc(Element * sizeof(int));	//random[]长度为Element
	for (i = 0; i < len; i++)	//顺序填充random[]
		random[i] = i;
	for (i = len - 1; i >= 1; i--)	//随机交换random中两个元素的位置（可能重复），保证随机数列中的元素两两不同
		swap(&random[i], &random[rand() % i]);
	for (i = 0; i < len; i++)	//取random[]前len个作为子集的元素
		temp[i] = random[i];
	temp[i] = -1;	//标记结尾
	free(random);
	random=NULL;
	return temp;
}

static int Num_Selected(int island,int start,int end)	//计算选择操作后被选出的基因数
{
	int mid = start + (end - start) / 2;
	
	int i=after_select[island][mid]>=0?MAXnum-1:mid;
	for (;i>=0;i--)
		if (i>=0)
			break;
		
	if (i<0)
		return 0;
	else 
		return i+1;
}

static int cmp(const void *a, const void *b)	//用于qsort的比较函数
{
	return *(int*)b - *(int*)a;	//当元素1-元素2大于0时降序
}

void swap(int *a, int *b)	//交换两个元素（int []）
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

static int * GetTempGene(void)	//为子代基因申请临时存放空间
{
	int *temp = NULL;
	temp = (int *)calloc(-1, Job * sizeof(int));	//长度为Job
	return &temp;
}

void crossover(int group)
{
	int i, j, k, l;
	int g1,g2;	//gene1,gene2
	int map1, map2;
	int interval;	//意义同CrossoverRange
	int *subset = NULL;
	int *temp[2] = { NULL };
	int operation_num;//获取种群的最大交叉操作数量
	int selected;//存放种群的中被选择出的数量

	qsort(after_select[group], MAXnum, sizeof(int), *cmp);
	selected = Num_Selected(group, 0, MAXnum - 1);
	operation_num = selected / 2;
	interval = CrossoverRange;
		
	for (j = 0; j < operation_num; j++)
		if (rand() <= interval)
			{
				map1 = rand() % selected;	//或许可以改成生成不重复随机数列后再选择？
				map2 = rand() % selected;
				while (map1 == map2)
					map2 = rand() % selected;
				g1 = after_select[group][map1];
				g2 = after_select[group][map2];

				subset = GetSubsets();
				temp[0] = GetTempGene();
				temp[1] = GetTempGene();

				for (k = 0; k < Job; k++)	//将亲本中属于subset的元素传给对应下一代
					for (l = 0; subset[l] != -1; l++)
						if (island[group][g1].gene[k] == subset[l])
						{
							temp[0][k] = island[group][g1].gene[k];
							island[group][g1].gene[k] = -1;
							break;
						}
				for (k = 0; k < Job; k++)
					for (l = 0; subset[l] != -1; l++)
						if (island[group][g2].gene[k] == subset[l])
						{
							temp[1][k] = island[group][g2].gene[k];
							island[group][g2].gene[k] = -1;
							break;
						}

				for (k=0,l=0;k<Job;k++)	//将亲本中不属于subset的元素依次插入子代的基因中
					if (island[group][g1].gene[k] != -1)
					{
						while (temp[0][l] != -1)
							l++;
						temp[1][l] = island[group][g1].gene[k];
					}
				for (k = 0, l = 0; k<Job; k++)
					if (island[group][g2].gene[k] != 0)
					{
						while (temp[0][l] != 0)
							l++;
						temp[0][l] = island[group][g2].gene[k];
					}

				memcpy(island[group][g1].gene, temp[0], Job * sizeof(int));	//覆盖
				memcpy(island[group][g2].gene, temp[1], Job * sizeof(int));

				after_select[group][map1] = -1;	//将进行过交叉的染色体排除在已选择的染色体外
				after_select[group][map2] = -1;
				swap(&after_select[group][map1], &after_select[group][selected--]);
				swap(&after_select[group][map2], &after_select[group][selected--]);

				for (i = 0; i < 2; i++)
				{
					free(temp[i]);
					temp[i]=NULL;
				}
				free(subset);
				subset=NULL;
			}
}