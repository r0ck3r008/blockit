#ifndef H_MAP_H
#define H_MAP_H

struct node
{
	char *ip;
	struct node *nxt;
	struct node *prev;
};

struct node **h_map_create(int);
void h_map_insert(struct node **, char *, int);
int h_map_find(struct node **, char *, int);
int h_map_key(char *, int);
void h_map_clean(struct node **, int);

#endif
