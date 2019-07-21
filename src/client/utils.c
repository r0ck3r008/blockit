#define NEED_ARGS

#include<stdio.h>
#include<string.h>
#include<unistd.h>

#include"utils.h"

void init_args(struct arg *arguments, int argc, char **argv)
{
	add_argument(arguments, "-u", "--uds_sock", "uds_sock",
			"The URI of uds socket", 1);

	if(argc!=3){
		show_help(arguments);
		_exit(-1);
	}

	parse_args(arguments, argc, argv);

}
