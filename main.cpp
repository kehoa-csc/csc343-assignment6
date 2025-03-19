#include <iostream>   //prints
#include <pthread.h> 
#include <mutex>
using namespace std;

/*
    Assignment 6 for CSC343. Written by Andrew Kehoe.
*/

//shared thread data
int data = 0;
int curr_thread = 0;
//threads run this method
void *runner( void *ptr ); 
mutex m;

int main() {

   pthread_t tid1, tid2; //defining threads
   pthread_attr_t attr1, attr2;

   pthread_attr_init(&attr1);
   pthread_attr_init(&attr2);
   pthread_create(&tid1, &attr1, runner, NULL);
   pthread_create(&tid2, &attr2, runner, NULL);

   pthread_join(tid1,NULL);
   pthread_join(tid2,NULL);

   return 0;
}

void *runner(void *ptr) {
    m.lock();
    curr_thread++;
    printf("I am thread %d.\n",curr_thread);
    if (curr_thread == 1) {
        data = 12345;
    } else if (curr_thread == 2) {
        printf("data is %d\n",data);
    }
    m.unlock();
    return 0;
}