#include <stdio.h>
#include <cv.h>
#include <cvaux.h>
#include <highgui.h>

#define max_char 100

/*** Assinatura dos métodos ***/
void  print_menu();
void  realize_action(int in);
int   get_input_int();
char* get_input_char();
void  realize_action();
void  create_vector();
void  recognize(char *file);
/*****************************/


int main(){

  int input;

  while (input != 3){
    print_menu();
    input = get_input_int();
    realize_action(input);
  }

  return 0;
}

//Imprime opções de seleção do menu
void print_menu(){
  printf("Escolha uma das seguintes opções:\n");
  printf("1. Inserir conjunto de treino.\n"); 
  printf(" 2. Reconhecer espécie vegetal.\n"); 
  printf(" 3. Sair.\n");
}

//Le informação do usuário:Integer
int get_input_int(){
    int input;
    scanf("%i",&input);
    return input;
}

//Le informação do usuário:String
char* get_input_char(){
    char input[max_char];
    scanf("%s",&input);
    return input;
}


//Faz a chamada para a opção escolhida
void realize_action(int in){
  switch (in){
         case 1:
              printf("Em qual diretório estão as imagens?\n");
              char dir[max_char];
              dir = get_input_char();
              create_vector(dir);
              break;
         case 2:
              printf("Qual o endereço da imagem que deseja reconheceer?\n");
              char file[max_char];
              file = get_input_char();
              recognize(file); 
              break;
         case 3:
              printf("Tchau!\n");
              break;
         default:
              printf("Este não é um comando válido!\n");
              break;
     }
}

//Faz o reconhecimento da imagem a partir do vetor de características
void recognize(char *file){
}

// Cria o vetor de características
void create_vector(){
    //nome do diretorio e vetor para nomes das imagens
    char dir[max_char], file[max_char];
    //Auxiliars
    int i;
}






