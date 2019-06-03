#define NEED_ARGS

#include<stdio.h>

#include"utils.h"
#include"uds_workings.h"

int main(int argc, char * argv[])
{
	struct arg *arguments=init_lib();
	init_args(arguments, argc, argv);

	uds_workings(find_arg_val(arguments, "uds_sock"));
}
