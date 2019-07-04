#define NEEDS_LIST

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"mem_mgr.h"
#include"h_map.h"

struct node **h_map_create(int rows)
{
	struct node **h_map=alloc("struct node *", rows);
	for(int i=0; i<rows; i++){
		h_map[i]=alloc_node("start");
	}

	return h_map;
}

void h_map_insert(struct node **h_map, char *ip, int rows)
{
	int key=h_map_key(ip, rows);
	struct node *new=alloc_node(ip);
	add_node(h_map[key], new);
}

int h_map_find(struct node **h_map, char *ip, int rows)
{
	int ret=0;
	int key=h_map_key(ip, rows);
	struct node *curr=find_memb(h_map[key], ip);
	if(curr!=NULL){
		ret=1;
	}

	return ret;
}

int h_map_key(char *ip, int rows)
{
	int count=0;
	char *ptr=ip;

	while(*ptr!='\0'){
		count+=(int)*ptr;
		ptr+=sizeof(char);
	}

	return count%rows;
}

void h_map_clean(struct node **h_map, int rows)
{
	for(int i=0; i<rows; i++){
		del_list(h_map[i]);
	}

	dealloc("struct node *", rows, h_map);
}
