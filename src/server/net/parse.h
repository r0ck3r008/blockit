#ifndef PARSE_H
#define PARSE_H

struct h_map_t *file_handle(char *);
int process_rd_buf(char **, struct h_map_t *);
void process_line(char *, struct h_map_t *);
char *find_ip(char *);
int regex_chk(char *);

#endif
