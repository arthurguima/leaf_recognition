#include "cv.h"
#include "cxcore.h"
#include "highgui.h"
#include "stdio.h"

int main() {

    //Carrega imagem da Folha
	IplImage* imagem = cvLoadImage("leaf.jpg",1); 
    //Recebe imagem Final
   	IplImage* imagem2;
    //Recebe escala de cinza
    IplImage* imagem3 = cvCreateImage(cvGetSize(imagem), IPL_DEPTH_8U, 1);

    //Escala de cinza
    cvCvtColor(imagem, imagem3, CV_BGR2GRAY);

    /* Opção de usar smooth para reduzir riscos ao lado da folha */
	cvSmooth(imagem3, imagem3, CV_GAUSSIAN, 5, 5, 5, 5);

    /* Threshold da imagem da folha */
        // pega algumas inervações quando comentado
	    cvThreshold(imagem3, imagem3, 242, 242, CV_THRESH_BINARY);

    //Cria imagem com 1 canal
    imagem2 = cvCreateImage(cvGetSize(imagem), IPL_DEPTH_8U, 1);


// Detecção de Bordas

    //Laplace
        //cvLaplace(imagem3, imagem2, 3);

    // Canny
        //void cvCanny( const CvArr* image, CvArr* edges, double threshold1,double threshold2, int aperture_size=3 );
        cvCanny(imagem3, imagem2, 50, 150, 3);
    
    // Sobel
    
// Janelas      
    cvNamedWindow("Leaf", 1);
	cvShowImage("Leaf", imagem);

    cvNamedWindow("Cinza", 1);
	cvShowImage("Cinza", imagem3);
	
    cvNamedWindow("Laplace", 1);
	cvShowImage("Laplace", imagem2);

	cvWaitKey(-1);
		
    cvDestroyWindow("Laplace");
    cvDestroyWindow("Leaf");
    cvDestroyWindow("Cinza");
    cvReleaseImage(&imagem);
    cvReleaseImage(&imagem2);
	cvReleaseImage(&imagem3);

}
