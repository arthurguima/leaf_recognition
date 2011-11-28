#include <stdio.h>
#include <string.h> 
#include <cv.h>
#include <cvaux.h>
#include <dirent.h>
#include <highgui.h>

#include <limits.h>
#include <float.h>

#define MAX_STRING_LENGTH 180   //número máximo de caracteres nas strings recebidas
#define MAX_SPECIES_VECTOR 10 //número máximo de espécies vegetais

//Estrutura para guardar as características e nome de cada espécie vegetal
struct caracteristic_vector {
  float caracteristics[5];
  char name[30];
};

//Vetor de estruturas
struct caracteristic_vector species[MAX_SPECIES_VECTOR];

/*** Assinatura dos métodos ***/
void  print_menu                ();
void  realize_action            (int in);
int   get_input_int             ();
int   get_input_char            (char* in);
void  create_vector             (char* dir);
int   recognize                 (char* file);
void  add_image_to_vector       (char* address, char* image);
void  initialize_species_vector ();
float leaf_width                (IplImage* img);
float leaf_height               (IplImage* img);
float leaf_area                 (IplImage* img);
float leaf_perimeter            (IplImage* img);
/*****************************/

//Função principal
int main(){

  int input;

  initialize_species_vector();

  while (input != 3){
    print_menu();
    input = get_input_int();
    realize_action(input);
  }

  return 0;
}

//inicializa o vetor species
void initialize_species_vector(){
  
  int i = 0, k;

  for(i; i < MAX_SPECIES_VECTOR; i++)
    for(k=0; k < 5; k++)
       species[i].caracteristics[k] = 0;
}

//Faz o reconhecimento da imagem a partir do vetor de características
int recognize(char* file){

 // puts("debug 1");

//Carrega imagem da Folha
	IplImage* imagem = cvLoadImage(file,0);
 //Usa smooth para reduzir riscos ao lado da folha 
	cvSmooth(imagem, imagem, CV_GAUSSIAN, 5, 5, 5, 5);
 //Threshold da imagem da folha
	cvThreshold(imagem, imagem, 242, 242, CV_THRESH_BINARY); //sem enervamento

  float best_choice = FLT_MAX - 1;
  int  i, result;
  float aux;
  float height    = leaf_height(imagem);
  float width     = leaf_width(imagem);
  float area      = leaf_area(imagem);
  float perimeter = leaf_perimeter(imagem);


  for (i = 0; i < MAX_SPECIES_VECTOR; i++) {
    aux = sqrt( 
                pow( (height - species[i].caracteristics[0]),2) + 
                pow( (width  - species[i].caracteristics[1]),2)  + 
                pow( (area   - species[i].caracteristics[2]),2) + 
                pow( (perimeter - species[i].caracteristics[3]),2));
    printf("Distancia %f\n", aux);

    if (aux < best_choice){
        best_choice = aux;
        result = i;
    }
  }

  printf("/nEssa folha pertence a espécie \"%s\"./n", species[result].name );

//  printf("/n%f/n",best_choice);
  return best_choice;
}

// Cria o vetor de características
void create_vector(char* dir){
    //Estrutura que percorre os arquivos do diretório
    struct dirent **namelist;
    int file_num; // número de arquivos no diretório
    file_num = scandir(dir, &namelist, 0, alphasort);

    printf("Numero de arquivos encontrados para o treinamento: %i\n\n", file_num-2);
       
    if (file_num == 2) //linux inclui . e .. não sei pq
      perror("Não existem arquivos no diretório");
    else {
      while(file_num-- > 2) {
        char image[MAX_STRING_LENGTH];
        sprintf(image, "%s/%s", dir, namelist[file_num]->d_name);

        /* !DEBUG!  printf("file_num = %i, name = %s\n", file_num, namelist[file_num]->d_name); !DEBUG! */
        /* !DEBUG! printf("Cadastra -> %s\n", namelist[file_num]->d_name);  !DEBUG! */
        
        add_image_to_vector(image, namelist[file_num]->d_name); //Usa a imagem como entrada para o vetor
        free(namelist[file_num]); //libera posição na memória
      }
    }
}

//Adiciona caracteristicas da folha ao vetor de carcterísticas
void add_image_to_vector(char* address, char* image){
 
 //Carrega imagem da Folha
	IplImage* imagem = cvLoadImage(address,0);
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
  int position; 
  char trash;
 
  sscanf(image, "%s %i %c", name, &position, &trash);

  /* !DEBUG! printf("NAME: %s, POSITION: %i, TRASH: %c \n", name,position, trash); !DEBUG */

  strcpy(species[position].name, name);

  if (species[position].caracteristics[0] ==  0){
     species[position].caracteristics[0] =  height;
     species[position].caracteristics[1] =  width;
     species[position].caracteristics[2] =  area;
     species[position].caracteristics[3] =  perimeter;
  }
  else{
     species[position].caracteristics[0] =  (species[position].caracteristics[0] + height)/2;
     species[position].caracteristics[1] =  (species[position].caracteristics[1] +  width)/2;
     species[position].caracteristics[2] =  (species[position].caracteristics[2] +  area)/2;
     species[position].caracteristics[3] =  (species[position].caracteristics[3] +  perimeter)/2;
  }

}

// Retorna a altura da folha
float leaf_height (IplImage* img){

  float max = -1;
  IplImage* imgA = img;
	int altura = imgA->height;
	int largura = imgA->width;
	int i,j;
	int contador = 0;

  int step    = imgA->widthStep;
  uchar* data = (uchar*) imgA->imageData;
  int channels= imgA->nChannels;

	
	for (i=0; i < largura; i++) {
    contador = 0;
		for (j=0; j < altura; j++) {
			if (data[i*step + j*channels] == 0) {
				contador++;
			}
		}
		if(contador > max)
      max = contador;
	}
	
  printf("MaxHeight: %f\n", max);
	return max; 
}

//Retorna a largura da folha
float leaf_width (IplImage* img){
  float max = -1;

  IplImage* imgB = img;
	int altura = imgB->height;
	int largura = imgB->width;
	int i,j;
	int contador = 0;

  int step    = imgB->widthStep;
  uchar* data = (uchar*) imgB->imageData;
  int channels= imgB->nChannels;


	for (i=0; i < altura; i++) {
    contador = 0;
		for (j=0; j < largura; j++) {
			if (data[i*step + j*channels] == 0) {
				contador++;
			}
		}
		if (contador > max)
       max = contador;
	}
	
  printf("MaxWidth: %f\n", max);
	return max;
}

//Retorna a área da folha
float leaf_area (IplImage* img) {
  float area;
  IplImage* grayImg = img;
  IplImage* contourImg = NULL;

  //Parametros para a detecção do contorno
  CvMemStorage * storage = cvCreateMemStorage(0);
  CvSeq * contour = 0;
  int mode = CV_RETR_CCOMP; //detect both outside and inside contour
  //int mode = CV_RETR_EXTERNAL;//detects only outer contour

  // Cria cópia pois o cvFindCountour altera a imagem original
  contourImg = cvCreateImage(cvGetSize(grayImg), IPL_DEPTH_8U, 3);
  contourImg=cvCloneImage(grayImg);   
  //Encontra o Contorno
  cvFindContours(contourImg, storage, &contour, sizeof(CvContour), mode, CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0));
  //cvFindContours(contourImg, storage, &contour, sizeof( CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint( 0, 0) );

  //Encontra o valor da área
   area = abs(cvContourArea(contour, CV_WHOLE_SEQ,0));

  printf("Area %f\n", area);
  return area;
}

//Retorna o perimetro da folha
float leaf_perimeter (IplImage* img){
  float perimeter;
  IplImage* grayImg = img;
  IplImage* contourImg = NULL;

  //Parametros para a detecção do contorno
  CvMemStorage * storage = cvCreateMemStorage(0);
  CvSeq * contour = 0;
  int mode = CV_RETR_CCOMP; //detect both outside and inside contour
  //int mode = CV_RETR_EXTERNAL;//detects only outer contour

  // Cria cópia pois o cvFindCountour altera a imagem original
  contourImg = cvCreateImage(cvGetSize(grayImg), IPL_DEPTH_8U, 3);
  contourImg=cvCloneImage(grayImg);   
  //Encontra o Contorno
  cvFindContours(contourImg, storage, &contour, sizeof(CvContour), mode, CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0));
  //cvFindContours(contourImg, storage, &contour, sizeof( CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint( 0, 0) );

  cvContourPerimeter(contour);

  printf("Perimeter: %f\n\n", perimeter);
  return perimeter; 
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
int get_input_char(char* in){
    char input[MAX_STRING_LENGTH];
    scanf("%s",input);
    strcpy (in, input);
    return 1;
}

//Faz a chamada para a opção escolhida
void realize_action(int in){
  switch (in){
         case 1:
              puts("Em qual diretório estão as imagens?\n");
              puts("Use . para o diretório atual\n");
              char dir[MAX_STRING_LENGTH];
              get_input_char(dir);  //DEBUG printf("READ: %s", dir);
              create_vector(dir);
              puts("Treinamento realizado com sucesso.\n");
              break;
         case 2:
              puts("Qual o endereço da imagem que deseja reconhecer?\n");
              char file[MAX_STRING_LENGTH];
              get_input_char(file);
              recognize(file); 
              break;
         case 3:
              puts("Tchau!\n");
              break;
         default:
              puts("Este não é um comando válido!\n");
              break;
  }
}

