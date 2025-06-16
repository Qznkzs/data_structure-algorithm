#ifndef _CHAIN_TABLE_H_
#define _CHAIN_TABLE_H_

typedef int data_t;

typedef struct SingleLinkedListNode
{
	data_t data;
	struct SingleLinkedListNode *next;
}sllnode, *p_sllnode;

typedef struct DualLinkedListNode
{
    data_t data;
    struct DualLinkedListNode *prev;
    struct DualLinkedListNode *next;
}dllnode, *p_dllnode;

typedef struct LIST_HEAD_NODE
{
    struct SingleLinkedListNode *head_node;
    int list_len;
}list_head_node, p_list_head_node;



#endif