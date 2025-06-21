#ifndef _LINEARTABLE_H_
#define _LINEARTABLE_H_

#define MAX_NUM 100

typedef int data_t;

typedef struct{
	data_t data[MAX_NUM];
	int last_index;
}sqlist, *p_sqlist;
// 还可以取名为sqlist，p_sqlist

int list_init(void);	// 系统唯一实例
p_sqlist list_get(void);
int list_exit(void);

int list_clear(p_sqlist L);
int list_length(p_sqlist L);
int list_insert(p_sqlist L, int index, data_t data);
int list_del(p_sqlist L, int index);
int list_renew(p_sqlist L, int index, data_t data);
int list_query(p_sqlist L, int index, data_t *data);
int list_append(p_sqlist L, data_t data);
int list_displayall(p_sqlist L);

#endif