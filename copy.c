#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include "share.h"

int main() {
    pid_t p1, p2, p3;
    int shmsid, shmtid;
    char* s;
    char* t;

    int semid = semget(SEM_KEY, 4, IPC_CREAT|0666);
    printf("the copy semid:%d\n", semid);   
    shmsid = shmget(SHMS_KEY, sizeof(char)*1024, 0666);
    shmtid = shmget(SHMT_KEY, sizeof(char)*1024, 0666);
    s = (char*)shmat(shmsid, NULL, SHM_R|SHM_W);
    t = (char*)shmat(shmtid, NULL, SHM_R|SHM_W);
    printf("the copy S shmID:%d\n", shmsid);
    printf("the copy T shmID:%d\n", shmtid);
    

   
    P(semid, 1);
    P(semid, 2);
    printf("[copy] start\n");
    printf("%s will be copyed to T\n",s);
    strcpy(t, s);
    
    printf("[copy] %s\n",t);
    shmctl(shmsid,IPC_RMID,0);
    V(semid, 3);
    V(semid, 0);
    
    return 0;
}

