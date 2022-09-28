#include <cstdlib>
#include <pthread.h>
#include <cstdio>

void *print_message_function(void *ptr);

int main() {
    pthread_t thread1, thread2;
    const char *message1 = "Hi! I am child thread1";
    const char *message2 = "Hi! I am child thread2";
    int iret1, iret2;

    /* Create independent threads each of which will execute function */

    iret1 = pthread_create(&thread1, NULL, print_message_function, (void *) message1);
    if (iret1) {
        fprintf(stderr, "Error - pthread_create() return code: %d\n", iret1);
        exit(EXIT_FAILURE);
    }

    iret2 = pthread_create(&thread2, NULL, print_message_function, (void *) message2);
    if (iret2) {
        fprintf(stderr, "Error - pthread_create() return code: %d\n", iret2);
        exit(EXIT_FAILURE);
    }

    /* Wait till threads are complete before main continues. Unless we  */
    /* wait we run the risk of executing an exit which will terminate   */
    /* the process and all threads before the threads have completed.   */

    printf("I am the parent thread. I have created two child threads and am waiting for them to complete\n");
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    exit(EXIT_SUCCESS);
}

void *print_message_function(void *ptr) {
    char *message;
    message = (char *) ptr;
    printf("%s \n", message);
}
