#define NEED_ARGS

#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<unistd.h>
#include<curl/curl.h>
#include<errno.h>

#include"utils.h"
#include"uds_workings.h"

int main(int argc, char *argv[])
{
	//start parser lib
	struct arg *arguments=init_lib();
	init_args(arguments, argc, argv);

	//start uds server
	int stat;
	pthread_t uds_tid;
	if((stat=pthread_create(&uds_tid, NULL, uds_workings,
				find_arg_val(arguments, "uds_path")))!=0){
		fprintf(stderr, "\n[-]Error in creating UDS thread: %s\n",
			strerror(errno));
		goto exit;
	}

	//start curl
	if(curl_global_init(CURL_GLOBAL_ALL)!=0){
		fprintf(stderr, "[-]Error in initiating the libcurl,\
		exiting now...\n");
		_exit(-1);
	}

exit:
	//clean cargparse lib
	clean(arguments);
}
