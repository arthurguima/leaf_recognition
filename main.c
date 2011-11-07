#include <stdio.h>
#include <string.h> 
#include <cv.h>
#include <cvaux.h>
#include <dirent.h>
#include <highgui.h>

#define max_char 100   //número máximo de caracteres nas strings recebidas
#define max_species 30 //número máximo de espécies vegetais

//Estrutura para guardar as características e nome de cada espécie vegetal
struct{
  int carac[5];
  char name[30];
} carcteristic_vector

//Vetor de estruturas
struct caracteristic_vector species[max_species];

/*** Assinatura dos métodos ***/
void  print_menu();
void  realize_action(int in);
int   get_input_int();
char  get_input_char();
void  create_vector(char *dir);
void  recognize(char *file);
void  add_image_to_vector(char *image);
/*****************************/

//Função principal
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
  puts("Escolha uma das seguintes opções:\n");
  puts("1. Inserir conjunto de treino.\n"); 
  puts("2. Reconhecer espécie vegetal.\n"); 
  puts("3. Sair.\n");
}

//Le informação do usuário:Integer
int get_input_int(){
    int input;
    scanf("%i",&input);
    return input;
}

//Le informação do usuário:String
char get_input_char(char *in){
    char input[max_char];
    scanf("%s",&input);
    strcpy (in, input);
    return 1;
}


//Faz a chamada para a opção escolhida
void realize_action(int in){
  switch (in){
         case 1:
              printf("Em qual diretório estão as imagens?\n");
              char dir[max_char];
              get_input_char(*dir);
              create_vector(dir);
              break;
         case 2:
              printf("Qual o endereço da imagem que deseja reconheceer?\n");
              char file[max_char];
              get_input_char(*file);
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
void create_vector(char *dir){
    //Estrutura que percorre os arquivos do diretório
    struct dirent **namelist;
    int file_num; // número de arquivos no diretório
    file_num = scandir(dir, &namelist, 0, alphasort);
    
    if (file_num < 0)
      perror("Não existem arquivos no diretório");
    else {
      while(file_num--) {
        //printf("Cadastra -> %s\n", namelist[file_num]->d_name); // !debug
        add_image_to_vector(namelist[file_num]->d_name); //Usa a imagem como entrada para o vetor
        free(namelist[file_num]); //libera posição na memória
      }
    }
}


//Adiciona caracteristicas da folha ao vetor de carcterísticas
void add_image_to_vector(char *image){
 
 //Carrega imagem da Folha
	IplImage* imagem = cvLoadImage(image,1); 
 //Usa smooth para reduzir riscos ao lado da folha 
	cvSmooth(imagem, imagem, CV_GAUSSIAN, 5, 5, 5, 5);
 //Threshold da imagem da folha
	cvThreshold(imagem, imagem, 242, 242, CV_THRESH_BINARY); //sem enervamento
 
        /* !DEBUG */
         /* cvNamedWindow("DEBUG", 1);
          cvShowImage("DEBUG", imagem);
          cvWaitKey(-1);
          cvDestroyWindow("DEBUG");
        	cvReleaseImage(&imagem);*/
       /* !DEBUG */

  // http://www710.univ-lyon1.fr/~bouakaz/OpenCV-0.9.5/docs/ref/OpenCVRef_StructAnalysis.htm

}



