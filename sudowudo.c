#include <stdint.h>
#include <pwd.h>
#include <stdbool.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>

char base46_map[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                     'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                     'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                     'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};


char* base64_encode(char* plain) {

    char counts = 0;
    char buffer[3];
    char* b64_encoded = malloc(strlen(plain) * 4 / 3 + 4);
    int i = 0, c = 0;

    for(i = 0; plain[i] != '\0'; i++) {
        buffer[counts++] = plain[i];
        if(counts == 3) {
            b64_encoded[c++] = base46_map[buffer[0] >> 2];
            b64_encoded[c++] = base46_map[((buffer[0] & 0x03) << 4) + (buffer[1] >> 4)];
            b64_encoded[c++] = base46_map[((buffer[1] & 0x0f) << 2) + (buffer[2] >> 6)];
            b64_encoded[c++] = base46_map[buffer[2] & 0x3f];
            counts = 0;
        }
    }

    if(counts > 0) {
        b64_encoded[c++] = base46_map[buffer[0] >> 2];
        if(counts == 1) {
            b64_encoded[c++] = base46_map[(buffer[0] & 0x03) << 4];
            b64_encoded[c++] = '=';
        } else {                      // if counts == 2
            b64_encoded[c++] = base46_map[((buffer[0] & 0x03) << 4) + (buffer[1] >> 4)];
            b64_encoded[c++] = base46_map[(buffer[1] & 0x0f) << 2];
        }
        b64_encoded[c++] = '=';
    }

    b64_encoded[c] = '\0';   /* string padding character */
    return b64_encoded;
}

bool udpSend(const char* msg, int port, char* dest_ip, char* source, char* user) {
    char payload[100] = "";
    strcat(payload, source);
    strcat(payload, ":");
    if (strlen(user) == 0){
        struct passwd *p = getpwuid(getuid());
        strcat(payload, p->pw_name);
    }else{
        strcat(payload, user);
    }
    strcat(payload, ":");
    strcat(payload, msg);
    char* encoded = base64_encode(payload);
    
    int sockfd;
    struct sockaddr_in serverAddr;
    char buffer[1024];
    socklen_t addr_size;

    sockfd = socket(PF_INET, SOCK_DGRAM, 0);
    memset(&serverAddr, '\0', sizeof(serverAddr));

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr(dest_ip);

    strcpy(buffer, encoded);
    sendto(sockfd, buffer, strlen(encoded), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    return true;
}

