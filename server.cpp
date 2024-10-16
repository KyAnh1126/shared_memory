#include <iostream>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <cstring>  
#include <unistd.h>  
#include <signal.h>
#include <thread>

using namespace std;

#define MSG_SZ 2048

int shmid;
char* msg;

int main() {
    key_t key = ftok("shmfile", 65);

    shmid = shmget(key, MSG_SZ, 0666 | IPC_CREAT); //0666: access permission to shared memory segment, IPC_CREAT: create shared memory segment if not exist

    msg = (char*)shmat(shmid, (void*)0, 0); 
    //attach shared memory segment to process
    //void *shmat(int shmid ,void *shmaddr ,int shmflg), shmaddr = (void*)0 -> OS should choose an address to attach to shared memory segment
    
    printf("shared memory segment attached at %p\n", (void*)msg);

    printf("enter a message: ");
    fgets(msg, MSG_SZ, stdin);

    printf("data writen into shared memory: %s\n", msg);

    shmdt(msg); //detach shared memory from process

    // shmctl(shmid, IPC_RMID, NULL);
}