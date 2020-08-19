#include "opencv2/opencv.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>
#include <assert.h>

using namespace std;
using namespace cv;

#define NCAMS 1

int main( int argc, const char** argv )
{
    const char *propnames[] = { "CV_CAP_PROP_POS_MSEC", "CV_CAP_PROP_POS_FRAMES", "CV_CAP_PROP_POS_AVI_RATIO",
"CV_CAP_PROP_FRAME_WIDTH", "CV_CAP_PROP_FRAME_HEIGHT", "CV_CAP_PROP_FPS", "CV_CAP_PROP_FOURCC",   "CV_CAP_PROP_FRAME_COUNT", "CV_CAP_PROP_FORMAT", "CV_CAP_PROP_MODE" , NULL } ;

    int propvals[] = { CV_CAP_PROP_POS_MSEC, CV_CAP_PROP_POS_FRAMES, CV_CAP_PROP_POS_AVI_RATIO,
CV_CAP_PROP_FRAME_WIDTH, CV_CAP_PROP_FRAME_HEIGHT, CV_CAP_PROP_FPS, CV_CAP_PROP_FOURCC, CV_CAP_PROP_FRAME_COUNT, CV_CAP_PROP_FORMAT, CV_CAP_PROP_MODE };

    VideoCapture* caps[NCAMS];	    
    char camname[NCAMS][60];
    int i;


    for (i= 0; i < NCAMS; i++)
    {
	int j;

	caps[i]= new VideoCapture(0);
	assert(caps[i] != NULL);

//	Mat toto;
//	caps[i]->read(toto);

	if (caps[i]->set(CV_CAP_PROP_FRAME_WIDTH, 320)) 
		cout << "CV_CAP_PROP_FRAME_WIDTH raté\n";

	caps[i]->set(CV_CAP_PROP_FRAME_HEIGHT, 240);

	namedWindow("CAM"+i, CV_WINDOW_AUTOSIZE);

	for (j=0; propnames[j] != NULL; j++)
	{
		double v= caps[i]->get(propvals[j]);
		printf("CAM %d, %s = %lf\n", i, propnames[j], v);	
	}
   }

     cout << "In capture ..." << endl;
     for(;;)	
     {
	for (i= 0; i < NCAMS; i++)
	{
	    Mat frame;

            caps[i]->read(frame);
            
            imshow("CAM"+i, frame );

            if( waitKey( 10 ) >= 0 )
                goto _cleanup_;
        }
     }

_cleanup_:
	for (i= 0; i < NCAMS; i++)
	{
		caps[i]->release();
	}

    return 0;
}


