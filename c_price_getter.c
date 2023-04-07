#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

extern __uint32_t convert(__uint32_t a,__uint32_t b);

#define FIFO_NAME "/tmp/fifo_crypto"

void signal_handler(int signal){
    printf("\nSIGINT detected\n");
    unlink(FIFO_NAME);
    exit(signal);
}

int main(){
    //asm("include converter.asm");
    signal(SIGINT, signal_handler);
    int fd;
    char buf[1024];
    char coin[1024];
    ssize_t num_bytes;

    umask(0);
    if(mkfifo(FIFO_NAME, 0666) == -1){
        perror("While creating FIFO");
        exit(1);
    }

    printf("\nWhich crypto's price do you want? Write 'ETH' for \
Ethereum or 'BTC' for Bitcoin\n");
    if(fgets(buf, sizeof(buf), stdin) == NULL)
        printf("\nEither an error occured or you entered an empty value\n");

    strcpy(coin, buf);

    //fd = open(FIFO_NAME, O_WRONLY);
    fd = open(FIFO_NAME, O_RDWR);
    if (fd == -1){
        perror("\nWhile opening the FIFO for reading\n");
        exit(1);
    }
    if(write(fd, &buf, sizeof(buf)) == -1)
        perror("\nWhile trying to write to the FIFO\n");

    int i = 0;
    while (i < 2) {
        num_bytes = read(fd, buf, sizeof(buf));
        if (num_bytes == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }
        if (num_bytes == 0) {
            printf("End of file\n");
            break;
        }
        // convert binary data to human-readable text
        buf[num_bytes] = '\0';
        i++;
    }
    printf("Received message: %s\n", buf);

    __uint32_t USD_ARS = 392;
    __uint32_t USD_EUR = 0.90;

    __uint32_t AUX = strtoul(buf, NULL, 10);

    __uint32_t A_PESO;
    __uint32_t A_EURO;

    A_PESO = convert(AUX,USD_ARS);

    AUX = strtoul(buf, NULL, 10);

    A_EURO = convert(AUX,USD_EUR);

    printf("El valor de %s es %d ARS",coin,A_PESO);
    printf("El valor de %s es %d ARS",coin,A_EURO);

    close(fd);
    unlink(FIFO_NAME);

    return 0;
}