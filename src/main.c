#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

char *filter_word(char *phrase, char *hide_phrase);
char *guess_checker(char *phrase, char guess, char *hide_phrase, int *lives, char *correct_guess, int flag_guessed);
void the_man(char *head, char *left_arm, char *right_arm, char *upper_body, char *lower_body, char *left_leg, char *right_leg, int lives);
char *generate_word(char *the_word);
int guessed(char guess, char *guess_buffer, int index, int *flag_guessed);
void print_guessed(char *guess_buffer);

int main(){
  srand(time(NULL));
  char option = 'y';
  int end = 1;
  int win = 0;
  while(option == 'y'){
    system("cls");
    int flag_guessed;
    int lives = 0;
    char head = ' ', left_arm = ' ', right_arm = ' ', upper_body = ' ', lower_body = ' ', left_leg = ' ', right_leg = ' ';
    size_t size = 32;
    char the_word[size];
    memset(the_word, 0, size);
    generate_word(the_word);
    char filter_buffer[size];
    filter_word(the_word, filter_buffer);
    char guess_letter;
    char guess_buffer[size];
    memset(guess_buffer, 0, size);
    int index = 0;
    while(lives != 7){
      printf("Guess the ulam: %s\n", filter_buffer);
      the_man(&head, &left_arm, &right_arm, &upper_body, &lower_body, &left_leg, &right_leg, lives);
      print_guessed(guess_buffer);
      printf("Guess a letter: ");
      scanf(" %c%*[^\n]", &guess_letter);
      index += 1;
      guessed(guess_letter, guess_buffer, index, &flag_guessed);
      guess_checker(the_word, guess_letter, filter_buffer, &lives, guess_buffer, flag_guessed);
      system("cls");
      if(strcmp(the_word, filter_buffer) == 0){
        win = 1;
        break;
      }
    }
    printf("The ulam was: \"%s\"\n", the_word);
    the_man(&head, &left_arm, &right_arm, &upper_body, &lower_body, &left_leg, &right_leg, lives);
    if(lives == 7){
      printf("Game Over! He's dead. Very sad. RIP");
    }
    else if(win == 1){
      printf("You win! Congratulations, you saved a life! ");
    }
    printf("\nAnyway, wanna play another round? Yes(y) or No(n)? ");
    scanf(" %c", &option);
    if(option != 'y' && option != 'n'){
      while(end == 1){
        printf("Please choose between 'y' and 'n' only: ");
        scanf(" %c", &option);
        if(option == 'y' || option == 'n'){
          break;
        }
      }
    }
    else if(option == 'n'){
      break;
    }
  }
  printf("Thank you for playing! The game will exit now in 3...\n");
  sleep(3);
  return 0;
}

char *filter_word(char *phrase, char *hide_phrase){
  int i;
  for(i = 0; phrase[i] != '\0'; i++){
    if(phrase[i] >= 'a' && phrase[i] <= 'z'){
      hide_phrase[i] = '?';
    }
    else{
      hide_phrase[i] = phrase[i];
    }
  }
  hide_phrase[strlen(phrase)] = '\0';
  return hide_phrase;
}

char *guess_checker(char *phrase, char guess, char *hide_phrase, int *lives, char *correct_guess, int flag_guessed){
  int i, flag = 0;
  for(i = 0; i < strlen(phrase); i++){
    if(guess == phrase[i]){
      flag = 1;
      hide_phrase[i] = phrase[i];
    }
  }
  if(flag == 0 && flag_guessed == 0){
    *lives += 1;
  }
  return hide_phrase;
}

void the_man(char *head, char *left_arm, char *right_arm, char *upper_body, char *lower_body, char *left_leg, char *right_leg, int lives){
  switch(lives){
    case 1:
      *head = 'O';
      break;
    case 2:
      *upper_body = '|';
      break;
    case 3:
      *left_arm = '/';
      break;
    case 4:
      *right_arm = '\\';
      break;
    case 5:
      *lower_body = '|';
      break;
    case 6:
      *left_leg = '/';
      break;
    case 7:
      *right_leg = '\\';
      break;
  }
  printf("\t-----------\n");
  printf("\t|         |\n");
  printf("\t|         %c \n", *head);
  printf("\t|        %c%c%c\n", *left_arm, *upper_body, *right_arm);
  printf("\t|         %c\n", *lower_body);
  printf("\t|        %c %c\n", *left_leg, *right_leg);
  printf("\t-----------\n");
  printf("\t|||||||||||\n");
  printf("\t-----------\n"); 
}

char *generate_word(char *the_word){
  char *generate[] = {"adobo", "chicken inasal", "kare-kare", "lechon baboy", "sinigang na baboy", 
                      "pinakbet", "pork menudo", "chop suey", "lechon paksiw", "tinolang manok", 
                      "nilagang baka", "dinuguan", "pork sisig", "lechon kawali", "bulalo",
                      "laing", "ginataang kalabasa", "bicol express", "crispy pata", "pochero",
                      "kinilaw", "tortang talong", "adobong kangkong", "sarciado", "afritada"};
  int size = sizeof(generate)/sizeof(*generate);
  int row;
  row = rand() % (size - 1);
  strcpy(the_word, generate[row]);
  return the_word;
}

int guessed(char guess, char *guess_buffer, int index, int *flag_guessed){
  int i, j, alphabet = 26;
  guess_buffer[0] = 0;
  *flag_guessed = 0;
  for(i = 0; i < alphabet; i++){
    if(guess_buffer[i] == guess){
      *flag_guessed = 1;
    }
  }
  if(*flag_guessed == 0){
    guess_buffer[index] = guess;
  }
  return *flag_guessed;
}

void print_guessed(char *guess_buffer){
  int j, alphabet = 26;
  printf("Guessed letters: ");
  for(j = 0; j < alphabet; j++){
    printf("%c", guess_buffer[j]);
  }
  printf("\n");
}
