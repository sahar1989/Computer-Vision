#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>

#define NCAMS 1

using namespace std;
using namespace cv;


int main()
{
	const char *noms[] = { "un", "deux" };

	VideoCapture caps[NCAMS];
	int i;

	for (i= 0; i < NCAMS; i++)
	{
		if (!caps[i].open(i)) 
		{
			cerr << "Ne peut pas initialiser la camera " << i+1 << "\n";
			return 1;
		}

		caps[i].set(CV_CAP_PROP_FRAME_WIDTH, 352);
		caps[i].set(CV_CAP_PROP_FRAME_HEIGHT, 288);
//		caps[i].set(CV_CAP_PROP_FPS, 2); 


	      namedWindow(noms[i], i+1);
	}
 
	char key = ' ';
 
 	while(key != 'q')          //On pourra arrêter la boucle en appuyant sur la touche q, key représente la touche du clavier appuyé
	{
		for (i= 0; i < NCAMS; i++)
		{
			Mat frame;

		 	caps[i] >> frame; //  On récupère la frame à chaque passage dans la boucle

			imshow(noms[i], frame); 
		        key = cvWaitKey(10); // On attend un peu de temps, IMPORTANT !
		}
    }
 
    cvDestroyAllWindows();  // On détruit les fenêtres, c'est plus agréable

    for (i= 0; i < NCAMS; i++)
	    caps[i].release();  // On détruit la capture

    cvWaitKey(0);  //  Mettre zéro permet d'attendre un temps infini
    return 0;
 
}

