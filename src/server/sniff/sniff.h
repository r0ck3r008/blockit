#ifndef SNIFF_H
#define SNIFF_H

#include<pcap/pcap.h>
#include"mem/h_map.h"

void init_sniff(struct h_map_t *);
pcap_if_t *find_app_dev(pcap_if_t *, char *);
pcap_t *get_handle(char *);
int compile_fltr(pcap_t *, char *);
void callbk_fn(u_char *, const struct pcap_pkthdr *,
		const u_char *pkt);
struct h_map_t **h_map_ptr;

#endif
