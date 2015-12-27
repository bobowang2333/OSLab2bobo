#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include "share.h"

int main() {
    pid_t p1, p2, p3;
    int shmsid;
    char* s;
    FILE *fp;
    fp = fopen("try.txt","r");
    
    if(fp == NULL)
    {
        fputs("file error!\n",stderr);
        exit(1);
    }

    int semid = semget(SEM_KEY, 4, IPC_CREAT|0666);
    shmsid = shmget(SHMS_KEY, sizeof(char)*1024, 0666);
    s = (char*)shmat(shmsid, NULL, SHM_W|SHM_R);
    printf("get shmID->%d\n",shmsid);
    printf("the get semid:%d\n",semid);
    
        P(semid,0);
        int len = fread(s,sizeof(char),20,fp);
        s[len] = '\0';
       
        
    printf("[get]%s \n",s);
    printf("[get] done!\n");
    V(semid,1);
    return 0;
        
}

