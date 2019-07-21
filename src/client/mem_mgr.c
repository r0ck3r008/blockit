#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"mem_mgr.h"

void *alloc(char *type, int size)
{
	void *ret=NULL;

	if(!strcmp(type, "char")){
		ret=malloc(sizeof(char)*size);
		explicit_bzero(ret, sizeof(char)*size);
	}

	if(ret==NULL){
		fprintf(stderr, "[-]Error in allocating %d bytes for %s type\n",
			size, type);
	}

	return ret;
}

void dealloc(char *type, int size, void *buf)
{
	if(!strcmp(type, "char")){
		explicit_bzero(buf, sizeof(char)*size);
	}

	free(buf);
}
