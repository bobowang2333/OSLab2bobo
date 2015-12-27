#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include "share.h"


int main() {
    pid_t p1, p2, p3;
    int semid = semget(SEM_KEY,4,IPC_CREAT|0666);
    int shmsid, shmtid;
    char* s;
    char* t;

    shmsid = shmget(SHMS_KEY, sizeof(char)*1024, IPC_CREAT|0666);
    shmtid = shmget(SHMT_KEY, sizeof(char)*1024, IPC_CREAT|0666);
    printf("the shmID:%d\n", shmsid);
    printf("the shmtid:%d\n", shmtid);
    s = (char*)shmat(shmsid, NULL, SHM_R|SHM_W);
    t = (char*)shmat(shmtid, NULL, SHM_R|SHM_W);

    semctl(semid, 0, SETVAL, 1);
    semctl(semid, 1, SETVAL, 0);
    semctl(semid, 2, SETVAL, 1);
    semctl(semid, 3, SETVAL, 0);
       
    printf("the main semid:%d\n",semid);
    
    if ((p1 = fork()) == 0)
    {
        execv("./get", NULL);
    } else
    {
        if ((p2 = fork()) == 0)
        {
            execv("./copy", NULL);  
        } else
        {
            execv("./put", NULL);
        }
    }
    semctl(semid,0,IPC_RMID,0);

    shmctl(shmtid,IPC_RMID,0);
    return 0;
}

