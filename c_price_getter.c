#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

extern float convert(float a,float b);

#define FIFO_NAME "/tmp/fifo_crypto"

void signal_handler(int signal){
    printf("\nThe SIGINT signal was received\n");
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

    // Verificar si la FIFO existe
    if (access(FIFO_NAME, F_OK) == -1) {
        // Si no existe, crear la FIFO
        if(mkfifo(FIFO_NAME, 0666) == -1){
        perror("While creating FIFO");
        exit(1);
        }
    }

    printf("\nWhich crypto's price do you want? Write 'ETH' for \
Ethereum or 'BTC' for Bitcoin\n");
    if(fgets(buf, sizeof(buf), stdin) == NULL)
        printf("\nEither an error occured or you entered an empty value\n");

    int i=0;
    while (1) {   
        if(strcmp(&buf[i], "\n")== 0){
            buf[i] = '\0';
            break;
        }
        i++;
    }
    strcpy(coin, buf);

    fd = open(FIFO_NAME, O_WRONLY);
    if (fd == -1){
        perror("\nWhile opening the FIFO for reading\n");
        exit(1);
    }
    if(write(fd, &buf, sizeof(buf)) == -1)
        perror("\nWhile trying to write to the FIFO\n");
    sleep(1);
    close(fd);
    fd = open(FIFO_NAME, O_RDONLY);
    i = 0;
    while (1) {
        num_bytes = read(fd, buf, sizeof(buf));
        if (num_bytes == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }
        if(num_bytes>0){
            printf("Received message: Price of %s is %s USD.\n", coin, buf);
            buf[num_bytes] = '\0';
        }
        //Final de la lectura
        if (num_bytes == 0) {
            break;
        }

        i++;
    }

    float USD_ARS = 392;
    float USD_EUR = 0.90;
    //float USD_EUR = 1;
    char *endptr;

    float AUX = strtof(buf, &endptr);

    float A_PESO;
    float A_EURO;

    A_PESO = convert(AUX,USD_ARS);

    AUX = strtoul(buf, NULL, 10);

    A_EURO = convert(AUX,USD_EUR);

    printf("Price of %s is %f ARS.\n", coin, A_PESO);
    printf("Price of %s is %f EUR.\n", coin, A_EURO);

    close(fd);
    unlink(FIFO_NAME);

    return 0;
}