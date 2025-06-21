#ifndef _CHAIN_TABLE_H_
#define _CHAIN_TABLE_H_

typedef int data_t;

#define LISTNAME_LEN 64

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
    char list_name[LISTNAME_LEN];
    int list_len;
}list_head_node, p_list_head_node;

p_sllnode node_create(data_t data);
int node_free(p_sllnode del_node);

struct LIST_HEAD_NODE *list_create(char *list_name);
int list_free(struct LIST_HEAD_NODE *H);

p_sllnode list_search_node(struct LIST_HEAD_NODE *H, int index);

int list_head_insert(struct LIST_HEAD_NODE *H, p_sllnode new_node);
int list_tail_insert(struct LIST_HEAD_NODE *H, p_sllnode new_node);
int list_index_insert(struct LIST_HEAD_NODE *H, int index, p_sllnode new_node);
int list_head_del(struct LIST_HEAD_NODE *H);
int list_tail_del(struct LIST_HEAD_NODE *H);
int list_display(struct LIST_HEAD_NODE *H);
int list_index_del(struct LIST_HEAD_NODE *H, int index);

int list_reverse_shallow(struct LIST_HEAD_NODE *H);
p_sllnode list_adj_max(struct LIST_HEAD_NODE *H, data_t *value);
struct LIST_HEAD_NODE *list_merge(struct LIST_HEAD_NODE* H1, struct LIST_HEAD_NODE* H2);

#endif