#include <stdio.h>
#include <stdlib.h>
#include "highgui/highgui_c.h"

#define NCAMS 1

int main( int argc, const char** argv )
{
    const char *propnames[] = { "CV_CAP_PROP_POS_MSEC", "CV_CAP_PROP_POS_FRAMES", "CV_CAP_PROP_POS_AVI_RATIO",
"CV_CAP_PROP_FRAME_WIDTH", "CV_CAP_PROP_FRAME_HEIGHT", "CV_CAP_PROP_FPS", "CV_CAP_PROP_FOURCC", NULL };

    int propvals[] = { CV_CAP_PROP_POS_MSEC, CV_CAP_PROP_POS_FRAMES, CV_CAP_PROP_POS_AVI_RATIO,
CV_CAP_PROP_FRAME_WIDTH, CV_CAP_PROP_FRAME_HEIGHT, CV_CAP_PROP_FPS, CV_CAP_PROP_FOURCC, 0 };

    CvCapture* cap[NCAMS];
    char camname[NCAMS][60];
    Mat frame, frame_droite;
    int i;

    for (i= 0; i < NCAMS; i++)
    {
	cap[i]= cvCaptureFromCAM(i);

	printf("cvSetCaptureProperty i=%d\n", i);
        cvSetCaptureProperty(cap[i], CV_CAP_PROP_FRAME_WIDTH, 384);
        cvSetCaptureProperty(cap[i], CV_CAP_PROP_FRAME_HEIGHT, 288);
//        cvSetCaptureProperty(cap[i], CV_CAP_PROP_FPS, 2); 

	sprintf(camname[i], "cam%d", i);
	cvNamedWindow( camname[i], i);
    }

   for (i= 0; i < NCAMS; i++)
   {
	int j;

	for (j=0; propnames[j] != NULL; j++)
	{
		double v= cvGetCaptureProperty(cap[i], propvals[j]);
		printf("CAM %d, %s = %d\n", i, propnames[j], v);	
	}
   }

	puts("In capture...");
     for(;;)	
     {
	for (i= 0; i < NCAMS; i++)
	{
            IplImage* iplImg = cvQueryFrame( cap[i] );

            cvImshow( camname[i], frame );

            if( waitKey( 10 ) >= 0 )
                goto _cleanup_;
        }
     }

_cleanup_:
	for (i= 0; i < NCAMS; i++)
	{
	        cvReleaseCapture( &cap[i] );
		cvDestroyWindow(camname[i]);
	}

    return 0;
}


