#define NEED_ARGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#include"h_map.h"
#include"misc/utils.h"
#include"mem_mgr.h"

void *alloc(char *type, int size)
{
	void *ret=NULL;

	if(!strcmp(type, "char")){
		ret=malloc(sizeof(char)*size);
		explicit_bzero(ret, sizeof(char)*size);
	} else if(!strcmp(type, "struct node")){
		ret=malloc(sizeof(struct node)*size);
		explicit_bzero(ret, sizeof(struct node)*size);
	} else if(!strcmp(type, "struct node *")){
		ret=malloc(sizeof(struct node *)*size);
		explicit_bzero(ret, sizeof(struct node *)*size);
	} else if(!strcmp(type, "struct h_map_t")){
		ret=malloc(sizeof(struct h_map_t)*size);
		explicit_bzero(ret, sizeof(struct h_map_t)*size);
	} else if(!strcmp(type, "struct arg *")){
		ret=malloc(sizeof(struct arg *)*size);
		explicit_bzero(ret, sizeof(struct arg *)*size);
	}

	if(ret==NULL){
		fprintf(stderr, "[-]Error in allocating %d bytes for %s type\n",
			size, type);
		_exit(-1);
	}

	return ret;
}

void dealloc(char *type, int size, void *buf)
{
	if(!strcmp(type, "char"))
		explicit_bzero(buf, sizeof(char)*size);
	else if(!strcmp(type, "struct node"))
		explicit_bzero(buf, sizeof(struct node)*size);
	else if(!strcmp(type, "struct node *"))
		explicit_bzero(buf, sizeof(struct node *)*size);
	else if(!strcmp(type, "struct h_map_t"))
		explicit_bzero(buf, sizeof(struct h_map_t)*size);
	else if(!strcmp(type, "struct arg *"))
		explicit_bzero(buf, sizeof(struct arg *)*size);

	free(buf);
}
