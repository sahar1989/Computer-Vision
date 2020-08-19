#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

int main()
{
	CvCapture *cg = 0;	
	Mat frGauche, frameCopy;

	cvNamedWindow("gauche", 1);
//	cvNamedWindow("droite", 2);
	cg= cvCaptureFromCAM(0);

	if (cg == NULL) {
		fprintf(stderr, "Je ne peux pas initialiser la camera\n");
		exit(1);
	}

	printf("cvCaptureFromCAM(0) fait\n");

	for (i=0; i < 50; i++)
	{
		IplImage* pImg= cvQueryFrame(cg);
		frGauche= pImg;

            if( frGauche.empty() )
		{
			puts("empty");
	                break;
		}

            if( pImg->origin == IPL_ORIGIN_TL )
                frGauche.copyTo( frameCopy );
            else
                flip( frGauche, frameCopy, 0 );

 
		cv::imshow("gauche", frameCopy);		
	}

	cvReleaseCapture(&cg);

	return 0;
}
