#ifndef H_MAP_H
#define H_MAP_H

#include"node.h"

struct h_map_t{
	struct node **h_map;
	int rows;
};

struct h_map_t *h_map_create(int);
void h_map_insert(struct h_map_t *, char *);
int h_map_find(struct h_map_t *, char *);
int h_map_key(char *, int);
void h_map_clean(struct h_map_t *);

#endif
