#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include <stddef.h>



int main(int argc,char *argv[]){
    int length;
    length = atoi(argv[1]);
    int err1, err2;
    if (length < 0){
        printf("Ingrese un número válido. Usage : pingpong [0-N]\n");
        exit(1);
    }
    err1 = sem_open(0,1);
    err2 = sem_open(1,0);
    if (err1 < 0 || err2 < 0){
        printf("error opening semaphore\n");
        exit(1);
    }
    //los sleep() no son necesarios, solo pretty printer
    int pid = fork();
    if (pid == 0){
        for (int i = 0; i < length; ++i){
            sleep(10);
            sem_down(1);
            printf("            pong\n");
            sem_up(0);
            sleep(10);
        }
    }
    if (pid > 0){
        for (int i = 0; i < length; i++){
            sem_down(0);
            printf("ping\n");
            sem_up(1);
            sleep(20);
        }
        wait(NULL);
        sem_close(0);
        sem_close(1);
    }
    return 0;
}