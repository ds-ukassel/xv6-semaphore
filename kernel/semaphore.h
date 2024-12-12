
#define SEM_ARR_SIZE 10

struct semaphore
{
    unsigned int value;
    unsigned int sem_initial;
    struct spinlock sem_lock;
};

struct semaphore sem[SEM_ARR_SIZE];

uint64 sys_sem_open(void);
uint64 sys_sem_close(void);
uint64 sys_sem_up(void);
uint64 sys_sem_down(void);
uint64 sys_sem_value(void);
