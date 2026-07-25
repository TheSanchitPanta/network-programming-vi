#include <stdio.h>
#include <pthread.h>

void* handle_client(void* msg) {
    printf("Thread handling: %s \n", msg);
    return NULL;
}

int main() {
    pthread_t t1, t2;
    
    pthread_create(&t1, NULL, handle_client, "Client A");
    pthread_create(&t2, NULL, handle_client, "Client B");
    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    
    printf("Both clients done!\n");
    return 0;
}