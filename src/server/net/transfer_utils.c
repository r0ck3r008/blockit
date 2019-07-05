#include<string.h>
#include<errno.h>
#include<unistd.h>
#include<sys/types.h>
#include<regex.h>
#include<curl/curl.h>

#include"transfer_utils.h"

size_t callback_func(void *buf)
{
	//TODO check why callback function cannot handle splitting
	//and regex checking
	char *ptr=strtok(buf, "\n");
	while(ptr!=NULL){
		if(regex_chk(ptr)){
			printf("%s\n", ptr);
		}
		ptr=strtok(NULL, "\n");
	}

	return strlen(buf);
}

int regex_chk(char *str)
{
	int stat, ret=0;
	regex_t reg;

	stat=regcomp(&reg, "^[#\n]", 0);
	if(stat!=0){
		fprintf(stderr, "[-]Error in compiling regexp: %s\n",
			strerror(stat));
		goto exit;
	}

	stat=regexec(&reg, str, 0, NULL, 0);
	if(stat==REG_NOMATCH){
		ret=1;
	}

exit:

	if(!ret)
		regfree(&reg);
	return ret;
}

void fetch(char *m_url)
{
	CURL *handle=curl_easy_init();

	if(curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, callback_func)!=0){
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
}
