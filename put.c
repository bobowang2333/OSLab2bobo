#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include "share.h"

int main() {
    pid_t p1, p2, p3;
    int shmtid;
    FILE* fp1;
    char* t;

    int semid = semget(SEM_KEY, 4, IPC_CREAT|0666);
    printf("the put  segetmid:%d\n", semid);
    shmtid = shmget(SHMT_KEY, sizeof(char)*1024, 0666);
    t = (char*)shmat(shmtid, NULL, SHM_W|SHM_R);
    printf("the put shmID is %d\n", shmtid);
    
    
    fp1 = fopen("result.txt", "w");
    P(semid, 3);
    printf("[put] start %s \n",t);
    fputs(t, fp1);
    V(semid, 2);
    printf("[put] end\n");
    semctl(semid,0,IPC_RMID,0);

    shmctl(shmtid,IPC_RMID,0);
    return 0;
}

