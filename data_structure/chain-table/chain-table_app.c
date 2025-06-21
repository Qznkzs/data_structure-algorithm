#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include "my_mem_pool.h"
#include "chain-table.h"

#define TABLE_POOL_SIZE 100

struct LIST_HEAD_NODE *chain_table_pool[100] = {0};

static struct LIST_HEAD_NODE *find_list_by_name(char *list_name)
{
    int i = 0;
    if (NULL == list_name || '\0' == list_name[0])
    {
        return NULL;
    }
    for (i = 0; i < TABLE_POOL_SIZE; i++)
    {
        if (NULL == chain_table_pool[i])
        {
            continue;
        }
        if (0 == strncmp(chain_table_pool[i]->list_name, list_name, LISTNAME_LEN))
        {
            return chain_table_pool[i];
        }
    }
    return NULL;
}

static int insert_list_to_pool(struct LIST_HEAD_NODE *list)
{
    int i;
    if (NULL == list)
    {
        return -1;
    }
    for (i = 0; i < TABLE_POOL_SIZE; i++)
    {
        if (NULL == chain_table_pool[i])
        {
            chain_table_pool[i] = list;
            return 0;
        }
    }
    return -1;
}

static int del_list_from_pool(struct LIST_HEAD_NODE *list)
{
    int i;
    if (NULL == list)
    {
        return -1;
    }
    for (i = 0; i < TABLE_POOL_SIZE; i++)
    {
        if (list == chain_table_pool[i])
        {
            chain_table_pool[i] = 0;
            return 0;
        }
    }
    return -1;
}

static void show_all_list_from_pool()
{
    int i = 0;
    for (i = 0; i < TABLE_POOL_SIZE; i++)
    {
        if (NULL != chain_table_pool[i])
        {
            list_display(chain_table_pool[i]);
        }
    }
    return ;
}

void signal_handler(int sign)
{
    mem_pool_free_all_space();
    exit(0);
}

void usage()
{
    printf("===============================\n");
    printf("= 1. create / destory a List  =\n");
    printf("= 2. add / del a node to List =\n");
    printf("= 3. show List                =\n");
    printf("= 4. reverse the List         =\n");
    printf("= 5. adj max List             =\n");
    printf("= 6. show all LIST            =\n");
    printf("= 7. example                  =\n");
    printf("===============================\n");
}

void example()
{
    printf("==================================================================================\n");
    printf("= 1 1 listname(create a List) [code][create][listname]                           =\n");
    printf("= 1 2 listname(destory a List) [code][destory][listname]                         =\n");
    printf("= 2 1 -1 listname 10000 (add by head) [code][add][by head][listname][data]       =\n");
    printf("= 2 1 -2 listname 10000 (add by tail) [code][add][by tail][listname][data]       =\n");
    printf("= 2 1 0 listname 10000 (add by pos) [code][add][pos][listname]                   =\n");
    printf("= 2 2 -1 listname (del by head) [code][del][by head][listname]                   =\n");
    printf("= 2 2 -2 listname (del by tail) [code][del][by tail][listname]                   =\n");
    printf("= 2 2 0 listname (del by pos) [code][del][pos][listname]                         =\n");
    printf("= 3 listname (show the List) [code][listname]                                    =\n");
    printf("= 4 listname (reverse the List) [code][listname]                                 =\n");
    printf("= 5 listname (adj max List) [code][listname]                                     =\n");
    printf("= 6 (show all  List) [code]                                                      =\n");
    printf("==================================================================================\n");
}

void process()
{
    char buf[512] = {0};
    int code = 0, op = 0, hand = 0, data = 0;
    char list_name[LISTNAME_LEN] = {0};
    struct LIST_HEAD_NODE *list = NULL;
    int errcode = 0;
    usage();
    printf("enter: ");
    fgets(buf, sizeof(buf), stdin);
    printf("\n");
    printf("buf:%s\n", buf);
    switch (buf[0])
    {   
        case '1':
            sscanf(buf, "%d %d %s", &code, &op, list_name);
            if ('\0' == list_name[0])
            {
                return ;
            }
            if (1 == op)
            {
                list = find_list_by_name(list_name);
                if (NULL != list)
                {
                    printf("list %s is already!\n");
                    return ;
                }
                list = list_create(list_name);
                if (NULL == list)
                {
                    printf("create list fail for malloc error!\n");
                    return ;
                }
                errcode = insert_list_to_pool(list);
                if (0 != errcode)
                {
                    list_free(list);
                    printf("insert_list_to_pool fail!\n");
                    return ;
                }
            }
            else if (2 == op)
            {
                list = find_list_by_name(list_name);
                del_list_from_pool(list);
                list_free(list);
            }
            break;
        case '2':
            sscanf(buf, "%d %d %d %s %d", &code, &op, &hand, list_name, &data);
            if ('\0' == list_name[0])
            {
                return ;
            }

            list = find_list_by_name(list_name);
            if (NULL == list)
            {
                printf("no list named %s!\n", list_name);
                return ;
            }

            if (1 == op)    // 增加节点
            {
                p_sllnode node;
                node = node_create(data);
                if (NULL == node)
                {
                    printf("create node fail for malloc!\n");
                    return ;
                }
                switch (hand)
                {
                    case -1:
                        errcode = list_head_insert(list, node);
                        break;
                    case -2:
                        errcode = list_tail_insert(list, node);
                        break;
                    default:
                        errcode = list_index_insert(list, hand, node);
                        break;
                }
                if (0 != errcode)
                {
                    node_free(node);
                    printf("node add to %s fail!\n", list_name);
                    return ;
                }
            }
            else if (2 == op)  // 删除节点
            {
                switch (hand)
                {
                    case -1:
                        errcode = list_head_del(list);
                        break;
                    case -2:
                        errcode = list_tail_del(list);
                        break;
                    default:
                        errcode = list_index_del(list, hand);
                        if (-2 == errcode)
                        {
                            printf("pos is invalid!\n");
                        }
                        break;
                }
                if (0 != errcode)
                {
                    return ;
                }
            }
            break;
        case '3':
        case '4':
        case '5':
            sscanf(buf, "%d %s", &code, list_name);
            if ('\0' == list_name[0])
            {
                return ;
            }
            list = find_list_by_name(list_name);
            if (NULL == list)
            {
                printf("no list named %s!\n", list_name);
                return ;
            }
            if (3 == code)
            {
                list_display(list);
            }
            else if (4 == code)
            {
                list_reverse_shallow(list);
                list_display(list);
            }
            else if (5 == code)
            {
                int value = 0;
                p_sllnode p;
                p = list_adj_max(list, &value);
                if(NULL != p)
                {
                    printf("p->data:%d\n", p->data);
                }
            }
            break;
        case '6':
            show_all_list_from_pool();
            break;
        case '7':
            example();
            break;
    }
    if ('6' != buf[0] && '7' != buf[0])
    {
        printf("ok!\n");
    }
    return ;
}

int main(int argc, char *argv[])
{
    signal(SIGINT, signal_handler);
    while (1)
    {
        process();
    }
}


