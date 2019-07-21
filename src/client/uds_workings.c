#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<errno.h>

#include"mem_mgr.h"
#include"uds_workings.h"

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
	printf("[!]Connection successful to %s!\n", addr);
exit:
	return sock;
}

void uds_workings(char *addr)
{
	int uds_sock;
	if((uds_sock=sock_create(addr))<0){
		_exit(-1);
	}

	char *cmdr;
	printf("[!]Welcome to Blockit!\nPlease input... (? for help)\n");

	for(int flag=0; ;){
		cmdr=alloc("char", 128);
		printf("[>]");
		fgets(cmdr, sizeof(char)*512, stdin);

		if(strstr(cmdr, "update")!=NULL){
			if(wrt(uds_sock, cmdr, "Send update query to server")){
				flag=1;
				goto exit_loop;
			}
		}else if(strstr(cmdr, "exit")!=NULL){
			printf("[!]Exiting now!\n");
			if(!wrt(uds_sock, cmdr, "Send exit command")){
				flag=1;
				goto exit_loop;
			}
		}else if(strstr(cmdr, "?")!=NULL){
			printf("[!]Help\n1) update: update\n2) Exit: exit\n"
			       );
		}else{
			printf("[!]Invalid input... retry!\n");
		}

exit_loop:
		dealloc("char", 128, cmdr);
		if(flag){
			break;
		}
	}
}

int wrt(int sock, char *cmdr, char *reason)
{
	char *cmds=alloc("char", 512);
	sprintf(cmds, "%s", cmdr);

	int ret=0;
	if(write(sock, cmds, sizeof(char)*512)<0){
		fprintf(stderr, "[-]Error in writing %s for %s: %s\n",
			cmds, reason, strerror(errno));
		ret=1;
	}

	dealloc("char", 512, cmds);
	return ret;
}
