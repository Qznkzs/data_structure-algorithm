#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "linear-table.h"

static void cleanup(int sig)
{
	list_exit();
	exit(0);
}

static void usage(p_sqlist L)
{
	int code = -1;
	int index = -1;
	int data = 0;
	printf("1-insert,2-add,3-renew,4-del,5-query,6-displayall\n");
	printf("entry op_code:\n");
	scanf("%d", &code);
	switch(code)
	{
		case 1:
			printf("entry index & data(0 255):\n");
			scanf("%d %d", &index, &data);
			list_insert(L, index, data);
			list_displayall(L);
			break;
		case 2:
			printf("entry data(255):\n");
			scanf("%d", &data);
			list_append(L, data);
			list_displayall(L);
			break;
		case 3:
			printf("entry index & data(0 255):\n");
			scanf("%d %d", &index, &data);
			list_renew(L, index, data);
			list_displayall(L);
			break;
		case 4:
			printf("entry index(255):\n");
			scanf("%d", &index);
			list_del(L, index);
			list_displayall(L);
			break;
		case 5:
			printf("entry index(255):\n");
			scanf("%d", &index);
			list_query(L, index, &data);
			printf("data:%d\n", data);
			break;
		case 6:
			list_displayall(L);
			break;
		default:
			break;
	}
}

int main(int argc, char *argv[])
{
	p_sqlist L = NULL;
	list_init();

	signal(SIGINT, cleanup);   // Ctrl + C
    signal(SIGTERM, cleanup);  // kill 命令等

	L = list_get();
	while(1)
	{
		usage(L);
	}
	return 0;
}

