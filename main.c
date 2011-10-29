#include <stdio.h>
#include <cv.h>
#include <cvaux.h>
#include <highgui.h>

void print_menu();
int get_input(int tipo);
void realize_action(int in);


int main(){

  while (input != -1){
    print_menu();
    input = get_input_int();
    realize_action(input);
  }

}

//Imprime opções de seleção do menu
void print_menu(){
}

//Le informação do usuário:Integer
int get_input_int(){
    int input;
    scanf("%i",&input);
    return input;
}

//Le informação do usuário:String
char get_input_char(){
    char input[100];
    scanf("%s",&input);
    return input;
}


//Faz a chamada para a opção escolhida
void realize_action(int in){
}







