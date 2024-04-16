#include <stdio.h>
#define array_size 1000


int array[array_size];

long result = 0;
int main (){

for (int i =0; i<array_size;i++){
array[i] = i+1;
}
for (int i=0; i< array_size; i++){
 result+=array[i];
}
printf("The result is %ld\n", result);
}