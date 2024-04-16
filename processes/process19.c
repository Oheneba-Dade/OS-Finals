#include <stdio.h>
#include <pthread.h>
#define array_size 1000
#define no_threads 2
#include <math.h>

void *sumArray(void *nums);

int sum = 0;
int array[array_size];
int sum_arr[2] = {0};
int main(){
pthread_t threads[no_threads];

int size = ceil(array_size/no_threads);
int part =0;


for (int i=0; i< array_size; i++){
array[i] = i+1;
}
for(int i =0; i< no_threads; i++){
pthread_create(&threads[i], NULL, sumArray, (void*)NULL);
}
for (int i =0; i < no_threads; i++){
pthread_join(threads[i], NULL);
}
int sum = 0;
for (int i =0; i<no_threads; i++){
sum+=sum_arr[i];
}
printf("The sum of the arr is %d", sum);
}