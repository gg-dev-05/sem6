#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pcap.h>

void my_packet_handler(u_char *args, const struct pcap_pkthdr *packet_header, const u_char *packet_body) {
    printf("Packet Capture length:%d\n", packet_header->caplen);
    return;
}
int main(int argc, char const *argv[]) {
    char *device;
    char error_buffer[PCAP_ERRBUF_SIZE];

    device = pcap_lookupdev(error_buffer);

    if (device == NULL) {
        printf("Error finding device: %s\n", error_buffer);
        return 1;
    }
    printf("Network device found: %s\n", device);

    // Get device info
    bpf_u_int32 ip_raw;
    bpf_u_int32 subnet_mask_raw;
    int lookup_return_code = pcap_lookupnet(device, &ip_raw, &subnet_mask_raw, error_buffer);
    if (lookup_return_code == -1) {
        printf("%s\n", error_buffer);
        return 1;
    }

    char ip[1];
    struct in_addr address;
    address.s_addr = ip_raw;
    strcpy(ip, inet_ntoa(address));
    printf("IP Address: %s\n", ip);

    address.s_addr = subnet_mask_raw;
    strcpy(ip, inet_ntoa(address));
    printf("Subnet Mask: %s\n", ip);

    // Open device for live capture
    pcap_t *handle;
    int timeout_limit = 10000;  // in ms
    handle = pcap_open_live(device, BUFSIZ, 0, timeout_limit, error_buffer);
    if (handle == NULL) {
        fprintf(stderr, "Could not open device %s: %s\n", device, error_buffer);
        return 2;
    }
    pcap_loop(handle, 10, my_packet_handler, NULL);
    return 0;
}