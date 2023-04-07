#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#define FIFO_NAME "/tmp/fifo_crypto"

void signal_handler(int signal){
    printf("\nSIGINT detected\n");
    unlink(FIFO_NAME);
    exit(signal);
}

int main(){
    signal(SIGINT, signal_handler);
    int fd;
    char buf[1024];
    char coin[1024];

    umask(0);
    if(mkfifo(FIFO_NAME, S_IRUSR | S_IWUSR | S_IWGRP) == -1){
        perror("While creating FIFO");
        exit(1);
    }

    printf("\nWhich crypto's price do you want? Write 'ETH' for \
Ethereum or 'BTC' for Bitcoin\n");
    if(fgets(buf, sizeof(buf), stdin) == NULL)
        printf("\nEither an error occured or you entered an empty value\n");

    strcpy(coin, buf);

    fd = open(FIFO_NAME, O_RDWR);
    if (fd == -1){
        perror("\nWhile opening the FIFO for reading\n");
        exit(1);
    }
    if(write(fd, &buf, sizeof(buf)) == -1)
        perror("\nWhile trying to write to the FIFO\n");

    sleep(60);

    if(read(fd, &buf, sizeof(buf)) != -1){
        printf("\nThe price of %s is: %s\n", coin, buf);
    }


    return 0;
}