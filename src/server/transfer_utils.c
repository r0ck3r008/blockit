#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<curl/curl.h>

#include"transfer_utils.h"

size_t callback_func(void *buf)
{
	//TODO find a method to store and parse this data
	return strlen(buf);
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
