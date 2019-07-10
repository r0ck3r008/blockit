#define NEED_ARGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<net/ethernet.h>
#include<netinet/ip.h>
#include<unistd.h>

#include"mem/mem_mgr.h"
#include"misc/utils.h"
#include"sniff.h"

void init_sniff(struct h_map_t *h_map)
{
	char *iface, *exp;
	if(arguments_glbl!=NULL){
		iface=find_arg_val(arguments_glbl, "iface");
		exp=find_arg_val(arguments_glbl, "expr");
	} else{
		fprintf(stderr, "[!]Empty arguments received!\n");
		_exit(-1);
	}

	pcap_t *handle;
	if((handle=get_handle(iface))==NULL)
		_exit(-1);

	if(compile_fltr(handle, exp))
		_exit(-1);

	if(pcap_loop(handle, -1, callbk_fn, (u_char *)h_map)){
		fprintf(stderr, "[-]Error in stating the capture process\n");
		_exit(-1);
	}

}

void callbk_fn(u_char *arg, const struct pcap_pkthdr *hdr,
		const u_char *pkt)
{
	struct h_map_t *h_map=(struct h_map_t *)arg;
	static int count=0;
	struct ip *ip_ptr;
	u_int len=hdr->len;
	ip_ptr=(struct ip *)(pkt+sizeof(struct ether_header));
	len-=sizeof(struct ether_header);

	//check if we have correct length range
	if(len<sizeof(struct ip)){
		fprintf(stderr, "[-]Truncated packet length: %d\n",
			len);
		return;
	}

	int ip_len=ntohs(ip_ptr->ip_len);
	int hlen=ip_ptr->ip_hl;
	int version=ip_ptr->ip_v;

	if(version!=4){
		fprintf(stderr, "[-]Wrong IP version recieved: %d\n",
			version);
		return;
	}
	if(hlen<5){
		fprintf(stderr, "[-]Bad hlen: %d\n", hlen);
		return;
	}
	if(len<ip_len){
		fprintf(stderr, "[!]Truncated pkt recieved\n");
		return;
	}

	//TODO check the reason why the same src and dst are printed
	//in a single printf call even though gdb inspection yeilds
	//correct dst and src addresses with same inet_ntoa call.
	//Also, wierdly enough, two printf calls yeild correct result
//	printf("[%d]Source: %s\t", ++count, inet_ntoa(ip_ptr->ip_src));
//	printf("Dest: %s\n", inet_ntoa(ip_ptr->ip_dst));
	if(h_map_find(h_map, inet_ntoa(ip_ptr->ip_dst))){
		printf("[!]Blocking %s\n", ip_ptr->ip_dst);
	}
}

pcap_if_t *find_app_dev(pcap_if_t *start, char *name)
{
	pcap_if_t *curr=start;
	int flag=1;

	for(curr; curr!=NULL; curr=curr->next){
		if(!strcmp(name, curr->name)){
			printf("[!]Found appropriate device %s\n",
				name);
			flag=0;
			break;
		}
	}

	if(flag){
		fprintf(stderr, "[-]Appropriate device not found!\n");
		curr=NULL;
	}

	return curr;
}

pcap_t *get_handle(char *iface)
{
	char *errbuf=alloc("char", PCAP_ERRBUF_SIZE);
	pcap_if_t *all_devs;
	pcap_t *handle=NULL;

	if(pcap_findalldevs(&all_devs, errbuf)==-1){
		fprintf(stderr, "[-]Error in finding devices: %s\n",
			errbuf);
		return NULL;
	}

	pcap_if_t *dev=find_app_dev(all_devs, iface);
	if(dev==NULL){
		goto exit;
	}

	handle=pcap_open_live(dev->name, 2048,
				0, 512, errbuf);
	if(handle==NULL){
		fprintf(stderr, "[-]Error in opening live: %s\n",
			errbuf);
		goto exit;
	}

exit:
	pcap_freealldevs(all_devs);
	dealloc(errbuf, PCAP_ERRBUF_SIZE, errbuf);
	return handle;
}

int compile_fltr(pcap_t *handle, char *fltr_exp)
{
	struct bpf_program fp;
	bpf_u_int32 netp=PCAP_NETMASK_UNKNOWN;

	if(pcap_compile(handle, &fp, fltr_exp,
			0, netp))
	{
		pcap_perror(handle, "[-]Error in compiling fltr: ");
		return 1;
	}

	if(pcap_setfilter(handle, &fp)){
		pcap_perror(handle, "[!]Error in setting fltr: ");
		return 1;
	}

	printf("[!]Expression compiled and applied: %s\n", fltr_exp);
	return 0;
}
