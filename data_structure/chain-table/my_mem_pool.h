#ifndef _MY_MEM_POOL_H_
#define _MY_MEM_POOL_H_

#define pool_size 1000

int mem_pool_free_all_space(void);
void *my_alloc(int size);
int my_free(void *pointer);

#endif