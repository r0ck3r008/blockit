#define NEED_ARGS

#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>

#include"utils.h"
#include"mem/mem_mgr.h"

void init_args(struct arg *arguments, int argc, char **argv)
{
	add_argument(arguments, "-u", "--uds_path",
		"uds_path" ,"The UDS path for server", 1);
	add_argument(arguments, "-i", "--interface",
		"iface" ,"The sniffing interface", 1);
	add_argument(arguments, "-e", "--expr",
		"expr" ,"The sniffing expression", 1);

	if(argc!=7){
		show_help(arguments);
		_exit(-1);
	}

	parse_args(arguments, argc, argv);
	arguments_glbl=arguments;
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
	int flag=0;

	if(stat<0){
		fprintf(stderr, "[-]Error in reading for %s: %s\n",
			reason, strerror(errno));
		flag=1;
	}
	else if(stat==0){
		fprintf(stderr, "[-]Read an empty buffer...\n");
		flag=1;
	}

	if(flag){
		dealloc("char", 512, cmdr);
		cmdr=NULL;
	}
	return stat;
}

FILE *openf(char *fname, int mode)
{
	if(mode){
		int stat=unlink(fname);
		if(stat!=0 && errno!=2){
			fprintf(stderr, "[-]Error in unlinking file: %s\n",
				strerror(errno));
			_exit(-1);
		}
	}

	char *mode_name= mode==1 ? "w" : "r";
	FILE *f=NULL;
	if((f=fopen(fname, mode_name))==NULL){
		fprintf(stderr, "[-]Error in opening file: %s\n",
			strerror(errno));
		_exit(-1);
	}

	return f;
}

char *fetch_url()
{
	FILE *f=openf("./mirror.conf", 0);
	if(f==NULL)
		_exit(-1);

	char *url=alloc("char", 500);
	fgets(url, 500*sizeof(char), f);

	fclose(f);
	return url;
}
