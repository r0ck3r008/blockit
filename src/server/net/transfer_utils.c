#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<signal.h>
#include<unistd.h>
#include<curl/curl.h>

#include"mem/h_map.h"
#include"mem/mem_mgr.h"
#include"misc/utils.h"
#include"parse.h"
#include"sniff/sniff.h"
#include"transfer_utils.h"

void fetch(char *m_url)
{
	CURL *handle=curl_easy_init();
	char *fname="./hosts.conf";
	FILE *f=openf(fname, 1);
	if(f==NULL){
		_exit(-1);
	}

	if(m_url[strlen(m_url)-1]=='\n')
		m_url[strlen(m_url)-1]='\0';

	if(curl_easy_setopt(handle, CURLOPT_WRITEDATA, f)!=0){
		fprintf(stderr, "[-]Error in setting curl_opt for\
			callback_func\n");
		goto exit;
	}

	if(curl_easy_setopt(handle, CURLOPT_URL, m_url)!=0){
		fprintf(stderr, "[-]Error in setting url for fetching\n");
		goto exit;
	}

	if(curl_easy_perform(handle)!=0){
		fprintf(stderr, "[-]Error in performing the transfer\n");
	}

exit:
	curl_easy_cleanup(handle);
	free(m_url);
	fclose(f);
	fork_n_sniff(fname);
}

void sig_callbk(int signo)
{
	if(signo==SIGTERM){
		printf("[!]Ending child and cleaning cache!\n");
		h_map_clean(*h_map_ptr);
		dealloc("struct h_map_t *", 1, h_map_ptr);
	}
}

void fork_n_sniff(char *fname)
{
	static int child_pid_bk=0;
	int child_pid=fork();

	if(child_pid==0){
		//child
		if(signal(SIGTERM, sig_callbk)==SIG_ERR)
			fprintf(stderr, "[-]Error in registering signal\
				handler\n");
		sleep(1);
		struct h_map_t *h_map=file_handle(fname);
		init_sniff(h_map);
	} else{
		//parent
		if(child_pid_bk){
			//kill prev
			if(kill(child_pid_bk, SIGTERM)==-1)
				fprintf(stderr, "[-]Error in killing\
					last proc: %s\n", strerror(errno));
		}
		child_pid_bk=child_pid;
	}
}
