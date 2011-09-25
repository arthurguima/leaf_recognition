#include "cv.h"
#include "cxcore.h"
#include "highgui.h"
#include "stdio.h"

int main() {
	IplImage* imagem;
	IplImage* imagem2;
	
	imagem = cvLoadImage("leaf.jpg",0); 
	
    /* Opção de usar smooth para reduzir riscos ao lado da folha */
	cvSmooth(imagem, imagem, CV_GAUSSIAN, 5, 5, 5, 5); //legalzinho

	/* Threshold da imagem da folha */
	cvThreshold(imagem, imagem, 242, 242, CV_THRESH_BINARY); //sem enervamento
	//cvThreshold(imagem, imagem, 155, 155, CV_THRESH_BINARY); //com enervamento
	
	cvNamedWindow("Leaf", 1);
	cvShowImage("Leaf", imagem);
	
	cvWaitKey(-1);
	
	cvDestroyWindow("Leaf");
	cvReleaseImage(&imagem);
}
