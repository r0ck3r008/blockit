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
	int sock;
	int close_flg=0;

	if((sock=socket(AF_UNIX, SOCK_STREAM, 0))<0){
		fprintf(stderr, "[-]Error in creating socket: %s\n",
			strerror(errno));
		goto exit;
	}

	int stat=unlink(addr);
	if(stat<0 && errno!=2){
		fprintf(stderr, "[-]Error in unlinking the address: %s\n",
			strerror(errno));
		close_flg=1;
		goto exit;
	}

	struct sockaddr_un addr_un;
	explicit_bzero(&addr_un, SUN_LEN(&addr_un));
	addr_un.sun_family=AF_UNIX;
	strncpy(addr_un.sun_path, addr, sizeof(addr_un.sun_path)-1);

	if(bind(sock, (struct sockaddr *)&addr_un, SUN_LEN(&addr_un))<0){
		fprintf(stderr, "[-]Error in binding to: %s\n",
			addr);
		close_flg=1;
		goto exit;
	}

	if(listen(sock, 5)<0){
		fprintf(stderr, "[-]Error in listening: %s\n",
			strerror(errno));
		close_flg=1;
	}
exit:
	if(close_flg){
		close(sock);
		sock=-1;
	}
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
	if(uds_sock==-1){
		goto exit;
	}

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
exit:
	pthread_exit(NULL);
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
