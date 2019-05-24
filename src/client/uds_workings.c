#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<errno.h>

#include"mem_mgr.h"

int sock_create(char *addr)
{
	int sock;
	if((sock=socket(AF_UNIX, SOCK_STREAM, 0))<0){
		fprintf(stderr, "[-]Error in creating socket: %s\n",
			strerror(errno));
		goto exit;
	}

	struct sockaddr_un addr_sun;
	explicit_bzero(&addr_sun, SUN_LEN(&addr_sun));
	addr_sun.sun_family=AF_UNIX;
	strncpy(addr_sun.sun_path, addr, strlen(addr));

	if(connect(sock, (struct sockaddr *)&addr_sun, SUN_LEN(&addr_sun))<0){
		fprintf(stderr, "[-]Error in connecting to %s: %s\n",
			addr, strerror(errno));
		sock=-1;
	}
exit:
	return sock;
}

void uds_workings(char *addr, char *m_list)
{
	//TODO server handler loop
}

int wrt(int sock, char *cmds, char *reason)
{
	int ret=0;
	if(write(sock, cmds, sizeof(char)*512)<0){
		fprintf(stderr, "[-]Error in writing %s for %s: %s\n",
			cmds, reason, strerror(errno));
		ret=1;
	}

	dealloc("char", 512, cmds);
	return ret;
}

int rd(int sock, char *cmdr, char *reason)
{
	int stat=read(sock, cmdr, sizeof(char)*512);
	int flag=0;

	if(stat==0){
		fprintf(stderr, "[-]Read empty buffer...\n");
		flag=1;
	}
	else if(stat<0){
		fprintf(stderr, "[-]Error in reading for %s: %s\n",
			reason, strerror(errno));
		flag=1;
	}

	return stat;
}
