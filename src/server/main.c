#define NEED_ARGS

#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<unistd.h>
#include<errno.h>

#include"utils.h"
#include"uds_workings.h"

int main(int argc, char *argv[])
{
	//start parser lib
	struct arg *arguments=init_lib();
	if(init_args(arguments, argc, argv)){
		_exit(-1);
	}

	int stat;
	pthread_t uds_tid;
	if((stat=pthread_create(&uds_tid, NULL, uds_workings,
				find_arg(arguments, "-u")))!=0){
		fprintf(stderr, "\n[-]Error in creating UDS thread: %s\n",
			strerror(errno));
		goto exit;
	}

exit:
	//clean cargparse lib
	clean(arguments);
}
