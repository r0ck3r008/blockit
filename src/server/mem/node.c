#include<stdio.h>
#include<string.h>

#include"node.h"
#include"mem_mgr.h"

struct node *alloc_node(char *ip)
{
	struct node *curr=alloc("struct node", 1);
	curr->nxt=NULL;
	curr->prev=NULL;
	curr->ip=alloc("char", 20);
	sprintf(curr->ip, "%s", ip);
	curr->blk=0;
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
