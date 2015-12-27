#ifndef OOSHARE_H
#define OOSHARE_H

#define SEM_KEY 0x12
#define SHMS_KEY 0x22
#define SHMT_KEY 0x33

int P(int semid, int index);
int V(int semid, int index);

#endif

