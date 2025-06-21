#include <stdio.h>
#include <stdlib.h>

#include "chain-table.h"
#include "my_mem_pool.h"

p_sllnode node_create(data_t data)
{
    p_sllnode node;
    node = (p_sllnode)my_malloc(sizeof(sllnode));
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
    my_free(del_node);
    return 0;
}

//创建一个链表(创建头节点)
struct LIST_HEAD_NODE *list_create(char *list_name)
{
    struct LIST_HEAD_NODE *H;
    p_sllnode p;
    H = (struct LIST_HEAD_NODE*)my_malloc(sizeof(struct LIST_HEAD_NODE));
    if (NULL == H)
    {
        return NULL;
    }
    p = node_create(0);
    if (NULL == p)
    {
        my_free(H);
        return NULL;
    }
    H->head_node = p;
    H->list_len = 0;
    snprintf(H->list_name, LISTNAME_LEN, list_name);
    return H;
}

// 销毁一个链表
int list_free(struct LIST_HEAD_NODE *H)
{
    p_sllnode p = NULL;
    p_sllnode q = NULL;
    if (NULL == H)
    {
        return -1;
    }
    p = H->head_node;
    while (NULL != p)
    {
        q = p;
        p = p->next;
        my_free(q);
    }
    my_free(H);
    return 0;
}

// 头插法
int list_head_insert(struct LIST_HEAD_NODE *H, p_sllnode new_node)
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
    new_node->next = p->next;
    p->next = new_node;
    H->list_len++;
    return 0;
}

// 尾插法
int list_tail_insert(struct LIST_HEAD_NODE *H, p_sllnode new_node)
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
    H->list_len++;
    return 0;
}

// 按序号查找
p_sllnode list_search_node(struct LIST_HEAD_NODE *H, int index)
{
    p_sllnode p;
    int i = -1;
    if (NULL == H)
    {
        return NULL;
    }
    p = H->head_node;
    while (NULL != p)
    {
        if (index == i)
        {
            return p;
        }
        p = p->next;
        i++;
    }
    return NULL;
}

// 任意位置插入
int list_index_insert(struct LIST_HEAD_NODE *H, int index, p_sllnode new_node)
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
    if (NULL == (p = list_search_node(H, index - 1)))
    {
        printf("index error\n");
        return -3;
    }
    new_node->next = p->next;
    p->next = new_node;
    H->list_len++;
    return 0;
}

// 头删法
int list_head_del(struct LIST_HEAD_NODE *H)
{
    p_sllnode p;
    if (NULL == H)
    {
        return -1;
    }
    p = H->head_node->next;
    if (NULL == p)
    {
        return -2;
    }
    H->head_node->next = p->next;
    my_free(p);
    H->list_len--;
    return 0;
}

// 尾删法
int list_tail_del(struct LIST_HEAD_NODE *H)
{
    p_sllnode p;
    if (NULL == H)
    {
        return -1;
    }
    p = H->head_node->next;
    if (NULL == p)
    {
        return -2;
    }
    p = H->head_node;
    while (NULL != p->next->next)
    {
        p = p->next;
    }
    my_free(p->next);
    H->list_len--;
    p->next = NULL;
}

int list_display(struct LIST_HEAD_NODE *H)
{
    p_sllnode p;
    
    if (NULL == H)
    {
        return -1;
    }
    printf("{LIST-%s:%d}", H->list_name, H->list_len);
    p = H->head_node->next;
    while (p)
    {
        printf("-[%d]", p->data);
        p = p->next;
    }
    printf("\n");
    return 0;
}

// 任意位置删除
int list_index_del(struct LIST_HEAD_NODE *H, int index)
{
    p_sllnode p;
    p_sllnode q;
    if (NULL == H)
    {
        return -1;
    }
    p = list_search_node(H, index - 1);
    if (NULL == p)
    {
        return -2; // index error
    }
    q = p->next;
    if (NULL == q)
    {
        return -3; // index error
    }
    p->next = q->next;
    my_free(q);
    H->list_len--;
    return 0;
}

// 链表浅倒置
int list_reverse_shallow(struct LIST_HEAD_NODE *H)
{
    p_sllnode p;
    p_sllnode q;
    if (NULL == H)
    {
        return NULL;
    }
    if (NULL == H->head_node->next || NULL == H->head_node->next->next)
    {
        return H;
    }
    p = H->head_node->next;
    H->head_node->next = NULL;
    while (NULL != p)
    {
        q = p;
        p = p->next;
        q->next = H->head_node->next;
        H->head_node->next = q;
    }
}

// 链表求两个相连结点最大值
p_sllnode list_adj_max(struct LIST_HEAD_NODE *H, data_t *value)
{
    p_sllnode p;
    p_sllnode q;
    p_sllnode r;
    if (NULL == H)
    {
        return NULL;
    }
    if (NULL == H->head_node->next || NULL == H->head_node->next->next)
    {
        return NULL;
    }
    if (NULL == H->head_node->next->next->next)
    {
        return H->head_node->next;
    }
    p = H->head_node->next;
    q = H->head_node->next->next;
    r = p;
    int sum = p->data + q->data;
    while (NULL != q->next)
    {
        p = p->next;
        q = q->next;
        if (sum < (p->data + q->data))
        {
            sum = p->data + q->data;
            r = p;
        }
    }
    *value = sum;
    return r;
}

// 有序链表的合并
struct LIST_HEAD_NODE *list_merge(struct LIST_HEAD_NODE* H1, struct LIST_HEAD_NODE* H2)
{
    p_sllnode p = NULL, q = NULL, r = NULL;
    struct LIST_HEAD_NODE *H3;
    if (NULL == H1 || NULL == H2)
    {
        return NULL;
    }
    if (NULL == (H3 = list_create("")))
    {
        return NULL;
    }
    
    p = H1->head_node->next;
    q = H2->head_node->next;
    r = H3->head_node;
    while (p && q)
    {
        if (p->data <= q->data)
        {
            r->next = p;
            p = p->next;
            r = r->next;
            r->next = NULL;
        }
        else
        {
            r->next = q;
            q = q->next;
            r = r->next;
            r->next = NULL;
        }
    }
    if (NULL == p)
    {
        r->next = q;
    }
    else if (NULL == q)
    {
        r->next = p;
    }
    
    r = H3->head_node->next;
    while (NULL != r)
    {
        H3->list_len++;
        r = r->next;
    }
    return H3;
}