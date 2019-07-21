#define NEED_ARGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<unistd.h>
#include<curl/curl.h>
#include<errno.h>

#include"utils.h"
#include"net/uds_workings.h"
#include"net/transfer_utils.h"
#include"mem/mem_mgr.h"

int main(int argc, char *argv[])
{
	arguments_glbl=alloc("struct arg *", 1);

	//start parser lib
	*arguments_glbl=init_lib();
	init_args(*arguments_glbl, argc, argv);

	//start curl
	if(curl_global_init(CURL_GLOBAL_ALL)!=0){
		fprintf(stderr, "[-]Error in initiating the libcurl,\
		exiting now...\n");
		_exit(-1);
	}

	//init sniffer proc
	char *url=fetch_url();
	fetch(url);

	sleep(1);
	//start uds server
	int stat;
	pthread_t uds_tid;
	if((stat=pthread_create(&uds_tid, NULL, uds_workings,
				NULL))!=0){
		fprintf(stderr, "\n[-]Error in creating UDS thread: %s\n",
			strerror(stat));
		goto exit;
	}

	if((stat=pthread_join(uds_tid, NULL))!=0){
		fprintf(stderr, "[-]Error in joining to uds thread: %s\n",
			strerror(stat));
	}
exit:
	//clean cargparse lib
	clean(*arguments_glbl);
}
