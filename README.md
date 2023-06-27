# Implementation-of-Named-Semaphores-in-XV6-Operating-System

The project implements a user-space Semaphore system for process synchronization in the XV6 operating system. The implemented semaphores follow the style of named semaphores, similar to POSIX named semaphores. Here are the key features of the semaphore system:

- The semaphores are managed by the kernel and are globally available to all processes in the system.
- Each semaphore has a name that identifies it in the kernel.
- The state of semaphores persists as long as the operating system is active.
- The semaphore system provides four main syscalls: `sem_open()`, `sem_close()`, `sem_up()`, and `sem_down()`.

In addition to implementing these syscalls, the project includes user programs to test the functionality of the semaphore system, such as `barrier_init`, `barrier_echo`, `barrier_rise`, and `barrier_release`. It also implements a user program called "pingpong" that synchronizes the printing of the "ping" and "pong" strings using the semaphores.

## Syscalls
The semaphore system implements the following syscalls:

- `int sem_open(int sem, int value)`: Opens and initializes the semaphore identified by "sem" with an arbitrary value "value".
- `int sem_close(int sem)`: Releases the semaphore identified by "sem".
- `int sem_up(int sem)`: Increments the semaphore "sem", unblocking processes when its value is 0.
- `int sem_down(int sem)`: Decrements the semaphore "sem", blocking processes when its value is 0.

These syscalls allow manipulation of the semaphores in user-space and provide synchronization mechanisms between processes.

## "Pingpong" Program
The "pingpong" program is an example of using the implemented semaphore system. Its goal is to synchronize the printing of the "ping" and "pong" strings using semaphores.

The "pingpong" program accepts an integer argument N, which indicates the number of times the "ping" and "pong" words will be printed. The program creates two processes using the `fork()` system call. One process is responsible for printing "ping" N times, ensuring that there are never two consecutive "ping" strings without a "pong" in between. The other process is responsible for printing "pong" N times, avoiding printing two consecutive "pong" strings without a "ping" in between.

The "pingpong" program guarantees that exactly 2N lines will be printed with the "ping" and "pong" strings interleaved. The program execution will not terminate until the complete "pingpong" game is finished. Once finished, the semaphores used by the program will be available for reuse.

## Useful XV6 Commands and Installation
To install and run XV6, follow these steps:

1. Clone the XV6 repository: `git clone https://github.com/mit-pdos/xv6-riscv.git`
2. Copy the cloned files to your Bitbucket repository assigned to your group.
3. Make the first commit and push the project.
4. Install QEMU: `sudo apt-get install qemu-system-riscv64`
5. Compile and run XV6: Navigate to the root directory of XV6 in your repository (there should be a "Makefile" file) and execute the command `make qemu`.

Useful XV6 commands:

- `ls`: Lists all available user programs in the system.
- `Ctrl-p`: Lists all running processes in the system.
- `Ctrl-a x`: Exits the operating system.

I hope this provides the information you need to present your project. If

 you have any further questions or need additional assistance, feel free to ask!
