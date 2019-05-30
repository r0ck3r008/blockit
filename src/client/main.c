#define NEED_ARGS

#include<stdio.h>

#include"utils.h"

int main(int argc, char * argv[])
{
	struct arg *arguments=init_lib();
	init_args(arguments, argc, argv);

}
