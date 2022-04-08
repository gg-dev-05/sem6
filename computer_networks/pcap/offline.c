#include <pcap.h>
#include <stdlib.h>
int main(int argc, char const *argv[]) {
    pcap_t *handle;
    char errbuf[PCAP_ERRBUF_SIZE];
    struct pcap_pkthdr header;
    const uint8_t *packet;
    char filename[] = "http.pcap";
    handle = pcap_open_offline(filename, errbuf);
    if (handle == NULL) {
        printf("Could not open file %s: %s\n", filename, errbuf);
        exit(-1);
    }

    int total_packets = 0;
    while (packet = pcap_next(handle, &header)) {
        printf("Got header with size: %d\n", header.caplen);
        total_packets++;
    }
    printf("Total packets recieved: %d\n", total_packets);

    pcap_close(handle);

    return 0;
}
