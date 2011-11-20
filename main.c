#include <stdio.h>
#include <string.h> 
#include <cv.h>
#include <cvaux.h>
#include <dirent.h>
#include <highgui.h>

#define MAX_STRING_LENGTH 180   //número máximo de caracteres nas strings recebidas
#define MAX_SPECIES_VECTOR 30 //número máximo de espécies vegetais

//Estrutura para guardar as características e nome de cada espécie vegetal
struct caracteristic_vector {
  int caracteristics[5];
  char name[30];
};

//Vetor de estruturas
struct caracteristic_vector species[MAX_SPECIES_VECTOR];

/*** Assinatura dos métodos ***/
void  print_menu          ();
void  realize_action      (int in);
int   get_input_int       ();
char  get_input_char      (char* in);
void  create_vector       (char* dir);
int  recognize            (char* file);
void  add_image_to_vector (char* image);
float leaf_width          (IplImage* img);
float leaf_height         (IplImage* img);
float leaf_area           (IplImage* img);
float leaf_perimeter      (IplImage* img);
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

//Faz o reconhecimento da imagem a partir do vetor de características
int recognize(char* file){
  return 0;
}

// Cria o vetor de características
void create_vector(char* dir){
    //Estrutura que percorre os arquivos do diretório
    struct dirent **namelist;
    int file_num; // número de arquivos no diretório
    file_num = scandir(dir, &namelist, 0, alphasort);

       
    if (file_num < 0)
      perror("Não existem arquivos no diretório");
    else {
      while(file_num--) {
        char image[MAX_STRING_LENGTH];
        sprintf(image, "%s%s", dir, namelist[file_num]->d_name); 

        /* !DEBUG! printf("Cadastra -> %s\n", namelist[file_num]->d_name);  !DEBUG! */
        add_image_to_vector(image, namelist[file_num]->d_name); //Usa a imagem como entrada para o vetor
        free(namelist[file_num]); //libera posição na memória
      }
    }
}

//Adiciona caracteristicas da folha ao vetor de carcterísticas
void add_image_to_vector(char* address, char* image){
 
 //Carrega imagem da Folha
	IplImage* imagem = cvLoadImage(address,1); 
 //Usa smooth para reduzir riscos ao lado da folha 
	cvSmooth(imagem, imagem, CV_GAUSSIAN, 5, 5, 5, 5);
 //Threshold da imagem da folha
	cvThreshold(imagem, imagem, 242, 242, CV_THRESH_BINARY); //sem enervamento

       /* !DEBUG */
          /*cvNamedWindow("DEBUG", 1);
          cvShowImage("DEBUG", imagem);
          cvWaitKey(-1);
          cvDestroyWindow("DEBUG");
        	cvReleaseImage(&imagem);*/
       /* !DEBUG */

  float height    = leaf_height(imagem);
  float width     = leaf_width(imagem);
  float area      = leaf_area(imagem);
  float perimeter = leaf_perimeter(imagem);

  char name[MAX_STRING_LENGTH];
  int  position; 
  
  sscanf();

}

// Retorna a altura da folha
float leaf_height (IplImage* img){
return 0.0;
}

//Retorna a largura da folha
float leaf_width (IplImage* img){
  return 0.0;
}

//Retorna a área da folha
float leaf_area (IplImage* img) {
  return 0.0;
}

//Retorna o perimetro da folha
float leaf_perimeter (IplImage* img){
  return 0.0;
}

/*                                                                                          *
 *                        Funções Gerais: Usadas para interação com o usuario               *                         
 *                                                                                          *
 *                                                                                          */

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
char get_input_char(char* in){
    char input[MAX_STRING_LENGTH];
    scanf("%s",input);
    strcpy (in, input);
    return 1;
}

//Faz a chamada para a opção escolhida
void realize_action(int in){
  switch (in){
         case 1:
              printf("Em qual diretório estão as imagens?\n");
              printf("Use . para o diretório atual\n");
              char dir[MAX_STRING_LENGTH];
              get_input_char(dir);  //DEBUG printf("READ: %s", dir);
              create_vector(dir);
              break;
         case 2:
              printf("Qual o endereço da imagem que deseja reconheceer?\n");
              char file[MAX_STRING_LENGTH];
              get_input_char(file);
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

