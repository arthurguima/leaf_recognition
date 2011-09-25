#include <stdio.h>
#include <cv.h>
#include <cvaux.h>
#include <highgui.h> 


int main( int argc, char** argv ) {

    // Carrega imagem recebida     
      IplImage* img = cvLoadImage(argv[1], 0);

    // Pega as propriedades da imagem 
      int height  = img->height;
      int width   = img->width;
      int step    = img->widthStep;
      uchar* data = (uchar*) img->imageData;
      int channels= img->nChannels;

      // Cria uma janela com a imagem do ponteiro criado, que espera por um sinal para finalizar
      cvNamedWindow( "Janela", 1 );
      cvShowImage("Janela", img);
      cvWaitKey(-1);
      cvDestroyWindow("Janela");

      // Libera a memória
      cvReleaseImage(&img);

  return 0;    
}
