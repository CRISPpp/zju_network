#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_endian.h>
#include <linux/if_ether.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include <linux/in.h>
#include <linux/ipv6.h>

#include "xdp_packet.h"

struct {
	__uint(type, BPF_MAP_TYPE_ARRAY);
	__type(key, __u32);
	__type(value, struct packet_info);
	__uint(max_entries, 1 << 24);
} xdp_stats_map SEC(".maps");

static __always_inline int bpf_memcmp(const void *s1, const void *s2, __u32 n) {
    const unsigned char *c1 = s1, *c2 = s2;
    for (__u32 i = 0; i < n; i++) {
        if (c1[i] != c2[i])
            return c1[i] - c2[i];
    }
    return 0;
}


#ifndef lock_xadd
#define lock_xadd(ptr, val)	((void) __sync_fetch_and_add(ptr, val))
#endif
struct packet_info tmp;

SEC("xdp")
int xdp_prog(struct xdp_md *ctx) {
    struct packet_info *rec;
    __u32 key = XDP_PASS;
	void *data_end = (void *)(long)ctx->data_end;	
	void *data = (void *)(long)ctx->data;
	__u64 bytes = data_end - data;
    struct ethhdr *eth = data;

	rec = bpf_map_lookup_elem(&xdp_stats_map, &key);

	if (!rec){
		tmp.receive_bytes = 100000;
		tmp.receive_packets = 100000;
        tmp.send_bytes = 100000;
		tmp.send_packets = 100000;
		rec = &tmp;
		bpf_map_update_elem(&xdp_stats_map, &key, rec, BPF_ANY);
		return XDP_ABORTED;
	}

    if ((void *)eth + sizeof(*eth) > data_end)
        return XDP_PASS;

    lock_xadd(&rec->send_packets, 1);
	lock_xadd(&rec->send_bytes, bytes);
    
    if (eth->h_proto == __constant_htons(ETH_P_IP)) {
        struct iphdr *iph = data + sizeof(*eth);
        
        if ((void *)iph + sizeof(*iph) > data_end)
            return XDP_PASS;
        bpf_printk("IPv4 Source Address: %u.%u.%u.%u\n",
            iph->saddr & 0xFF,
            (iph->saddr >> 8) & 0xFF,
            (iph->saddr >> 16) & 0xFF,
            (iph->saddr >> 24) & 0xFF);

        bpf_printk("IPv4 Destination Address: %u.%u.%u.%u\n",
            iph->daddr & 0xFF,
            (iph->daddr >> 8) & 0xFF,
            (iph->daddr >> 16) & 0xFF,
            (iph->daddr >> 24) & 0xFF);

        if (iph->saddr == __constant_htonl(0x7F000001)) {
            bpf_printk("IPv4 packet from localhost: 127.0.0.1\n");
            lock_xadd(&rec->send_packets, 1);
	        lock_xadd(&rec->send_bytes, bytes);
        }
        
        if (iph->daddr == __constant_htonl(0x7F000001)) {
            bpf_printk("IPv4 packet to localhost: 127.0.0.1\n");
            lock_xadd(&rec->receive_packets, 1);
	        lock_xadd(&rec->receive_bytes, bytes);
        }
    } 
    else if (eth->h_proto == __constant_htons(ETH_P_IPV6)) {
        struct ipv6hdr *ip6h = data + sizeof(*eth);
        if ((void *)ip6h + sizeof(*ip6h) > data_end)
            return XDP_PASS;
        struct in6_addr localhost_ip6 = {{{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 }}};
        
        if (bpf_memcmp(&ip6h->saddr, &localhost_ip6, sizeof(localhost_ip6)) == 0) {
            bpf_printk("IPv6 packet from localhost: ::1\n");
            lock_xadd(&rec->send_packets, 1);
	        lock_xadd(&rec->send_bytes, bytes);
        }
        
        if (bpf_memcmp(&ip6h->daddr, &localhost_ip6, sizeof(localhost_ip6)) == 0) {
            bpf_printk("IPv6 packet to localhost: ::1\n");
            lock_xadd(&rec->receive_packets, 1);
	        lock_xadd(&rec->receive_bytes, bytes);
        }
    }

	bpf_map_update_elem(&xdp_stats_map, &key, rec, BPF_ANY);

    return XDP_PASS;
}

char _license[] SEC("license") = "GPL";
