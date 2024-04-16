#include <stdio.h>
#include <string.h>
#include <ctype.h>
void modify_string(char sentence[]);
void count_letters(char characters[]);

void print_nested(int rows, int columns);
int main(){
char sentence [100];
printf("Enter the sentence\n");

fgets(sentence, sizeof(sentence), stdin);
//count_letters(sentence);
print_nested(10, 9);
return 0;
}

void modify_string(char sentence[]){
char space = ' ';

sentence[0] = toupper(sentence[0]);
for (int i =1; i< strlen(sentence); i++){
 if (sentence[i] == space){
  sentence[i+1] = toupper(sentence[i+1]);
 }
}
printf("%s", sentence);
}

void count_letters(char characters[]){
int lowercase, uppercase, special = 0;
char space = ' ';
for (int i =0; i< strlen(characters); i++){
   char character = characters[i];
 if (character != space && !isdigit(character)){
 if (isupper(character)) {
	 uppercase+=1;
 }
  else if (islower(character)){ 
	  lowercase+=1;
  }
 else {
	 special+=1;
}
}
}
printf(" The number of uppercase letters are: %d\n The number of lowercase are: %d \n The number of special letters are: %d \n", uppercase, lowercase, special);
}

void print_nested(int rows, int columns){
for (int i =0; i< rows; i++){
 for (int  j =0; j < columns; j++){
	 if (i%2==0)
	 printf("*\n");
 }
}
}