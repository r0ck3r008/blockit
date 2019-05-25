#define NEED_ARGS

#include<stdio.h>
#include<string.h>

#include"utils.h"

int init_args(struct arg *arguments, int argc, char **argv)
{
	add_argument(arguments, "-s", "--sock_uds", "The URI of uds socket",
			1);

	if(argc!=3){
		fprintf(stderr, "[!]Insufficient args\n");
		show_help(arguments);
	}

	parse_args(arguments, argc, argv);

	return 0;
}

char *find_arg(struct arg *arguments, char *s_name)
{
	struct arg *curr=arguments;
	int flag;

	for(flag=0; ;){
		if(!strcmp(curr->s_name, s_name)){
			flag=1;
			break;
		}
		curr=curr->nxt;
	}

	if(flag){
		return curr->value;
	}else{
		return NULL;
	}
}
