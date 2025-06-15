#include <stdio.h>
#include <stdlib.h>
#include "linear-table.h"

static p_sqlist g_L;

// 创建一个空顺序表
static p_sqlist list_create(void)  // 如果app（整个系统）只需要维护一个数据结构的实例，则在这个文件中定义一个全局变量，create函数和free函数不对app开放。
{
	p_sqlist L = NULL;
	// malloc
	L = (p_sqlist)malloc(sizeof(sqlist));
	if (NULL == L)
	{
		return L;
	}
	// init
	memset(L, 0, sizeof(sqlist));
	L->last_index = -1;
	// return
	return L;
}

// 释放一个顺序表
static int list_free(p_sqlist L)  // 如果app（整个系统）只需要维护一个数据结构的实例，则在这个文件中定义一个全局变量，create函数和free函数不对app开放。
{
	if (NULL == L)
	{
		return -1;
	}
	free(L);
	L = NULL;
	return 0;
}

// 初始化线性表全局变量
int list_init(void)
{
	g_L = list_create();
	if (NULL == g_L)
	{
		printf("g_L malloc fail\n");
		return -1;
	}
	else
	{
		return 0;
	}
}

// 获取线性表全局变量
p_sqlist list_get(void)
{
	return g_L;
}

int list_exit(void)
{
	if (0 != list_free(g_L))
	{
		printf("g_L free already\n");
		return -1;
	}
	else
	{
		return 0;
	}
}

// 清空一个空顺序表
int list_clear(p_sqlist L)
{
	if (NULL == L)
	{
		return -1;
	}
	memset(L, 0, sizeof(sqlist));
	L->last_index = -1;
	return 0;
}

// 判断一个顺序表是否为空
static int list_empty(p_sqlist L)
{
	if (NULL == L)
	{
		return -1;
	}
	if (-1 == L->last_index)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

// 判断一个顺序表是否已满
static int list_full(p_sqlist L)
{
	if (NULL == L)
	{
		return -1;
	}
	if (MAX_NUM <= L->last_index + 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

// 返回顺序表长度
int list_length(p_sqlist L)
{
	if (NULL == L)
	{
		return -1;
	}
	return L->last_index + 1;
}

// 增
int list_insert(p_sqlist L, int index, data_t data)
{
	int i;
	if (NULL == L)
	{
		return -1;	// 没有列表对象
	}
	if (list_full(L))
	{
		return -2;	// 列表满了
	}
	if (index < 0 || index > L->last_index + 1)
	{
		return -3;  // 下标不合法
	}
	// 移动数据
	for (i = L->last_index; i >= index; i--)
	{
		L->data[i+1] = L->data[i];
	}
	
	// 插入数据
	L->data[index] = data;
	L->last_index++;
	return 0;
}

// 删
int list_del(p_sqlist L, int index)
{
	int i;
	if (NULL == L)
	{
		return -1;
	}
	if (list_empty(L))
	{
		return -2;
	}
	if (index < 0 || index > L->last_index)
	{
		return -3;
	}
	L->data[index] = 0;
	for (i=index+1; i <= L->last_index; i++)
	{
		L->data[i-1] = L->data[i];
	}
	L->last_index--;
	return 0;
}

// 改
int list_renew(p_sqlist L, int index, data_t data)
{
	if (NULL == L)
	{
		return -1;
	}
	if (list_empty(L))
	{
		return -2;
	}
	if (index < 0 || index > L->last_index)
	{
		return -3;
	}
	L->data[index] = data;
	return 0;
}

// 查
int list_query(p_sqlist L, int index, data_t *data)
{
	if (NULL == L)
	{
		return -1;
	}
	if (list_empty(L))
	{
		return -2;
	}
	if (index < 0 || index > L->last_index)
	{
		return -3;
	}
	*data = L->data[index];
	return 0;
}

// 增的特例，在尾部添加
int list_append(p_sqlist L, data_t data)
{
	if (NULL == L)
	{
		return -1;
	}
	return list_insert(L, L->last_index + 1, data);
}

// 显示所有
int list_displayall(p_sqlist L)
{
	int i;
	char buff[1024]={'\0'};
	int len = 0;
	int offset = 0;
	if (NULL == L)
	{
		return -1;
	}
	for (i=0; i<=L->last_index; i++)
	{
		len = snprintf(buff + offset, sizeof(buff) - offset, "|%d|-", L->data[i]);
		offset += len;
	}
	buff[strlen(buff)] = '\n';
	printf(buff);
	return 0;
}