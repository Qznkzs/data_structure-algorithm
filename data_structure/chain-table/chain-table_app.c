#include <stdio.h>
#include <stdlib.h>

#include "chain-table.h"



void sign_handler(int sign)
{
	mem_pool_free_all_space();
	exit(0);
}

int main(int argc, char *argv[])
{
	
}