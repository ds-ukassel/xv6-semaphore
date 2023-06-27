#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"
#include "semaphore.h"


#define SEM_ARR_SIZE 10


struct semaphore
{
    unsigned int value;
    unsigned int sem_initial;
    struct spinlock sem_lock;
};
 
struct semaphore sem[SEM_ARR_SIZE];


/* Abre y/o incializa el semaforo sem con un valor arbitrario "value" */
uint64 
sys_sem_open(void){
    int sem_number; 
    int value;
    argint(0,&sem_number); 
    argint(1,&value);
    //CHECKS: semaforo valido
    if (sem_number >= SEM_ARR_SIZE ){
        //printear errores de acuerdo a lo que corresponde
        return -1;
    }
    initlock(&sem[sem_number].sem_lock, "sem_i");
    acquire(&sem[sem_number].sem_lock);
    sem[sem_number].value = value;
    sem[sem_number].sem_initial = value;
    release(&sem[sem_number].sem_lock);
    return 0;
}

/* Libera el semaforo */
uint64 
sys_sem_close(void){
    int sem_number;
    argint(0,&sem_number);
    //CHECKS: semaforo valido
    if (sem_number >= SEM_ARR_SIZE){
        printf("ingrese un nro de semáforo válido\n");
        return -1;
    };
    acquire(&sem[sem_number].sem_lock);
    if (sem[sem_number].sem_initial != sem[sem_number].value){
        printf("errror: no se puede liberar semáforo, no se encuentra en su valor inicial\n");
        release(&sem[sem_number].sem_lock);
        return -1;
    }
    sem[sem_number].value = 0u;
    sem[sem_number].sem_initial = 0u;
    release(&sem[sem_number].sem_lock);
    
    return 0;
}

/* incrementa el semaforo "sem" desbloqueando los procesos cuando corresponde */
uint64
sys_sem_up(void){
    int sem_number;
    argint(0, &sem_number);
    if (sem_number >= SEM_ARR_SIZE){
        printf("error: %d no es un nro de semáforo válido\n", sem_number);
        return -1;
    }
    acquire(&sem[sem_number].sem_lock); 
    sem[sem_number].value = sem[sem_number].value + 1; 
    release(&sem[sem_number].sem_lock);      
    if (sem[sem_number].value == 1){
        wakeup(&sem[sem_number]);                         // Despierta los procesos del canal &sem[sem_number]
    }
    return 0;
}

/* Decrementa el semaforo "sem" bloqueando los procesos si el valor actual es 0 */
uint64
sys_sem_down(void){
    int sem_number;
    argint(0, &sem_number);
    if (sem_number >= SEM_ARR_SIZE){
        printf("error: %d no es un nro de semáforo válido\n", sem_number);
        return -1;
    }
    acquire(&sem[sem_number].sem_lock);
    while (sem[sem_number].value == 0) { 
        sleep(&sem[sem_number], &sem[sem_number].sem_lock); // Duerme al proceso
    }
    sem[sem_number].value = sem[sem_number].value - 1;   

    release(&sem[sem_number].sem_lock);                     // Devolvemos el lock    

    return 0;
}


/* devuelve el valor del semáforo en el instante que se realiza el llamado*/
uint64
sys_sem_value(void){
    int sem_number;
    argint(0, &sem_number);
    if (sem_number >= SEM_ARR_SIZE){
        printf("error: %d no es un nro de semáforo válido\n", sem_number);
        return -1;
    }
    return sem[sem_number].value;
}
