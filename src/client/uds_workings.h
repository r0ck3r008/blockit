#ifndef UDS_WORKINGS_H
#define UDS_WORKINGS_H

int sock_create(char *);
void uds_workings(char *, char *);
int wrt(int, char *, char *);
int rd(int, char *, char *);

#endif
