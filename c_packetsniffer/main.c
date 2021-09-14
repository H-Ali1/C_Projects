#include <stdio.h>
#include "pcap/pcap.h"

int main(int argc, char* argv[]) {
    pcap_t *handle;

    char *dev, errbuf[PCAP_ERRBUF_SIZE];



    dev = pcap_lookupdev(errbuf);

    handle  = pcap_open_live(dev, BUFSIZ, 1, 1000, errbuf);
    // If pcap lookup fails, stores error message in errbuf and prints it
    if(handle = NULL){

        fprintf(stderr,"Couldn't find device: %s\n", errbuf);
        return(2);

    }
    // user specifices the device as first argument
    printf("Device is: %s\n", dev);

    return 0;

}
