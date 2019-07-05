#include<string.h>
#include<errno.h>
#include<unistd.h>
#include<curl/curl.h>

#include"transfer_utils.h"

FILE *openf(char *fname)
{
	int stat=unlink(fname);
	if(stat!=0 && errno!=2){
		fprintf(stderr, "[-]Error in unlinking file: %s\n",
			strerror(errno));
		return NULL;
	}

	FILE *f=NULL;
	if((f=fopen(fname, "w"))==NULL){
		fprintf(stderr, "[-]Error in opening file: %s\n",
			strerror(errno));
		return NULL;
	}

	return f;
}
char *fetch(char *m_url)
{
	CURL *handle=curl_easy_init();
	char *fname="./hosts.conf";
	FILE *f=openf(fname);
	if(f==NULL){
		_exit(-1);
	}

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
	fclose(f);
	return fname;
}
