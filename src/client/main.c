#define NEED_ARGS

#include<stdio.h>

#include"utils.h"

int main(int argc, char * argv[])
{
	struct arg *arguments=init_lib();
	if(init_args(arguments, argc, argv)){
		fprintf(stderr, "[-]Error in initializing the arguments\n");
		goto exit;
	}

exit:
	clean(arguments);
}
