#server
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

struct data { char str[100]; int flag; };

int main() {
    key_t key = ftok("abc.txt", 'A');
    int shmid = shmget(key, sizeof(struct data), 0777 | IPC_CREAT);
    struct data *d = (struct data *)shmat(shmid, NULL, 0);

    printf("Enter data: ");
    fgets(d->str, sizeof(d->str), stdin);
    d->flag = 1;

    while (d->flag != -1) { sleep(2); }
    shmdt(d); shmctl(shmid, IPC_RMID, NULL);
    return 0;
}




//client.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

struct data { char str[100]; int flag; };

int main() {
    key_t key = ftok("abc.txt", 'A');
    int shmid = shmget(key, sizeof(struct data), 0777 | IPC_CREAT);
    struct data *d = (struct data *)shmat(shmid, NULL, 0);

    while (d->flag != 1) { sleep(2); }
    printf("Accepted data: %s", d->str);
    d->flag = -1;
    shmdt(d);
    return 0;
}


//output
student@student:~$ gcc -o server server.c
student@student:~$ ./server
Enter data: Hello I am Yash


student@student:~$ gcc -o client client.c
student@student:~$ ./client
Accepted data: Hello I am Yash
student@student:~