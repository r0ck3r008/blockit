#define NEEDS_LIST

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#include"h_map.h"
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
	if(!strcmp(type, "char")){
		explicit_bzero(buf, sizeof(char)*size);
	} else if(!strcmp(type, "struct node")){
		explicit_bzero(buf, sizeof(struct node)*size);
	} else if(!strcmp(type, "struct node *")){
		explicit_bzero(buf, sizeof(struct node *)*size);
	}

	free(buf);
}

struct node *alloc_node(char *ip)
{
	struct node *curr=alloc("struct node", 1);
	curr->nxt=NULL;
	curr->prev=NULL;
	curr->ip=alloc("char", 20);
	sprintf(curr->ip, "%s", ip);
	return curr;
}

void dealloc_node(struct node *curr)
{
	dealloc("char", 20, curr->ip);
	dealloc("struct node", 1, curr);
}

void add_node(struct node *start, struct node *new)
{
	struct node *curr=start;
	for(curr; curr->nxt!=NULL; curr=curr->nxt);

	curr->nxt=new;
	new->prev=curr;
}

void del_node(struct node *curr)
{
	curr->prev->nxt=curr->nxt;
	if(curr->nxt!=NULL)
		curr->nxt->prev=curr->prev;
	dealloc_node(curr);
}

void del_list(struct node *start)
{
	struct node *curr=start;
	for(curr; curr->nxt!=NULL; ){
		del_node(curr->nxt);
	}

	dealloc_node(curr);
}

struct node *find_memb(struct node *start, char *ip)
{
	struct node *curr=start;
	int flag=0;
	for(curr; curr!=NULL; curr=curr->nxt){
		if(!strcmp(curr->ip, ip)){
			flag=1;
			break;
		}
	}

	if(flag){
		return curr;
	}
	return NULL;
}
