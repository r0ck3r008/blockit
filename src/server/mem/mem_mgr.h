#ifndef MEM_MGR_H
#define MEM_MGR_H

#ifdef NEEDS_LIST
	struct node
	{
		char *ip;
		struct node *nxt;
		struct node *prev;
	};
	struct node *alloc_node(char *);
	void dealloc_node(struct node *);
	void add_node(struct node *, struct node *);
	void del_node(struct node *);
	void del_list(struct node *);
	struct node *find_memb(struct node *start, char *);
#endif

void *alloc(char *, int);
void dealloc(char *, int, void *);

#endif
