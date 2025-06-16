#include <stdio.h>
#include <stdlib.h>

p_sllnode node_create(data_t data)
{
	p_sllnode node;
	node = (p_sllnode)malloc(sizeof(sllnode));
	if (NULL == node)
	{
		return NULL;
	}
	node->data = data;
	node->next = NULL;
	return node;
}

int node_free(p_sllnode del_node)
{
	if (NULL == del_node)
	{
		return -1;
	}
	free(del_node);
	return 0;
}

//创建一个链表(创建头节点)
struct LIST_HEAD_NODE* list_create(void)
{
	struct LIST_HEAD_NODE* H;
	p_sllnode p;
	H = (struct LIST_HEAD_NODE*)malloc(sizeof(struct LIST_HEAD_NODE));
	if (NULL == H)
	{
		return NULL;
	}
	p = node_create(0);
	if (NULL == p)
	{
		return NULL;
	}
	H->head_node = p;
	H->list_len = 0;
	return H;
}

// 销毁一个链表
int list_free(struct LIST_HEAD_NODE* H)
{
	p_sllnode p = NULL;
	if (NULL == H)
	{
		return -1;
	}
	
	p = H->head_node;
	while (NULL != p)
	{
		p = H;
		H = H->next;
		free(p);
	}
	free(H);
	return 0;
}

// 头插法
int list_head_insert(struct LIST_HEAD_NODE* H, p_sllnode new_node)
{
	p_sllnode p = NULL;
	if (NULL == H)
	{
		return -1;
	}
	if (NULL == new_node)
	{
		return -2;
	}
	p = H->head_node;
	node->next = p->next;
	p->next = node;
	return 0;
}

// 尾插法
int list_tail_insert(struct LIST_HEAD_NODE* H, p_sllnode new_node)
{
	p_sllnode p;
	if (NULL == H)
	{
		return -1;
	}
	if (NULL == new_node)
	{
		return -2;
	}
	p = H->head_node;
	while (NULL != p->next)
	{
		p = p->next;
	}
	p->next = new_node;
	return 0;
}