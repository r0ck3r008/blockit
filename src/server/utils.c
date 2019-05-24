#define NEED_ARGS

#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>

#include"utils.h"
#include"mem_mgr.h"

int init_args(struct arg *arguments, int argc, char **argv)
{
	add_argument(arguments, "-u", "--uds_path",
		"The UDS path for server", 1);

	if(argc!=2){
		show_help(arguments);
		clean(arguments);
		return 1;
	}

	parse_args(arguments, argc, argv);
	return 0;
}

char *find_arg(struct arg *arguments, char *s_name)
{
	char *ret=NULL;
	struct arg *curr=arguments;
	for(curr; curr->nxt!=NULL || !strcmp(curr->s_name, s_name);
		curr=curr->nxt){
		ret=curr->value;
	}

	return ret;
}

void wrt(int sock, char *cmds, char *reason)
{
	if(write(sock, cmds, 512)<0){
		fprintf(stderr, "[-]Error in writing %s for %s: %s\n",
			cmds, reason, strerror(errno));
	}

	dealloc("char", 512, cmds);
}

int rd(int sock, char *cmdr, char *reason)
{
	int stat=read(sock, cmdr, 512);

	if(stat<0){
		fprintf(stderr, "[-]Error in reading for %s: %s\n",
			reason, strerror(errno));
		dealloc("char", 512, cmdr);
		cmdr=NULL;
	}
	else if(stat==0){
		fprintf(stderr, "[-]Read an empty buffer...\n");
	}

	return stat;
}
