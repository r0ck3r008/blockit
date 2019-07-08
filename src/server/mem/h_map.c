#include<string.h>

#include"mem_mgr.h"
#include"h_map.h"

struct h_map_t *h_map_create(int rows)
{
	struct h_map_t *h_map_st=alloc("struct h_map_t", 1);
	struct node **h_map=alloc("struct node *", rows);
	for(int i=0; i<rows; i++){
		h_map[i]=alloc_node("start");
	}

	h_map_st->h_map=h_map;
	h_map_st->rows=rows;

	return h_map_st;
}

void h_map_insert(struct h_map_t *h_map, char *ip)
{
	int key=h_map_key(ip, h_map->rows);
	struct node *new=alloc_node(ip);
	add_node(h_map->h_map[key], new);
}

int h_map_find(struct h_map_t *h_map, char *ip)
{
	int ret=0;
	int key=h_map_key(ip, h_map->rows);
	struct node *curr=find_memb(h_map->h_map[key], ip);
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

void h_map_clean(struct h_map_t *h_map)
{
	for(int i=0; i<h_map->rows; i++){
		del_list(h_map->h_map[i]);
	}

	dealloc("struct node *", h_map->rows, h_map->h_map);
}
