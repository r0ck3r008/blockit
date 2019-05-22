#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<unistd.h>
#include<pthread.h>
#include<errno.h>

#include"uds_workings.h"
#include"utils.h"
#include"mem_mgr.h"
#include"transfer_utils.h"

int sock_create(char *addr)
{
	int sock=-1;
	if((sock=socket(AF_UNIX, SOCK_STREAM, 0))<0){
		fprintf(stderr, "[-]Error in creating UDS socket: %s\n",
			strerror(errno));
		goto exit;
	}

	if(unlink(addr)<0 && errno!=2){
		fprintf(stderr, "[-]Error in unlinking the address: %s\n",
			strerror(errno));
		goto exit;
	}

	struct sockaddr_un addr_un;
	explicit_bzero(&addr, SUN_LEN(&addr_un));
	addr_un.sun_family=AF_UNIX;
	strcpy(addr_un.sun_path, addr);

	if(bind(sock, (struct sockaddr *)&addr_un, SUN_LEN(&addr_un))<0){
		fprintf(stderr, "[-]Error in binding the UDS server sock: %s\n",
			strerror(errno));
	}

exit:
	return sock;
}

void *uds_workings(void *a)
{
	if(a==NULL){
		fprintf(stderr, "[-]Error in receving the UDS name\n");
		pthread_exit(NULL);
	}

	char *addr=a;
	int uds_sock=sock_create(addr);

	//server loop
	pthread_t tid[10];
	for(int i=0; ;){
		int sock=0, stat;
		if((sock=accept(uds_sock, NULL, NULL))<0){
			fprintf(stderr, "[-]Error in accepting client %d: %s\n",
				i, strerror(errno));
			continue;
		}

		if((stat=pthread_create(&tid[i], NULL, uds_cli_run, &sock))!=0){
			fprintf(stderr, "[-]Error in starting client %d: %s\n",
				i, strerror(errno));
			continue;
		}

		i++;
	}
}

void *uds_cli_run(void *a)
{
	int sock=*(int *)a;
	char *cmdr=NULL;

	//work_loop
	for(int exit_flag=0; ;){
		cmdr=alloc("char", 512);
		if(rd(sock, cmdr, "Read from client")<=0){
			goto loop_end;
		}

		if(strstr(cmdr, "update")!=NULL){
			char *cmd=strtok(cmdr, ":");
			char *url=strtok(NULL, ":");
			fetch(url);
		}
		else if(!strcmp(cmdr, "exit")){
			exit_flag=1;
		}

loop_end:
		dealloc("char", 512, cmdr);
		if(exit_flag){
			break;
		}
	}

	close(sock);
	pthread_exit(NULL);
}
