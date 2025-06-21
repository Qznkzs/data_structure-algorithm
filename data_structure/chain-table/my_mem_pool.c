#include <stdio.h>
#include <stdlib.h>

#include "my_mem_pool.h"

void *g_my_mem_pool[pool_size] = {NULL};

int mem_pool_get_newspace_pos(void)
{
    int i;
    for (i = 0; i < pool_size; i++)
    {
        if (NULL == g_my_mem_pool[i])
        {
            return i;
        }
    }
    return -1;
}

int mem_pool_record_pointer(void *pointer)
{
    int pos;
    if (NULL == pointer)
    {
        return -1;
    }
    pos = mem_pool_get_newspace_pos();
    if (-1 == pos)
    {
        return -1;
    }
    g_my_mem_pool[pos] = pointer;
    return 0;
}

int mem_pool_del_pointer(void *pointer)
{
    int i;
    if (NULL == pointer)
    {
        return -1;
    }
    
    for (i = 0; i < pool_size; i++)
    {
        if (pointer == g_my_mem_pool[i])
        {
            g_my_mem_pool[i] = NULL;
            return 0;
        }
    }
    return -2;
}

int mem_pool_free_all_space(void)
{
    int i;
    for (i = 0; i < pool_size; i++)
    {
        if (NULL != g_my_mem_pool[i])
        {
            free(g_my_mem_pool[i]);
            g_my_mem_pool[i] = NULL;
        }
    }
}

void *my_malloc(int size)
{
    void *pointer = NULL;
    pointer = malloc(size);
    if (NULL == pointer)
    {
        return NULL;
    }
    if (0 != mem_pool_record_pointer(pointer))
    {
        free(pointer);
        return NULL;
    }
    return pointer;
}

int my_free(void *pointer)
{
    free(pointer);
    mem_pool_del_pointer(pointer);
    return 0;
}